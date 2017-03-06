/*
 * HDC1010.h
 *
 *  Created on: Feb 8, 2017
 *      Author: Justin Curewitz
 */
#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>
#include <Board.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#ifndef HDC1010_H_
#define HDC1010_H_
#define HDCTEMP 0x00
#define HDCHUMIDITY 0x01
#define HDCCONFIG 0x02
#define TEMP 0x0000
#define DEFAULT_SLAVE 0x40

int getTIid(I2C_Handle i2c, I2C_Transaction config, uint8_t* txBuf, uint8_t* rxBuf, int slave_address);
int getConfig(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address);
void setConfig(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address);
void requestTemp(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address);
int getTemp(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address);



#endif /* HDC1010_H_ */
