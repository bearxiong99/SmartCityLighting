/*
 * sensor_light2.c
 *
 *  Created on: Feb 15, 2017
 *      Author: Justin Curewitz
 */
#include "Sensors.h"


static PIN_State motionPinState;
static PIN_Handle motionPinHandle;

/*Thread that runs the OPT3001 light sensor.*/
PIN_Config motionPinTable[] = {
    CC1310_LAUNCHXL_DIO21  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    CC1310_LAUNCHXL_DIO16_TDO | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};
    uint8_t         txBuffer[4];
    uint8_t         rxBuffer[4];
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;
    ADC_Handle adc;
    int motions;
    int light;
    int good_config;

void motionCallbackFxn(PIN_Handle handle, PIN_Id pinId) {
    if (pinId == 21) {
        CPUdelay(250);
        motions += 1;
    } else if (pinId == 16 && good_config) {
        light = get_Light(txBuffer, rxBuffer, i2cTransaction, i2c);
        uint16_t exp = (light >> 12)&0x000F;
        uint16_t mantissa = light & 0x0FFF;
        uint32_t lux = 0.01*(mantissa<<exp);
        if (lux < 50) {
            LampOn();
        } else {
            LampOff();
        }
    }
}
/*get interrupt from motion sensor*/
void initMotion(void){
    motions = 0;
    good_config = 0;
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

/*converts Sensor Struct to byte array*/
uint8_t* structToArray(SensorDataStruct* s){
    uint16_t temp_motions = s->motions;
    uint8_t* b = malloc(10*sizeof(uint8_t));
    uint16_t temp = 0;
    temp = s->temp;
    b[0] = (temp&0xFF00) >> 8;
    b[1] = temp&0x00FF;
    temp = s->humidity;
    b[2] = (temp&0xFF00) >> 8;
    b[3] = temp&0x00FF;
    temp = s->light;
    b[4] = (temp&0xFF00) >> 8;
    b[5] = temp&0x00FF;
    temp = s->amps;
    b[6] = (temp&0xFF00) >> 8;
    b[7] = temp&0x00FF;
    temp = temp_motions;
    b[8] = (temp&0xFF00) >> 8;
    b[9] = temp&0x00FF;
    free(s);
    return b;
}
/*fill packet with sensor data*/
SensorDataStruct* packageData(int temp, int humidity, int light, int amps, int motions) {
    SensorDataStruct* sp = malloc(sizeof(SensorData));
    sp->temp = temp;
    sp->humidity = humidity;
    sp->light = light;
    sp->amps = amps;
    sp->motions = motions;
    return sp;
}
/*main thread*/
void init_sensors(void){
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C0, &i2cParams);
    adc = a_init();
    toggleLED(0);
    toggleLED2(0);
}

void config_sensors(void) {
    light = 0;
    int id = get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);
    good_config = config(txBuffer, rxBuffer, i2cTransaction, i2c);
    setConfig(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    initMotion();
}

//void *sensor_light2(void *arg0) {
uint8_t* getMeasurements(void) {
    int z = 1;
//    int id = get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);
//    int good_config = config(txBuffer, rxBuffer, i2cTransaction, i2c);
//    setConfig(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    requestTemp(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
    int temp = 0;
    int hum = 0;
    //read light on loop
    while(1) {
        uint16_t adc_val = Check_Light(adc);
        if ((adc_val > 2335) && (lightOn() == 1)) {
            adc_val = 0;                     //light broken
        } else {
            adc_val = 1;                     //light functioning
        }
        toggleLED2(z);
        z = !z;
        light = get_Light(txBuffer, rxBuffer, i2cTransaction, i2c);
        if (temp == 0) {
            temp = getTemp(i2c, i2cTransaction, txBuffer, rxBuffer, DEFAULT_SLAVE);
            hum = (rxBuffer[2] << 8) + rxBuffer[3];
        }

        if (temp != 0 && light != 0){
            SensorDataStruct* sp = packageData(temp, hum, light, adc_val, motions);
            //uint8_t* arr = (uint8_t*) sp;
            uint8_t* toSend = structToArray(sp);
            motions = 0;
            return toSend;
        }

        toggleLED(z);
        //end of loop
    }
    //get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);

}
