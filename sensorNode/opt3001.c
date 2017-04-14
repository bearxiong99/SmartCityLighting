/*
 * opt3001.c
 *
 *  Created on: Feb 27, 2017
 *      Author: curew
 */
#include "opt3001.h"

/*Get TI ID*/
int get_TI_ID(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h) {
    txBuf[0] = 0x7E;
    i2c.writeBuf = txBuf;
    i2c.readBuf = rxBuf;
    i2c.readCount = 2;
    i2c.writeCount= 1;
    i2c.slaveAddress = 0x44;
    I2C_transfer(i2c_h, &i2c);
    return (rxBuf[0] << 8) + rxBuf[1];
}
/*Configure Measurement Mode for continuous operation*/
int config(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h) {
    txBuf[0] = 0x01;     //configuration register
    i2c.writeBuf = txBuf;
    i2c.readBuf = rxBuf;
    i2c.readCount = 2;
    i2c.writeCount= 1;
    i2c.slaveAddress = 0x44;
    if(I2C_transfer(i2c_h, &i2c)) {               //gets config register value
        uint16_t con = (rxBuf[0] << 8) | rxBuf[1];
        con = con & 0xF9FF; //clear bit 10 and bit 9
        con = con | 0x0600; //set bit 10 and bit 9   //friendly write
        i2c.writeCount = 3;
        i2c.readCount = 0;
        uint8_t conLSB = con&0xFF;
        uint8_t conMSB = (con>>8)&0xFF;
        txBuf[1] = conMSB; //msb first
        txBuf[2] = conLSB;  //lsb second
        return I2C_transfer(i2c_h, &i2c);  //write config register address, msb, lsb
    }
    return 0;
}
/*get config register*/
int get_config(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h){
    //txBuf[0] = 0x01;  //read address already set
    i2c.writeBuf = txBuf;
    i2c.readBuf = rxBuf;
    i2c.readCount = 2;
    i2c.writeCount= 0;
    i2c.slaveAddress = 0x44;
    I2C_transfer(i2c_h, &i2c);
    return (rxBuf[0] << 8) | rxBuf[1];
}
/*Get Light Measurement*/
int get_Light(uint8_t* txBuf, uint8_t* rxBuf, I2C_Transaction i2c, I2C_Handle i2c_h){
    txBuf[0] = 0x00;
    i2c.writeBuf = txBuf;
    i2c.readBuf = rxBuf;
    i2c.readCount = 2;
    i2c.writeCount= 1;
    i2c.slaveAddress = 0x44;
    I2C_transfer(i2c_h, &i2c);
    return (rxBuf[0] << 8) + rxBuf[1];
}



