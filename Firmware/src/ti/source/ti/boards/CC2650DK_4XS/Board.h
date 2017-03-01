/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Watchdog.h>

#include "CC2650DK_4XS.h"

#define Board_initGeneral()     CC2650DK_4XS_initGeneral()

/* These #defines allow us to reuse TI-RTOS across other device families */

#define Board_3V3_EN            CC2650DK_4XS_3V3_EN

#define Board_CRYPTO0           CC2650DK_4XS_CRYPTO0

#define Board_GPIO_BUTTON0      CC2650DK_4XS_GPIO_S1
#define Board_GPIO_BUTTON1      CC2650DK_4XS_GPIO_S2
#define Board_GPIO_LED0         CC2650DK_4XS_GPIO_LED0
#define Board_GPIO_LED1         CC2650DK_4XS_GPIO_LED1
#define Board_GPIO_LED2         CC2650DK_4XS_GPIO_LED0
#define Board_GPIO_LED_ON       CC2650DK_4XS_GPIO_LED_ON
#define Board_GPIO_LED_OFF      CC2650DK_4XS_GPIO_LED_OFF

#define Board_GPTIMER0A         CC2650DK_4XS_GPTIMER0A
#define Board_GPTIMER0B         CC2650DK_4XS_GPTIMER0B
#define Board_GPTIMER1A         CC2650DK_4XS_GPTIMER1A
#define Board_GPTIMER1B         CC2650DK_4XS_GPTIMER1B
#define Board_GPTIMER2A         CC2650DK_4XS_GPTIMER2A
#define Board_GPTIMER2B         CC2650DK_4XS_GPTIMER2B
#define Board_GPTIMER3A         CC2650DK_4XS_GPTIMER3A
#define Board_GPTIMER3B         CC2650DK_4XS_GPTIMER3B

#define Board_KEY_DOWN          CC2650DK_4XS_KEY_DOWN
#define Board_KEY_LEFT          CC2650DK_4XS_KEY_LEFT
#define Board_KEY_RIGHT         CC2650DK_4XS_KEY_RIGHT
#define Board_KEY_SELECT        CC2650DK_4XS_KEY_SELECT
#define Board_KEY_UP            CC2650DK_4XS_KEY_UP

#define Board_LCD_CSN           CC2650DK_4XS_LCD_CSN
#define Board_LCD_MODE          CC2650DK_4XS_LCD_MODE
#define Board_LCD_RST           CC2650DK_4XS_LCD_RST

#define Board_PIN_BUTTON0       CC2650DK_4XS_KEY_UP
#define Board_PIN_BUTTON1       CC2650DK_4XS_KEY_DOWN
#define Board_PIN_BUTTON2       CC2650DK_4XS_KEY_SELECT
#define Board_PIN_LED0          CC2650DK_4XS_PIN_LED3
#define Board_PIN_LED1          CC2650DK_4XS_PIN_LED4
#define Board_PIN_LED2          CC2650DK_4XS_PIN_LED3

#define Board_PWM0              CC2650DK_4XS_PWM0
#define Board_PWM1              CC2650DK_4XS_PWM1
#define Board_PWM2              CC2650DK_4XS_PWM2
#define Board_PWM3              CC2650DK_4XS_PWM3
#define Board_PWM4              CC2650DK_4XS_PWM4
#define Board_PWM5              CC2650DK_4XS_PWM5
#define Board_PWM6              CC2650DK_4XS_PWM6
#define Board_PWM7              CC2650DK_4XS_PWM7

#define Board_SPI0              CC2650DK_4XS_SPI0

#define Board_UART0             CC2650DK_4XS_UART0

#define Board_WATCHDOG0         CC2650DK_4XS_WATCHDOG0

/*
 * These macros are provided for backwards compatibility.
 * Please use the <Driver>_init functions directly rather
 * than Board_init<Driver>.
 */
#define Board_initGPIO()        GPIO_init()
#define Board_initPWM()         PWM_init()
#define Board_initSPI()         SPI_init()
#define Board_initUART()        UART_init()
#define Board_initWatchdog()    Watchdog_init()

/*
 * These macros are provided for backwards compatibility.
 * Please use the 'Board_PIN_xxx' macros to differentiate
 * them from the 'Board_GPIO_xxx' macros.
 */
#define Board_BUTTON0           Board_PIN_BUTTON0
#define Board_BUTTON1           Board_PIN_BUTTON1
#define Board_LED0              Board_PIN_LED0
#define Board_LED1              Board_PIN_LED1
#define Board_LED2              Board_PIN_LED0
#define Board_LED_ON            Board_GPIO_LED_ON
#define Board_LED_OFF           Board_GPIO_LED_OFF

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
