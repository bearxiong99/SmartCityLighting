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
 *  @file       CC2650_LAUNCHXL.h
 *
 *  @brief      CC2650 LaunchPad Board Specific header file.
 *
 *  The CC2650_LAUNCHXL header file should be included in an application as
 *  follows:
 *  @code
 *  #include "CC2650_LAUNCHXL.h"
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __CC2650_LAUNCHXL_BOARD_H__
#define __CC2650_LAUNCHXL_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc26x0/driverlib/ioc.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
#define CC2650_LAUNCHXL

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                  <pin mapping>
 */

/* Analog Capable DIOs */
#define CC2650_LAUNCHXL_DIO23_ANALOG          IOID_23
#define CC2650_LAUNCHXL_DIO24_ANALOG          IOID_24
#define CC2650_LAUNCHXL_DIO25_ANALOG          IOID_25
#define CC2650_LAUNCHXL_DIO26_ANALOG          IOID_26
#define CC2650_LAUNCHXL_DIO27_ANALOG          IOID_27
#define CC2650_LAUNCHXL_DIO28_ANALOG          IOID_28
#define CC2650_LAUNCHXL_DIO29_ANALOG          IOID_29
#define CC2650_LAUNCHXL_DIO30_ANALOG          IOID_30

/* Digital IOs */
#define CC2650_LAUNCHXL_DIO0                  IOID_0
#define CC2650_LAUNCHXL_DIO1_RFSW             IOID_1
#define CC2650_LAUNCHXL_DIO12                 IOID_12
#define CC2650_LAUNCHXL_DIO15                 IOID_15
#define CC2650_LAUNCHXL_DIO16_TDO             IOID_16
#define CC2650_LAUNCHXL_DIO17_TDI             IOID_17
#define CC2650_LAUNCHXL_DIO21                 IOID_21
#define CC2650_LAUNCHXL_DIO22                 IOID_22

/* Discrete Inputs */
#define CC2650_LAUNCHXL_PIN_BTN1              IOID_13
#define CC2650_LAUNCHXL_PIN_BTN2              IOID_14

/* GPIO */
#define CC2650_LAUNCHXL_GPIO_LED_ON           1
#define CC2650_LAUNCHXL_GPIO_LED_OFF          0

/* I2C */
#define CC2650_LAUNCHXL_I2C0_SCL0             IOID_4
#define CC2650_LAUNCHXL_I2C0_SDA0             IOID_5

/* LCD (430BOOST - Sharp96 Rev 1.1) */
#define CC2650_LAUNCHXL_LCD_CS                IOID_24 /* SPI chip select */
#define CC2650_LAUNCHXL_LCD_EXTCOMIN          IOID_12 /* External COM inversion */
#define CC2650_LAUNCHXL_LCD_ENABLE            IOID_22 /* LCD enable */
#define CC2650_LAUNCHXL_LCD_POWER             IOID_23 /* LCD power control */
#define CC2650_LAUNCHXL_LCD_CS_ON             1
#define CC2650_LAUNCHXL_LCD_CS_OFF            0

/* LEDs */
#define CC2650_LAUNCHXL_PIN_LED_ON            1
#define CC2650_LAUNCHXL_PIN_LED_OFF           0
#define CC2650_LAUNCHXL_PIN_RLED              IOID_6
#define CC2650_LAUNCHXL_PIN_GLED              IOID_7

/* PWM Outputs */
#define CC2650_LAUNCHXL_PWMPIN0               CC2650_LAUNCHXL_PIN_RLED
#define CC2650_LAUNCHXL_PWMPIN1               CC2650_LAUNCHXL_PIN_GLED
#define CC2650_LAUNCHXL_PWMPIN2               PIN_UNASSIGNED
#define CC2650_LAUNCHXL_PWMPIN3               PIN_UNASSIGNED
#define CC2650_LAUNCHXL_PWMPIN4               PIN_UNASSIGNED
#define CC2650_LAUNCHXL_PWMPIN5               PIN_UNASSIGNED
#define CC2650_LAUNCHXL_PWMPIN6               PIN_UNASSIGNED
#define CC2650_LAUNCHXL_PWMPIN7               PIN_UNASSIGNED

