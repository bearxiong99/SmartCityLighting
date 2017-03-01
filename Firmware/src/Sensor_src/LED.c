/*
 * LED.c
 *
 *  Created on: Feb 15, 2017
 *      Author: curew
 */
#include <LED.h>


void toggleLED(int on){
    if (on == 1) {
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
    } else {
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);
    }
}

/*toggles led2*/
void toggleLED2(int on){
    if (on == 1) {
        GPIO_write(Board_GPIO_LED2, Board_GPIO_LED_ON);
    } else {
        GPIO_write(Board_GPIO_LED2, Board_GPIO_LED_OFF);
    }
}
