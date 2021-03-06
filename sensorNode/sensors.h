/*
 * sensors.h
 *
 *  Created on: Mar 5, 2017
 *      Author: curew
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <ti/drivers/GPIO.h>
#include <Board.h>
#include <ti/drivers/I2C.h>
#include <stdint.h>
#include <ti/drivers/PIN.h>
//#include <unistd.h>
#include "LED.h"
#include "opt3001.h"
#include "packets.h"
#include <stdlib.h>
#include "acs712.h"
#include "HDC1010.h"

uint8_t* structToArray(SensorDataStruct* s);
void packageData(uint16_t temp, uint16_t humidity, uint16_t light, uint16_t operational, uint16_t motions, SensorDataStruct *sensorStruct);
void init_sensors(void);
void getSensorData(SensorDataStruct *sensorStruct);
void start_sensors(void);





#endif /* SENSORS_H_ */
