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
/** ============================================================================
 *  @file       CC2650DK_7ID.h
 *
 *  @brief      CC2650DK_7ID Board Specific header file.
 *
 *  The CC2650DK_7ID header file should be included in an application as
 *  follows:
 *  @code
 *  #include "CC2650DK_7ID.h"
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __CC2650DK_7ID_BOARD_H__
#define __CC2650DK_7ID_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc26x0/driverlib/ioc.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
#define CC2650DK_7ID
/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                <pin mapping>
 */

/* Accelerometer */
#define CC2650DK_7ID_ACC_PWR                       IOID_20         /* P2.8 */
#define CC2650DK_7ID_ACC_CSN                       IOID_24         /* P2.10 */

/* Ambient Light Sensor */
#define CC2650DK_7ID_ALS_OUT                       IOID_23         /* P2.5 */
#define CC2650DK_7ID_ALS_PWR                       IOID_26         /* P2.6 */

/* Analog Capable DIO's */
#define CC2650DK_7ID_DIO23_ANALOG                  IOID_23
#define CC2650DK_7ID_DIO24_ANALOG                  IOID_24
#define CC2650DK_7ID_DIO25_ANALOG                  IOID_25
#define CC2650DK_7ID_DIO26_ANALOG                  IOID_26
#define CC2650DK_7ID_DIO27_ANALOG                  IOID_27
#define CC2650DK_7ID_DIO28_ANALOG                  IOID_28
#define CC2650DK_7ID_DIO29_ANALOG                  IOID_29
#define CC2650DK_7ID_DIO30_ANALOG                  IOID_30

/* Button Board */
#define CC2650DK_7ID_KEY_SELECT                    IOID_11         /* P1.14 */
#define CC2650DK_7ID_KEY_UP                        IOID_19         /* P1.10 */
#define CC2650DK_7ID_KEY_DOWN                      IOID_12         /* P1.12 */
#define CC2650DK_7ID_KEY_LEFT                      IOID_15         /* P1.6  */
#define CC2650DK_7ID_KEY_RIGHT                     IOID_18         /* P1.8  */

/* GPIO */
#define CC2650DK_7ID_GPIO_LED_ON                   1
#define CC2650DK_7ID_GPIO_LED_OFF                  0

/* LEDs */
#define CC2650DK_7ID_PIN_LED_ON                     1
#define CC2650DK_7ID_PIN_LED_OFF                    0
#define CC2650DK_7ID_PIN_LED1                       IOID_25         /* P2.11 */
#define CC2650DK_7ID_PIN_LED2                       IOID_27         /* P2.13 */
#define CC2650DK_7ID_PIN_LED3                       IOID_7          /* P1.2  */
#define CC2650DK_7ID_PIN_LED4                       IOID_6          /* P1.4  */

/* LCD  Board */
#define CC2650DK_7ID_LCD_MODE                      IOID_4          /* P1.11 */
#define CC2650DK_7ID_LCD_RST                       IOID_5          /* P1.13 */
#define CC2650DK_7ID_LCD_CSN                       IOID_14         /* P1.17 */

/* SD Card */
#define CC2650DK_7ID_SDCARD_CSN                    IOID_30         /* P2.12 */

/* SPI Board */
#define CC2650DK_7ID_SPI0_MISO                     IOID_8          /* P1.20 */
#define CC2650DK_7ID_SPI0_MOSI                     IOID_9          /* P1.18 */
#define CC2650DK_7ID_SPI0_CLK                      IOID_10         /* P1.16 */
#define CC2650DK_7ID_SPI0_CSN                      PIN_UNASSIGNED  /* P1.14, separate CSn for LCD, SDCARD, and ACC */
#define CC2650DK_7ID_SPI1_MISO                     IOID_24         /* RF2.10 for testing only */
#define CC2650DK_7ID_SPI1_MOSI                     IOID_23         /* RF2.5  for testing only */
#define CC2650DK_7ID_SPI1_CLK                      IOID_30         /* RF2.12 for testing only */
#define CC2650DK_7ID_SPI1_CSN                      PIN_UNASSIGNED  /* RF2.6  for testing only */

/* Power Board */
#define CC2650DK_7ID_3V3_EN                        IOID_13         /* P1.15 */

/* PWM Outputs */
#define CC2650DK_7ID_PWMPIN0                       CC2650DK_7ID_PIN_LED1
#define CC2650DK_7ID_PWMPIN1                       CC2650DK_7ID_PIN_LED2
#define CC2650DK_7ID_PWMPIN2                       PIN_UNASSIGNED
#define CC2650DK_7ID_PWMPIN3                       PIN_UNASSIGNED
#define CC2650DK_7ID_PWMPIN4                       PIN_UNASSIGNED
#define CC2650DK_7ID_PWMPIN5                       PIN_UNASSIGNED
#define CC2650DK_7ID_PWMPIN6                       PIN_UNASSIGNED
#define CC2650DK_7ID_PWMPIN7                       PIN_UNASSIGNED

