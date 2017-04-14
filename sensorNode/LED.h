/*
 * LED.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Justin Curewitz
 */

#ifndef LED_H_
#define LED_H_
#include <ti/drivers/GPIO.h>
#include <Board.h>

extern int motions;

void toggleLED(int on);

void toggleLED2(int on);

void LampOn(void);

void LampOff(void);

void LampInit(void);

int lightOn(void);

void MotionInit(void);

void MotionDetected(PIN_Handle ph, PIN_Id pinID);
#endif /* LED_H_ */
