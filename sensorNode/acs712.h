/*
 * acs712.h
 *
 *  Created on: Feb 27, 2017
 *      Author: curew
 */

#ifndef ACS712_H_
#define ACS712_H_

#include <ti/devices/cc13x0/driverlib/i2c.h>
#include <ti/drivers/ADC.h>
#include <Board.h>
#include <ti/drivers/I2C.h>
#include <stdint.h>
#include "LED.h"
#include <unistd.h>


/*Prepare all Hardware thread will use*/
ADC_Handle a_init(void);

/*Handle GPIO Signal*/
uint16_t Check_Light(ADC_Handle adc);

#endif /* ACS712_H_ */
