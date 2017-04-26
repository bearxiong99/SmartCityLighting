/*
 * mesh.c
 *
 *  Created on: Mar 9, 2017
 *      Author: Chris
 */


#define _DEBUGGING_


#include <stdbool.h>
#include <ti/drivers/dpl/ClockP.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
/* Board Header files */
#include "Board.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* User include files */
#include "mesh.h"
#include "packets.h"
#include "sensors.h"
#include "NODE_ID.h"

#include <stdio.h>
#include <stdlib.h>
/***** Defines *****/

#define RFEASYLINKEX_TASK_STACK_SIZE 1024
#define RFEASYLINKEX_TASK_PRIORITY   2

#define PINGPARENT_TASK_STACK_SIZE 1024
#define PINGPARENT_TASK_PRIORITY   5

#define SENSOR_TASK_STACK_SIZE 1024
#define SENSOR_TASK_PRIORITY   4

#define DISCOVER_TASK_STACK_SIZE 1024
#define DISCOVER_TASK_PRIORITY   3

#define REMOVE_KIDS_TASK_STACK_SIZE 512
#define REMOVE_KIDS_TASK_PRIORITY   3

// TODO: add task to remove children if they haven't pinged recently

/***** Variable declarations *****/
static uint8_t rxTaskStack[RFEASYLINKEX_TASK_STACK_SIZE];
static uint8_t pingParentTaskStack[PINGPARENT_TASK_STACK_SIZE];
static uint8_t sensorTaskStack[SENSOR_TASK_STACK_SIZE];
static uint8_t discoverTaskStack[DISCOVER_TASK_STACK_SIZE];
static uint8_t removeKidsTaskStack[REMOVE_KIDS_TASK_STACK_SIZE];
Task_Handle pingParentTask;    /* not static so you can see in ROV */
Task_Handle rxTask;    /* not static so you can see in ROV */
Task_Handle sensorTask;    /* not static so you can see in ROV */
Task_Handle discoverTask;    /* not static so you can see in ROV */
Task_Handle removeKidsTask;    /* not static so you can see in ROV */
bool pingConfReceived;
Semaphore_Handle ezlnkSem;
Semaphore_Handle pingConfSem;
Semaphore_Handle nodeSem;
/***** Node variables *****/
nodeInfo node;
address defaultAddress = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

void txPayload(packetType type, uint8_t *payload, uint8_t len, uint8_t *dstAddr);
void pingParentTask_init();
void discoverTask_init();
void sensorTask_init();
void remove_kids_Task_init();
bool createChildAddress(address* address);

void receivedParentalPing(ParentalPingStruct *p) {
    ReceiptConfirmationStruct r;
    r.t = ParentalPing;
    uint8_t childNum = 0x00;
    uint8_t childBitShift = 4;
    uint8_t val = p->childAddress.addr[childBitShift/8] << (childBitShift % 8);
    while(val) { // if our address isn't all 0s yet
        childBitShift += 2;
        val = p->childAddress.addr[childBitShift/8] << (childBitShift % 8);
    }

    childNum = (p->childAddress.addr[(childBitShift-2)/8] & (0x03 << ((8-(childBitShift%8))% 8))) >> ((8 - (childBitShift%8))% 8); // Would like to clean up this mess

    Semaphore_pend(nodeSem, BIOS_WAIT_FOREVER);
    switch(childNum) {
    case 1:
        node.childOnePinged = true;
        break;
    case 2:
        node.childTwoPinged = true;
        break;
    case 3:
        node.childThreePinged = true;
        break;
    }
    Semaphore_post(nodeSem);

    txPayload(ReceiptConfirmation, (uint8_t *) &r, sizeof(r), &(p->childAddress.addr[0]));

}

void receivedConfirmation(ReceiptConfirmationStruct *m) {
    Semaphore_pend(pingConfSem, BIOS_WAIT_FOREVER);
    pingConfReceived = true;
    Semaphore_post(pingConfSem);
}

void receivedDiscoveryMessage(DiscoveryMessageStruct *m) {
    UndiscoveredResponseStruct resp;
    Semaphore_pend(nodeSem, BIOS_WAIT_FOREVER);
    if(!node.inNetwork) {
        node.undiscoveredID = rand();
        resp.undiscoveredID = node.undiscoveredID;
    }
    Semaphore_post(nodeSem);
    txPayload(UndiscoveredResponse, (uint8_t*) &resp, sizeof(resp), (uint8_t *) &m->parentAddress.addr[0]);
}

