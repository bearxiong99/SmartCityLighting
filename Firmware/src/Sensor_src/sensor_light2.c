/*
 * sensor_light2.c
 *
 *  Created on: Feb 15, 2017
 *      Author: Justin Curewitz
 */

/*Thread that runs the OPT3001 light sensor.*/


#include <ti/devices/cc13x0/driverlib/i2c.h>
#include <ti/drivers/GPIO.h>
#include <Board.h>
#include <ti/drivers/I2C.h>
#include <stdint.h>
#include <unistd.h>
#include "LED.h"
#include "opt3001.h"
#include "packets.h"
#include <stdlib.h>
#include "acs712.h"

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

void *sensor_light2(void *arg0) {
    uint8_t         txBuffer[4];
    uint8_t         rxBuffer[2];
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;
    int id = 0;
    int light = 0;
    uint16_t config_val = 0;
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C0, &i2cParams);
    ADC_Handle adc = a_init();
    int z = 1;
    id = get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);
    toggleLED(0);
    toggleLED2(0);
    if(config(txBuffer, rxBuffer, i2cTransaction, i2c)) {
        toggleLED(1);
        toggleLED2(1);
    }
    //read light on loop
    while(1) {
        config_val = get_config(txBuffer, rxBuffer, i2cTransaction, i2c);
        if (config_val & 0x0080) {
            light = get_Light(txBuffer, rxBuffer, i2cTransaction, i2c);
        }
        uint16_t adc_val = Check_Light(adc);
        SensorDataStruct* sp = packageData(0, 0, light, adc_val, 0);
        if (light) {
            light = 0;
        }
        toggleLED2(z);
        z = !z;
        sleep(1);
    }
    //get_TI_ID(txBuffer, rxBuffer, i2cTransaction, i2c);

}