/* SPI */
#define CC2650_LAUNCHXL_SPI_FLASH_CS          IOID_20
#define CC2650_LAUNCHXL_FLASH_CS_ON           0
#define CC2650_LAUNCHXL_FLASH_CS_OFF          1

/* SPI Board */
#define CC2650_LAUNCHXL_SPI0_MISO             IOID_8          /* RF1.20 */
#define CC2650_LAUNCHXL_SPI0_MOSI             IOID_9          /* RF1.18 */
#define CC2650_LAUNCHXL_SPI0_CLK              IOID_10         /* RF1.16 */
#define CC2650_LAUNCHXL_SPI0_CSN              PIN_UNASSIGNED
#define CC2650_LAUNCHXL_SPI1_MISO             PIN_UNASSIGNED
#define CC2650_LAUNCHXL_SPI1_MOSI             PIN_UNASSIGNED
#define CC2650_LAUNCHXL_SPI1_CLK              PIN_UNASSIGNED
#define CC2650_LAUNCHXL_SPI1_CSN              PIN_UNASSIGNED

/* UART Board */
#define CC2650_LAUNCHXL_UART_RX               IOID_2          /* RXD */
#define CC2650_LAUNCHXL_UART_TX               IOID_3          /* TXD */
#define CC2650_LAUNCHXL_UART_CTS              IOID_19         /* CTS */
#define CC2650_LAUNCHXL_UART_RTS              IOID_18         /* RTS */

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC2650_LAUNCHXL_initGeneral(void);

/*!
 *  @def    CC2650_LAUNCHXL_ADCBufName
 *  @brief  Enum of ADCs
 */
typedef enum CC2650_LAUNCHXL_ADCBufName {
    CC2650_LAUNCHXL_ADCBUF0 = 0,

    CC2650_LAUNCHXL_ADCBUFCOUNT
} CC2650_LAUNCHXL_ADCBufName;

/*!
 *  @def    CC2650_LAUNCHXL_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum CC2650_LAUNCHXL_ADCName {
    CC2650_LAUNCHXL_ADC0 = 0,
    CC2650_LAUNCHXL_ADC1,
    CC2650_LAUNCHXL_ADC2,
    CC2650_LAUNCHXL_ADC3,
    CC2650_LAUNCHXL_ADC4,
    CC2650_LAUNCHXL_ADC5,
    CC2650_LAUNCHXL_ADC6,
    CC2650_LAUNCHXL_ADC7,
    CC2650_LAUNCHXL_ADCDCOUPL,
    CC2650_LAUNCHXL_ADCVSS,
    CC2650_LAUNCHXL_ADCVDDS,

    CC2650_LAUNCHXL_ADCCOUNT
} CC2650_LAUNCHXL_ADCName;

/*!
 *  @def    CC2650_LAUNCHXL_CryptoName
 *  @brief  Enum of Crypto names
 */
typedef enum CC2650_LAUNCHXL_CryptoName {
    CC2650_LAUNCHXL_CRYPTO0 = 0,

    CC2650_LAUNCHXL_CRYPTOCOUNT
} CC2650_LAUNCHXL_CryptoName;

