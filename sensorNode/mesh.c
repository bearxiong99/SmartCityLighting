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

#include <stdio.h>
#include <stdlib.h>
/***** Defines *****/

#define RFEASYLINKEX_TASK_STACK_SIZE 1024
#define RFEASYLINKEX_TASK_PRIORITY   4

#define PINGPARENT_TASK_STACK_SIZE 1024
#define PINGPARENT_TASK_PRIORITY   2

#define SENSOR_TASK_STACK_SIZE 1024
#define SENSOR_TASK_PRIORITY   3



/***** Variable declarations *****/
static uint8_t rxTaskStack[RFEASYLINKEX_TASK_STACK_SIZE];
static uint8_t pingParentTaskStack[PINGPARENT_TASK_STACK_SIZE];
static uint8_t sensorTaskStack[SENSOR_TASK_STACK_SIZE];
Task_Handle pingParentTask;    /* not static so you can see in ROV */
Task_Handle rxTask;    /* not static so you can see in ROV */
Task_Handle sensorTask;    /* not static so you can see in ROV */
bool pingConfReceived;
Semaphore_Handle ezlnkSem;
Semaphore_Handle pingConfSem;
Semaphore_Handle nodeSem;
/***** Node variables *****/
nodeInfo node;
const address defaultAddress = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

#define _DEBUGGING_
#ifdef _DEBUGGING_
#define DbgPrint_printf System_printf
#else
#define DbgPrint_printf
#endif

void txPayload(packetType type, uint8_t *payload, uint8_t len, uint8_t *dstAddr);
void pingParentTask_init();
bool createChildAddress(address* address);

void receivedParentalPing(ParentalPingStruct *p) {
    ReceiptConfirmationStruct r;
    r.t = ParentalPing;
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

    while(node.own_address.addr[childBitShift/8] << (childBitShift % 8)) { // if our address isn't all 0s yet
        childBitShift += 2;
    }

    for(i = 0; i < childBitShift; i++) {
        address->addr[i] = node.own_address.addr[i];
    }
    if(node.hasChildOne) {
        childBits = 0x01;
        success = true;
    }
    else if(node.hasChildTwo) {
        childBits = 0x10;
        success = true;
    }
    else if(node.hasChildThree) {
        childBits = 0x11;
        success = true;
    }
    else {
        success = false;
    }

    address->addr[childBitShift/8 + 1] = node.own_address.addr[childBitShift/8+1] & (childBits << (childBitShift % 8));

    Semaphore_post(nodeSem);
    return success;
}


static void sensorFnx(UArg arg0, UArg arg1) {
    SensorDataStruct sensors;
    getSensorData(&sensors);
    txPayload(SensorData, (uint8_t*) &sensors, sizeof(SensorDataStruct), &node.parent_address.addr[0]); // Send sensor data to parent
}

static void pingParentFnx(UArg arg0, UArg arg1)
{
    System_printf("Entered TX task\n");
    System_flush();
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
            for(i = 0; i < 8; i++) {
                node.own_address.addr[i] = DEFAULT_NODE_ADDRESS;
            }
            Semaphore_post(nodeSem);

        }
        // add send ping, wait for response, etc.
        for(i = 0; i < 8; i++) {
            ping.childAddress.addr[i] = node.own_address.addr[i];
        }
        txPayload(ParentalPing, (uint8_t*) &ping, sizeof(ParentalPingStruct), &node.own_address.addr[0]); // Send ping
    }
}

static void rfEasyLinkRxFnx(UArg arg0, UArg arg1)
{
    EasyLink_init(EasyLink_Phy_Custom);

    pingParentTask_init();

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

    EasyLink_enableRxAddrFilter(&node.own_address.addr[0], 8, 1);

    while(true) {
        Semaphore_pend(ezlnkSem, BIOS_WAIT_FOREVER);
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
                // Case for each kind of message
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

    for(i = 0; i < 8; i++) {
        node.own_address.addr[i] = DEFAULT_NODE_ADDRESS;
        node.parent_address.addr[i] = DEFAULT_NODE_ADDRESS;
    }

    node.inNetwork = false;

    rxTask_init(); // pingParentTask_init called from inside rx task;
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


