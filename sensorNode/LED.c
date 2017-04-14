/*
 * LED.c
 *
 *  Created on: Feb 15, 2017
 *      Author: curew
 */
#include <LED.h>
#include <ti/drivers/PIN.h>
#include "CC1310_LAUNCHXL.h"
#include "opt3001.h"

/*PIN_Config ledPinTable[] = {
    Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW  | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};*/

PIN_Config lampTable[] = {CC1310_LAUNCHXL_DIO15};
PIN_Config motionTable[] = {CC1310_LAUNCHXL_DIO21, CC1310_LAUNCHXL_DIO22};
static PIN_State lampPinState;
static PIN_State motionPinState;
static PIN_Handle lampPinHandle;
static PIN_Handle motionPinHandle;

int on = 0;
void toggleLED(int on){
    if (on == 1) {
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
    } else {
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);
    }
}

void LampInit(void) {
    lampPinHandle = PIN_open(&lampPinState, lampTable);
    PIN_setOutputEnable(lampPinHandle, CC1310_LAUNCHXL_DIO15, 1);
}

void LampOn(void) {
    PIN_setOutputValue(lampPinHandle, CC1310_LAUNCHXL_DIO15, 0xFFFFFFFF);
    on = 1;
}

void LampOff(void) {
    PIN_setOutputValue(lampPinHandle, CC1310_LAUNCHXL_DIO15, 0);
    on = 0;
}

int lightOn(void) {
    return on;
}

void MotionDetected(PIN_Handle ph, PIN_Id pinID) {
    if (pinID == 0) {
        motions += 1;
    } else if (pinID == 1) {
        motions += 1;
    } else {
        motions += 1;
    }
}

void MotionInit(void){
    motionPinHandle = PIN_open(&motionPinState, motionTable);
    int success = PIN_registerIntCb(motionPinHandle, &MotionDetected);
    int motions = 0;
}