void receivedUndiscoveredResponse(UndiscoveredResponseStruct *m) {
    AssignAddressStruct assignment;
    int i;
    assignment.undiscoveredID = m->undiscoveredID;

    if(!node.inNetwork) {
        return; // Some error must have occurred
    }

    for(i = 0; i < 8; i++) {
        assignment.parentAddress.addr[i] = node.own_address.addr[i];
    }

    if(createChildAddress(&assignment.finalAddress)) {
        txPayload(AssignAddress, (uint8_t *) &assignment, sizeof(assignment), (uint8_t *) &defaultAddress.addr[0]);
    } // Else no room for kids, so do nothing
}

void receivedAssignAddress(AssignAddressStruct *m) {
    if(node.inNetwork || m->undiscoveredID != node.undiscoveredID) {
        return; // Message not meant for me
    }

    int i;
    for(i = 0; i < 8; i++) {
        node.own_address.addr[i] = m->finalAddress.addr[i];
        node.parent_address.addr[i] = m->parentAddress.addr[i];
    }
    node.inNetwork = true;

    Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
    EasyLink_enableRxAddrFilter(&node.own_address.addr[0], 8, 1);
    Semaphore_post(ezlnkSem);
}

void receivedSensorData(SensorDataStruct *m) {
    if(!node.inNetwork) {
        return; // Sensor data dies here
    }

    txPayload(SensorData, (uint8_t *) m, sizeof(SensorDataStruct), (uint8_t *) &node.parent_address.addr[0]); // Send to parent
}

bool createChildAddress(address* address) {
    bool success = false;
    uint8_t childBitShift = 4;
    int i;
    uint8_t childBits = 0x00;
    if(node.own_address.addr[7] & 0xC0 != 0) { //Can't give address to child
        return false;
    }

    Semaphore_pend(nodeSem, BIOS_WAIT_FOREVER);

    uint8_t val = node.own_address.addr[childBitShift/8] << (childBitShift % 8);
    while(val) { // if our address isn't all 0s yet
        childBitShift += 2;
        val = node.own_address.addr[childBitShift/8] << (childBitShift % 8);
    }

    for(i = 0; i < 8; i++) {
        address->addr[i] = node.own_address.addr[i];
    }
    if(!node.hasChildOne) {
        childBits = 0x01;
        node.hasChildOne = true;
        node.childOnePinged = true;
        success = true;
    }
    else if(!node.hasChildTwo) {
        childBits = 0x02;
        node.hasChildTwo = true;
        node.childTwoPinged = true;
        success = true;
    }
    else if(!node.hasChildThree) {
        childBits = 0x03;
        node.hasChildThree = true;
        node.childThreePinged = true;
        success = true;
    }
    else {
        success = false;
    }

    address->addr[childBitShift/8] = node.own_address.addr[childBitShift/8] | (childBits << (6 - (childBitShift % 8)));

    Semaphore_post(nodeSem);
    return success;
}

static void removeKidsFnx(UArg arg0, UArg arg1) {

    uint64_t timeout = ((unsigned long)MIN_TIME_TO_REMOVE_CHILD * 1000000L) / Clock_tickPeriod;
    node.childOnePinged = true;
    node.childTwoPinged = true;
    node.childThreePinged = true;
    while(true) {
        Task_sleep(timeout);
        if(!node.inNetwork) {
            continue;
        }
        Semaphore_pend(nodeSem, BIOS_WAIT_FOREVER);
        if(node.childOnePinged) {
            node.childOnePinged = false;
        }
        else { // else remove child
            node.hasChildOne = false;
        }
        if(node.childTwoPinged) {
            node.childTwoPinged = false;
        }
        else { // else remove child
            node.hasChildTwo = false;
        }
        if(node.childThreePinged) {
            node.childThreePinged = false;
        }
        else { // else remove child
            node.hasChildThree = false;
        }
        Semaphore_post(nodeSem);
    }
}

static void discoverFnx(UArg arg0, UArg arg1) {

    uint64_t timeout = ((unsigned long)DISCOVERY_MESSAGE_INTERVAL * 1000000L) / Clock_tickPeriod;
    DiscoveryMessageStruct d;
    int i;

    while(true) {
        Task_sleep(timeout);
        if(!node.inNetwork) {
            continue;
        }

        for(i = 0; i < 8; i++) {
            d.parentAddress.addr[i] = node.own_address.addr[i];
        }

        txPayload(DiscoveryMessage, (uint8_t*) &d, sizeof(DiscoveryMessageStruct), &defaultAddress.addr[0]); // Send sensor data to parent
    }
}

static void sensorFnx(UArg arg0, UArg arg1) {

    SensorDataStruct sensors;
    uint64_t timeout = ((unsigned long)SENSOR_TRANSMISSION_INTERVAL * 1000000L) / Clock_tickPeriod;
    while(true) {
        Task_sleep((uint32_t)timeout);
        if(!node.inNetwork) {
            continue; // Don't bother sampling if out of network
        }

        getSensorData(&sensors);
        /*sensors.amps = 11;
        sensors.humidity = 22;
        sensors.light = 33;
        sensors.motions = 44;
        sensors.temp = 55;*/
        sensors.id = NODE_ID;

        txPayload(SensorData, (uint8_t*) &sensors, sizeof(SensorDataStruct), &node.parent_address.addr[0]); // Send sensor data to parent
    }
}

