/*
 * HDC1010.c
 *
 *  Created on: Mar 3, 2017
 *      Author: Justin Curewitz
 */


#include "HDC1010.h"

int getTIid(I2C_Handle i2c, I2C_Transaction config, uint8_t* txBuf, uint8_t* rxBuf, int slave_address) {
    config.slaveAddress = slave_address;
    config.writeBuf = txBuf;
    config.readBuf = rxBuf;
    config.readCount = 2;
    config.writeCount = 1;
    txBuf[0] = 0xFE;
    I2C_transfer(i2c, &config);
    return (rxBuf[0] << 8) + rxBuf[1];
}
int getConfig(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address){
    temp.slaveAddress = slave_address;
    temp.writeBuf = txBuf;
    temp.readBuf = rxBuf;
    temp.readCount = 2;
    temp.writeCount = 1;
    txBuf[0] = 0x2;
    I2C_transfer(i2c, &temp);
    return (rxBuf[0] << 8) + rxBuf[1];
}
void setConfig(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address){
    temp.slaveAddress = slave_address;
    temp.writeBuf = txBuf;
    temp.readBuf = rxBuf;
    temp.readCount = 0;
    temp.writeCount = 2;
    txBuf[0] = 0x2;
    txBuf[1] = 0x00;
    txBuf[2] = 0x00;
    I2C_transfer(i2c, &temp);
}
void requestTemp(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address) {
    temp.slaveAddress = slave_address;
    temp.writeBuf = txBuf;
    txBuf[0] = 0x00;
    temp.writeCount = 1;
    temp.readCount = 0;
    temp.readBuf = rxBuf;
    I2C_transfer(i2c, &temp);
}
int getTemp(I2C_Handle i2c, I2C_Transaction temp, uint8_t* txBuf, uint8_t* rxBuf, int slave_address) {
    temp.slaveAddress = slave_address;
    temp.writeBuf = txBuf;
    txBuf[0] = 0x00;
    temp.readBuf = rxBuf;
    temp.readCount = 2;
    temp.writeCount = 0;
    I2C_transfer(i2c, &temp);
    return (rxBuf[0] << 8) + rxBuf[1];
}

