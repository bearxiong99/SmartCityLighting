/*
 * sensor_light2.c
 *
 *  Created on: Feb 15, 2017
 *      Author: Justin Curewitz
 */
#include "Sensors.h"
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>


static PIN_State motionPinState;
static PIN_Handle motionPinHandle;

#define HDC1010_SLEEP_MS 20

/*Thread that runs the OPT3001 light sensor.*/
PIN_Config motionPinTable[] = {
    CC1310_LAUNCHXL_DIO12  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    CC1310_LAUNCHXL_DIO21  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};
    uint8_t         txBuffer[4];
    uint8_t         rxBuffer[4];
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;
    ADC_Handle adc;
    int motions;
    int good_config;

void motionCallbackFxn(PIN_Handle handle, PIN_Id pinId) {
    if (pinId == 21) {
        CPUdelay(250);
        motions += 1;
    }
}

/*get interrupt from motion sensor*/
void initMotion(void){
    motions = 0;
    motionPinHandle = PIN_open(&motionPinState, motionPinTable);
    if(!motionPinHandle) {
        //System_abort("Error initializing button pins\n");
        while(1){}
    }
    if (PIN_registerIntCb(motionPinHandle, &motionCallbackFxn) != 0) {
        //System_abort("Error registering button callback function");
        while(1);
    }
}

/*fill packet with sensor data*/
void packageData(uint16_t temp, uint16_t humidity, uint16_t light, uint16_t operational, uint16_t motions, SensorDataStruct *sp) {
    sp->temp = temp;
    sp->humidity = humidity;
    sp->light = light;
    sp->amps = operational;
    sp->motions = motions;
}

/* Call this before starting sysbios but after peripherals are init'd */
void init_sensors(void){
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C0, &i2cParams);
    adc = a_init();
    initMotion();
    good_config = 0;
}

void config_sensors(void) {
    int id = get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);
    good_config = config(txBuffer, rxBuffer, i2cTransaction, i2c);
    setConfig(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    //initMotion();
}

void getSensorData(SensorDataStruct *sensorStruct) {
    int z = 1;
    requestTemp(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    uint64_t timeout = ((unsigned long)HDC1010_SLEEP_MS * 1000L) / Clock_tickPeriod;
    Task_sleep(timeout);
    //read light on loop
    uint16_t adc_val = Check_Light(adc);
    if ((adc_val > 2335) && (lightOn() == 1)) {
        adc_val = 0;                     //light broken
    } else {
        adc_val = 1;                     //light functioning
    }
    z = !z;
    int configReg = get_config(txBuffer, rxBuffer, i2cTransaction, i2c);
    int light = get_Light(txBuffer, rxBuffer, i2cTransaction, i2c);
    uint16_t exp = (light >> 12)&0x000F;
    uint16_t mantissa = light & 0x0FFF;
    uint32_t lux = 0.01*(mantissa<<exp);
    if (lux < 50) {
        LampOn();
    } else {
        LampOff();
    }
    int temp = getTemp(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    int hum = (rxBuffer[2] << 8) + rxBuffer[3];

    packageData(temp, hum, light, adc_val, motions, sensorStruct);
    //motions = 0;

    motions = configReg;
}