static void pingParentFnx(UArg arg0, UArg arg1)
{
    int i;
    uint8_t failureCount = 0; // Counts number of pings to parent without response from parent
    uint64_t timeout = ((unsigned long)MIN_PING_INTERVAL * 1000000L) / Clock_tickPeriod;
    ParentalPingStruct ping;
    while(true) {
        Task_sleep((uint32_t)timeout);
        if(!node.inNetwork) {
            continue;
        }
        Semaphore_pend(pingConfSem, BIOS_WAIT_FOREVER);
        if(pingConfReceived) {
            pingConfReceived = false;
            failureCount = 0;
        }
        else {
            failureCount++;
        }
        Semaphore_post(pingConfSem);

        if(failureCount >= MAX_PING_ATTEMPTS) { // Leave network
            Semaphore_pend(nodeSem, BIOS_WAIT_FOREVER);
            node.inNetwork = false;
            node.hasChildOne = false;
            node.hasChildTwo = false;
            node.hasChildThree = false;
            failureCount = 0;
            for(i = 0; i < 8; i++) {
                node.own_address.addr[i] = DEFAULT_NODE_ADDRESS;
            }
            Semaphore_post(nodeSem);

            Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
            EasyLink_enableRxAddrFilter(&node.own_address.addr[0], 8, 1); // Have to acquire easylink to change receiving addresses
            Semaphore_post(ezlnkSem);

        }
        // add send ping, wait for response, etc.
        for(i = 0; i < 8; i++) {
            ping.childAddress.addr[i] = node.own_address.addr[i];
        }
        txPayload(ParentalPing, (uint8_t*) &ping, sizeof(ParentalPingStruct), &node.parent_address.addr[0]); // Send ping
    }
}

static void rfEasyLinkRxFnx(UArg arg0, UArg arg1)
{
    //EasyLink_init(EasyLink_Phy_Custom);
    EasyLink_init(EasyLink_Phy_50kbps2gfsk);

    // These are initialized in here so they can be run after EasyLink is init'd,
    // EasyLinkInit is in here b/c it uses semaphores so needs to run inside a task
    config_sensors();
    pingParentTask_init();
    discoverTask_init();
    sensorTask_init();
    remove_kids_Task_init();

    EasyLink_RxPacket rxPacket = {0};
    EasyLink_Status status;

    uint32_t timeout = ((unsigned long)BLOCKING_RECEIVE_TIMEOUT_MS * 1000000L) / Clock_tickPeriod;
    rxPacket.rxTimeout = timeout;
    rxPacket.absTime = 0;

    /*
     * If you wish to use a frequency other than the default, use
     * the following API:
     * EasyLink_setFrequency(868000000);
     */
    Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
    EasyLink_setCtrl(EasyLink_Ctrl_AddSize, 8);
    EasyLink_enableRxAddrFilter(&node.own_address.addr[0], 8, 1);
    Semaphore_post(ezlnkSem);

    while(true) {
        Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
        rxPacket.rxTimeout = timeout;
        rxPacket.absTime = 0;
        status = EasyLink_receive(&rxPacket);
        Semaphore_post(ezlnkSem);

        if (status == EasyLink_Status_Success)
        {
            packetType p = ((packetType*) rxPacket.payload)[0];
            uint8_t *message = &(rxPacket.payload[sizeof(packetType)]);
            switch(p) {
                case ParentalPing:
                    receivedParentalPing((ParentalPingStruct*) message);
                    break;
                case ReceiptConfirmation:
                    receivedConfirmation((ReceiptConfirmationStruct*) message);
                    break;
                case DiscoveryMessage:
                    receivedDiscoveryMessage((DiscoveryMessageStruct *) message);
                    break;
                case UndiscoveredResponse:
                    receivedUndiscoveredResponse((UndiscoveredResponseStruct *) message);
                    break;
                case AssignAddress:
                    receivedAssignAddress((AssignAddressStruct *) message);
                    break;
                case SensorData:
                    receivedSensorData((SensorDataStruct *) message);
            }
        }
    }
}

void rxTask_init() {
    Task_Params tp;
    Task_Params_init(&tp);
    tp.stackSize = RFEASYLINKEX_TASK_STACK_SIZE;
    tp.priority = RFEASYLINKEX_TASK_PRIORITY;
    tp.stack = &rxTaskStack;
    tp.arg0 = (UInt)1000000;

    rxTask = Task_create(rfEasyLinkRxFnx, &tp, NULL);
}

