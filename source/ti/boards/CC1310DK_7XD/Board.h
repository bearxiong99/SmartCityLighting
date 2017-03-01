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

#include <ti/drivers/ADC.h>
#include <ti/drivers/ADCBuf.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Watchdog.h>

#include "CC1310DK_7XD.h"

#define Board_initGeneral()     CC1310DK_7XD_initGeneral()

/* These #defines allow us to reuse TI-RTOS across other device families */

#define Board_3V3_EN            CC1310DK_7XD_3V3_EN

#define Board_ADC0              CC1310DK_7XD_ADCVDDS
#define Board_ADC1              CC1310DK_7XD_ADCALS

#define Board_ADCBUF0           CC1310DK_7XD_ADCBUF0
#define Board_ADCBUFCHANNEL0    0
#define Board_ADCBUFCHANNEL1    1

#define Board_ALS_PWR           CC1310DK_7XD_ALS_PWR

#define Board_CRYPTO0           CC1310DK_7XD_CRYPTO0

#define Board_DIO23_ANALOG      CC1310DK_7XD_DIO23_ANALOG
#define Board_DIO24_ANALOG      CC1310DK_7XD_DIO24_ANALOG
#define Board_DIO25_ANALOG      CC1310DK_7XD_DIO25_ANALOG
#define Board_DIO26_ANALOG      CC1310DK_7XD_DIO26_ANALOG
#define Board_DIO27_ANALOG      CC1310DK_7XD_DIO27_ANALOG
#define Board_DIO28_ANALOG      CC1310DK_7XD_DIO28_ANALOG
#define Board_DIO29_ANALOG      CC1310DK_7XD_DIO29_ANALOG
#define Board_DIO30_ANALOG      CC1310DK_7XD_DIO30_ANALOG

#define Board_GPIO_BUTTON0      CC1310DK_7XD_GPIO_S1
#define Board_GPIO_BUTTON1      CC1310DK_7XD_GPIO_S2
#define Board_GPIO_LED0         CC1310DK_7XD_GPIO_LED0
#define Board_GPIO_LED1         CC1310DK_7XD_GPIO_LED1
#define Board_GPIO_LED2         CC1310DK_7XD_GPIO_LED2
#define Board_GPIO_LED3         CC1310DK_7XD_GPIO_LED3
#define Board_GPIO_LED_ON       CC1310DK_7XD_GPIO_LED_ON
#define Board_GPIO_LED_OFF      CC1310DK_7XD_GPIO_LED_OFF

#define Board_GPTIMER0A         CC1310DK_7XD_GPTIMER0A
#define Board_GPTIMER0B         CC1310DK_7XD_GPTIMER0B
#define Board_GPTIMER1A         CC1310DK_7XD_GPTIMER1A
#define Board_GPTIMER1B         CC1310DK_7XD_GPTIMER1B
#define Board_GPTIMER2A         CC1310DK_7XD_GPTIMER2A
#define Board_GPTIMER2B         CC1310DK_7XD_GPTIMER2B
#define Board_GPTIMER3A         CC1310DK_7XD_GPTIMER3A
#define Board_GPTIMER3B         CC1310DK_7XD_GPTIMER3B

#define Board_KEY_SELECT        CC1310DK_7XD_KEY_SELECT
#define Board_KEY_UP            CC1310DK_7XD_KEY_UP
#define Board_KEY_DOWN          CC1310DK_7XD_KEY_DOWN
#define Board_KEY_LEFT          CC1310DK_7XD_KEY_LEFT
#define Board_KEY_RIGHT         CC1310DK_7XD_KEY_RIGHT

#define Board_LCD_CSN           CC1310DK_7XD_LCD_CSN
#define Board_LCD_MODE          CC1310DK_7XD_LCD_MODE
#define Board_LCD_RST           CC1310DK_7XD_LCD_RST

#define Board_PIN_BUTTON0       CC1310DK_7XD_KEY_UP
#define Board_PIN_BUTTON1       CC1310DK_7XD_KEY_DOWN
#define Board_PIN_LED0          CC1310DK_7XD_PIN_LED4
#define Board_PIN_LED1          CC1310DK_7XD_PIN_LED1
#define Board_PIN_LED2          CC1310DK_7XD_PIN_LED2
#define Board_PIN_LED3          CC1310DK_7XD_PIN_LED3
#define Board_PIN_LED4          CC1310DK_7XD_PIN_LED4

#define Board_PWM0              CC1310DK_7XD_PWM0
#define Board_PWM1              CC1310DK_7XD_PWM1
#define Board_PWM2              CC1310DK_7XD_PWM2
#define Board_PWM3              CC1310DK_7XD_PWM3
#define Board_PWM4              CC1310DK_7XD_PWM4
#define Board_PWM5              CC1310DK_7XD_PWM5
#define Board_PWM6              CC1310DK_7XD_PWM6
#define Board_PWM7              CC1310DK_7XD_PWM7

#define Board_SPI0              CC1310DK_7XD_SPI0
#define Board_SPI1              CC1310DK_7XD_SPI1

#define Board_UART0             CC1310DK_7XD_UART0

#define Board_UDMA0             CC1310DK_7XD_UDMA0

#define Board_WATCHDOG0         CC1310DK_7XD_WATCHDOG0

/*
 * These macros are provided for backwards compatibility.
 * Please use the <Driver>_init functions directly rather
 * than Board_init<Driver>.
 */
#define Board_initADC()         ADC_init()
#define Board_initADCBuf()      ADCBuf_init()
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
#define Board_LED2              Board_PIN_LED2
#define Board_LED3              Board_PIN_LED3
#define Board_LED4              Board_PIN_LED0
#define Board_LED_ON            Board_GPIO_LED_ON
#define Board_LED_OFF           Board_GPIO_LED_OFF

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
