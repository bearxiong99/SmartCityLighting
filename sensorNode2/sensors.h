/*
 * sensors.h
 *
 *  Created on: Apr 10, 2017
 *      Author: Chris
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

// Fills sensorStruct with necessary sensor data
void getSensorData(SensorDataStruct *sensorStruct);


/*
 * sensors.h
 *
 *  Created on: Mar 5, 2017
 *      Author: curew
 */


uint8_t* structToArray(SensorDataStruct* s);
SensorDataStruct* packageData(int temp, int humidity, int light, int amps, int motions);
void init_sensors(void);
uint8_t* getMeasurements(void);



#endif /* SENSORS_H_ */