void pingParentTask_init() {
    Task_Params tp;
    Task_Params_init(&tp);
    tp.stackSize = PINGPARENT_TASK_STACK_SIZE;
    tp.priority = PINGPARENT_TASK_PRIORITY;
    tp.stack = &pingParentTaskStack;
    tp.arg0 = (UInt)1000000;

    pingParentTask = Task_create(pingParentFnx, &tp, NULL);
}

void sensorTask_init() {
    Task_Params tp;
    Task_Params_init(&tp);
    tp.stackSize = SENSOR_TASK_STACK_SIZE;
    tp.priority = SENSOR_TASK_PRIORITY;
    tp.stack = &sensorTaskStack;
    tp.arg0 = (UInt)1000000;

    sensorTask = Task_create(sensorFnx, &tp, NULL);
}

void discoverTask_init() {
    Task_Params tp;
    Task_Params_init(&tp);
    tp.stackSize = DISCOVER_TASK_STACK_SIZE;
    tp.priority = DISCOVER_TASK_PRIORITY;
    tp.stack = &discoverTaskStack;
    tp.arg0 = (UInt)1000000;

    sensorTask = Task_create(discoverFnx, &tp, NULL);
}

void remove_kids_Task_init() {
    Task_Params tp;
    Task_Params_init(&tp);
    tp.stackSize = REMOVE_KIDS_TASK_STACK_SIZE;
    tp.priority = REMOVE_KIDS_TASK_PRIORITY;
    tp.stack = &removeKidsTaskStack;
    tp.arg0 = (UInt)1000000;

    removeKidsTask = Task_create(removeKidsFnx, &tp, NULL);
}
/* initMesh should only be called once at the startup of slave node */
void initMesh() {

    /* Create a semaphore for the RF hardware b/c can't tx and rx simultaneously */
    Semaphore_Params ezlnkParams;
    Error_Block ezlnkEb;
    Semaphore_Params nodeParams;
    Error_Block nodeEb;
    Semaphore_Params pingParams;
    Error_Block pingEb;

    int i;

    Semaphore_Params_init(&ezlnkParams);
    Error_init(&ezlnkEb);
    Semaphore_Params_init(&nodeParams);
    Error_init(&nodeEb);
    Semaphore_Params_init(&pingParams);
    Error_init(&pingEb);

    ezlnkParams.mode = Semaphore_Mode_BINARY;
    nodeParams.mode = Semaphore_Mode_BINARY;
    pingParams.mode = Semaphore_Mode_BINARY;
    /* Create semaphore instance */
    ezlnkSem = Semaphore_create(1, &ezlnkParams, &ezlnkEb);
    nodeSem = Semaphore_create(1, &nodeParams, &nodeEb);
    pingConfSem = Semaphore_create(1, &pingParams, &pingEb);

    Semaphore_post(ezlnkSem);
    Semaphore_post(nodeSem);
    Semaphore_post(pingConfSem);

    node.childOnePinged = false;
    node.hasChildOne = false;
    node.childTwoPinged = false;
    node.hasChildTwo = false;
    node.childThreePinged = false;
    node.hasChildThree = false;

    for(i = 0; i < 8; i++) {
        node.own_address.addr[i] = DEFAULT_NODE_ADDRESS;
        node.parent_address.addr[i] = DEFAULT_NODE_ADDRESS;
    }

    node.inNetwork = false;
    I2C_init();
    ADC_init();
    LampInit();
    init_sensors();
    rxTask_init(); // All other inits called from inside rx task so that easylink can be initialized;
}

//#define RFEASYLINKTX_BURST_SIZE 10
#define RFEASYLINKTX_BURST_SIZE 1

// Blocking tx call
void txPayload(packetType type, uint8_t* payload, uint8_t len, uint8_t *dstAddr)
{
    uint8_t txBursts = 0;


    /* If you wish to use a frequency other than the default use
     * the below API
     * EasyLink_setFrequency(868000000);
     */

    /* Set output power to 12dBm */
    EasyLink_setRfPwr(12);

    EasyLink_TxPacket txPacket =  { {0}, 0, 0, {0} };
    txPacket.len = len+1;
    int i;
    for (i = 0; i < 8; i++) {
        txPacket.dstAddr[i] = dstAddr[i];
    }

    txPacket.payload[0] = (uint8_t) type;

    for(i = 0; i < len; i++) {
        txPacket.payload[i+1] = payload[i];
    }


    while(txBursts <= RFEASYLINKTX_BURST_SIZE) {
        {
          /* Set Tx absolute time to send instantly */
          txPacket.absTime = 0;
        }
        Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
        EasyLink_Status result = EasyLink_transmit(&txPacket);
        Semaphore_post(ezlnkSem);

        txBursts++;
    }
}