/* UART Board */
#define CC2650DK_7ID_UART_RX                       IOID_2          /* P1.7 */
#define CC2650DK_7ID_UART_TX                       IOID_3          /* P1.9 */
#define CC2650DK_7ID_UART_CTS                      IOID_0          /* P1.3 */
#define CC2650DK_7ID_UART_RTS                      IOID_21         /* P2.18 */

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC2650DK_7ID_initGeneral(void);

/*!
 *  @def    CC2650DK_7ID_ADCBufName
 *  @brief  Enum of ADCBufs
 */
typedef enum CC2650DK_7ID_ADCBufName {
    CC2650DK_7ID_ADCBUF0 = 0,

    CC2650DK_7ID_ADCBUFCOUNT
} CC2650DK_7ID_ADCBufName;

/*!
 *  @def    CC2650DK_7ID_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum CC2650DK_7ID_ADCName {
    CC2650DK_7ID_ADCALS = 0,
    CC2650DK_7ID_ADCDCOUPL,
    CC2650DK_7ID_ADCVSS,
    CC2650DK_7ID_ADCVDDS,

    CC2650DK_7ID_ADCCOUNT
} CC2650DK_7ID_ADCName;

/*!
 *  @def    CC2650DK_7ID_CryptoName
 *  @brief  Enum of Crypto names
 */
typedef enum CC2650DK_7ID_CryptoName {
    CC2650DK_7ID_CRYPTO0 = 0,

    CC2650DK_7ID_CRYPTOCOUNT
} CC2650DK_7ID_CryptoName;

/*!
 *  @def    CC2650DK_7ID_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC2650DK_7ID_GPIOName {
    CC2650DK_7ID_GPIO_S1 = 0,
    CC2650DK_7ID_GPIO_S2,
    CC2650DK_7ID_GPIO_LED0,
    CC2650DK_7ID_GPIO_LED1,
    CC2650DK_7ID_GPIO_LED2,
    CC2650DK_7ID_GPIO_LED3,

    CC2650DK_7ID_GPIOCOUNT
} CC2650DK_7ID_GPIOName;

/*!
 *  @def    CC2650DK_7ID_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum CC2650DK_7ID_GPTimerName {
    CC2650DK_7ID_GPTIMER0A = 0,
    CC2650DK_7ID_GPTIMER0B,
    CC2650DK_7ID_GPTIMER1A,
    CC2650DK_7ID_GPTIMER1B,
    CC2650DK_7ID_GPTIMER2A,
    CC2650DK_7ID_GPTIMER2B,
    CC2650DK_7ID_GPTIMER3A,
    CC2650DK_7ID_GPTIMER3B,

    CC2650DK_7ID_GPTIMERPARTSCOUNT
} CC2650DK_7ID_GPTimerName;

/*!
 *  @def    CC2650DK_7ID_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum CC2650DK_7ID_GPTimers {
    CC2650DK_7ID_GPTIMER0 = 0,
    CC2650DK_7ID_GPTIMER1,
    CC2650DK_7ID_GPTIMER2,
    CC2650DK_7ID_GPTIMER3,

    CC2650DK_7ID_GPTIMERCOUNT
} CC2650DK_7ID_GPTimers;

/*!
 *  @def    CC2650DK_7ID_PWM
 *  @brief  Enum of PWM outputs
 */
typedef enum CC2650DK_7ID_PWMName {
    CC2650DK_7ID_PWM0 = 0,
    CC2650DK_7ID_PWM1,
    CC2650DK_7ID_PWM2,
    CC2650DK_7ID_PWM3,
    CC2650DK_7ID_PWM4,
    CC2650DK_7ID_PWM5,
    CC2650DK_7ID_PWM6,
    CC2650DK_7ID_PWM7,

    CC2650DK_7ID_PWMCOUNT
} CC2650DK_7ID_PWMName;

/*!
 *  @def    CC2650DK_7ID_SPIName
 *  @brief  Enum of SPI names
 */
typedef enum CC2650DK_7ID_SPIName {
    CC2650DK_7ID_SPI0 = 0,
    CC2650DK_7ID_SPI1,

    CC2650DK_7ID_SPICOUNT
} CC2650DK_7ID_SPIName;

/*!
 *  @def    CC2650DK_7ID_UARTName
 *  @brief  Enum of UARTs
 */
typedef enum CC2650DK_7ID_UARTName {
    CC2650DK_7ID_UART0 = 0,

    CC2650DK_7ID_UARTCOUNT
} CC2650DK_7ID_UARTName;

/*!
 *  @def    CC2650DK_7ID_UDMAName
 *  @brief  Enum of DMA buffers
 */
typedef enum CC2650DK_7ID_UDMAName {
    CC2650DK_7ID_UDMA0 = 0,

    CC2650DK_7ID_UDMACOUNT
} CC2650DK_7ID_UDMAName;

/*!
 *  @def    CC2650DK_7ID_WatchdogName
 *  @brief  Enum of Watchdogs
 */
typedef enum CC2650DK_7ID_WatchdogName {
    CC2650DK_7ID_WATCHDOG0 = 0,

    CC2650DK_7ID_WATCHDOGCOUNT
} CC2650DK_7ID_WatchdogName;

#ifdef __cplusplus
}
#endif

#endif /* __CC2650DK_7ID_BOARD_H__ */
