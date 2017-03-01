/*
 * opt3001.h
 *
 *  Created on: Feb 27, 2017
 *      Author: curew
 */

#ifndef OPT3001_H_
#define OPT3001_H_
#include <ti/devices/cc13x0/driverlib/i2c.h>
#include <ti/drivers/GPIO.h>
#include <Board.h>
#include <ti/drivers/I2C.h>
#include <stdint.h>
#include <unistd.h>
#include "LED.h"

/*Get TI ID*/
int get_TI_ID(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h);

/*set the config register - device will continuously measure light*/
int config(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h);

/*get value of config register*/
int get_config(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h);

/*get one light measurement - does NOT check if data is available*/
int get_Light(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h);

#endif /* OPT3001_H_ */