/*!
 *  @def    CC2650_LAUNCHXL_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC2650_LAUNCHXL_GPIOName {
    CC2650_LAUNCHXL_GPIO_S1 = 0,
    CC2650_LAUNCHXL_GPIO_S2,
    CC2650_LAUNCHXL_GPIO_LED_GREEN,
    CC2650_LAUNCHXL_GPIO_LED_RED,

    CC2650_LAUNCHXL_GPIOCOUNT
} CC2650_LAUNCHXL_GPIOName;

/*!
 *  @def    CC2650_LAUNCHXL_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum CC2650_LAUNCHXL_GPTimerName {
    CC2650_LAUNCHXL_GPTIMER0A = 0,
    CC2650_LAUNCHXL_GPTIMER0B,
    CC2650_LAUNCHXL_GPTIMER1A,
    CC2650_LAUNCHXL_GPTIMER1B,
    CC2650_LAUNCHXL_GPTIMER2A,
    CC2650_LAUNCHXL_GPTIMER2B,
    CC2650_LAUNCHXL_GPTIMER3A,
    CC2650_LAUNCHXL_GPTIMER3B,

    CC2650_LAUNCHXL_GPTIMERPARTSCOUNT
} CC2650_LAUNCHXL_GPTimerName;

/*!
 *  @def    CC2650_LAUNCHXL_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum CC2650_LAUNCHXL_GPTimers {
    CC2650_LAUNCHXL_GPTIMER0 = 0,
    CC2650_LAUNCHXL_GPTIMER1,
    CC2650_LAUNCHXL_GPTIMER2,
    CC2650_LAUNCHXL_GPTIMER3,

    CC2650_LAUNCHXL_GPTIMERCOUNT
} CC2650_LAUNCHXL_GPTimers;

/*!
 *  @def    CC2650_LAUNCHXL_I2CName
 *  @brief  Enum of I2C names
 */
typedef enum CC2650_LAUNCHXL_I2CName {
    CC2650_LAUNCHXL_I2C0 = 0,

    CC2650_LAUNCHXL_I2CCOUNT
} CC2650_LAUNCHXL_I2CName;

/*!
 *  @def    CC2650_LAUNCHXL_PWM
 *  @brief  Enum of PWM outputs
 */
typedef enum CC2650_LAUNCHXL_PWMName {
    CC2650_LAUNCHXL_PWM0 = 0,
    CC2650_LAUNCHXL_PWM1,
    CC2650_LAUNCHXL_PWM2,
    CC2650_LAUNCHXL_PWM3,
    CC2650_LAUNCHXL_PWM4,
    CC2650_LAUNCHXL_PWM5,
    CC2650_LAUNCHXL_PWM6,
    CC2650_LAUNCHXL_PWM7,

    CC2650_LAUNCHXL_PWMCOUNT
} CC2650_LAUNCHXL_PWMName;
/*!
 *  @def    CC2650_LAUNCHXL_SPIName
 *  @brief  Enum of SPI names
 */
typedef enum CC2650_LAUNCHXL_SPIName {
    CC2650_LAUNCHXL_SPI0 = 0,
    CC2650_LAUNCHXL_SPI1,

    CC2650_LAUNCHXL_SPICOUNT
} CC2650_LAUNCHXL_SPIName;

/*!
 *  @def    CC2650_LAUNCHXL_UARTName
 *  @brief  Enum of UARTs
 */
typedef enum CC2650_LAUNCHXL_UARTName {
    CC2650_LAUNCHXL_UART0 = 0,

    CC2650_LAUNCHXL_UARTCOUNT
} CC2650_LAUNCHXL_UARTName;

/*!
 *  @def    CC2650_LAUNCHXL_UDMAName
 *  @brief  Enum of DMA buffers
 */
typedef enum CC2650_LAUNCHXL_UDMAName {
    CC2650_LAUNCHXL_UDMA0 = 0,

    CC2650_LAUNCHXL_UDMACOUNT
} CC2650_LAUNCHXL_UDMAName;

/*!
 *  @def    CC2650_LAUNCHXL_WatchdogName
 *  @brief  Enum of Watchdogs
 */
typedef enum CC2650_LAUNCHXL_WatchdogName {
    CC2650_LAUNCHXL_WATCHDOG0 = 0,

    CC2650_LAUNCHXL_WATCHDOGCOUNT
} CC2650_LAUNCHXL_WatchdogName;

#ifdef __cplusplus
}
#endif

#endif /* __CC2650_LAUNCHXL_BOARD_H__ */
