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

/*
 *  ============================= CC1310DK_7XD.c =============================
 *  This file is responsible for setting up the board specific items for the
 *  CC1310DK_7XD board.
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include <ti/devices/cc13x0/driverlib/ioc.h>
#include <ti/devices/cc13x0/driverlib/udma.h>
#include <ti/devices/cc13x0/inc/hw_ints.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>

#include "CC1310DK_7XD.h"

/*
 *  =============================== ADCBuf ===============================
 */
#include <ti/drivers/ADCBuf.h>
#include <ti/drivers/adcbuf/ADCBufCC26XX.h>

ADCBufCC26XX_Object adcBufCC26xxObjects[CC1310DK_7XD_ADCBUFCOUNT];

/*
 *  This table converts a virtual adc channel into a dio and internal analogue
 *  input signal. This table is necessary for the functioning of the adcBuf
 *  driver. Comment out unused entries to save flash. Dio and internal signal
 *  pairs are hardwired. Do not remap them in the table. You may reorder entire
 *  entries. The mapping of dio and internal signals is package dependent.
 */
const ADCBufCC26XX_AdcChannelLutEntry ADCBufCC26XX_adcChannelLut[CC1310DK_7XD_ADCCOUNT] = {
    {CC1310DK_7XD_ALS_OUT,  ADC_COMPB_IN_AUXIO7},
    {PIN_UNASSIGNED, ADC_COMPB_IN_DCOUPL},
    {PIN_UNASSIGNED, ADC_COMPB_IN_VSS},
    {PIN_UNASSIGNED, ADC_COMPB_IN_VDDS}
};

const ADCBufCC26XX_HWAttrs adcBufCC26xxHWAttrs[CC1310DK_7XD_ADCBUFCOUNT] = {
    {
        .intPriority       = ~0,
        .swiPriority       = 0,
        .adcChannelLut     = ADCBufCC26XX_adcChannelLut,
        .gpTimerUnit       = CC1310DK_7XD_GPTIMER0A,
        .gptDMAChannelMask = 1 << UDMA_CHAN_TIMER0_A,
    }
};

const ADCBuf_Config ADCBuf_config[CC1310DK_7XD_ADCBUFCOUNT] = {
    {
        &ADCBufCC26XX_fxnTable,
        &adcBufCC26xxObjects[CC1310DK_7XD_ADCBUF0],
        &adcBufCC26xxHWAttrs[CC1310DK_7XD_ADCBUF0]
    }
};

const uint_least8_t ADCBuf_count = CC1310DK_7XD_ADCBUFCOUNT;

/*
 *  =============================== ADC ===============================
 */
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC26XX.h>

ADCCC26XX_Object adcCC26xxObjects[CC1310DK_7XD_ADCCOUNT];

const ADCCC26XX_HWAttrs adcCC26xxHWAttrs[CC1310DK_7XD_ADCCOUNT] = {
    {
        .adcDIO              = CC1310DK_7XD_ALS_OUT,
        .adcCompBInput       = ADC_COMPB_IN_AUXIO7,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL
    },
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_DCOUPL,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL
    },
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_VSS,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL
    },
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_VDDS,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL
    }
};

const ADC_Config ADC_config[CC1310DK_7XD_ADCCOUNT] = {
    {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310DK_7XD_ADCALS], &adcCC26xxHWAttrs[CC1310DK_7XD_ADCALS]},
    {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310DK_7XD_ADCDCOUPL], &adcCC26xxHWAttrs[CC1310DK_7XD_ADCDCOUPL]},
    {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310DK_7XD_ADCVSS], &adcCC26xxHWAttrs[CC1310DK_7XD_ADCVSS]},
    {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310DK_7XD_ADCVDDS], &adcCC26xxHWAttrs[CC1310DK_7XD_ADCVDDS]},
};

const uint_least8_t ADC_count = CC1310DK_7XD_ADCCOUNT;

/*
 *  =============================== Crypto ===============================
 */
#include <ti/drivers/crypto/CryptoCC26XX.h>

CryptoCC26XX_Object cryptoCC26XXObjects[CC1310DK_7XD_CRYPTOCOUNT];

const CryptoCC26XX_HWAttrs cryptoCC26XXHWAttrs[CC1310DK_7XD_CRYPTOCOUNT] = {
    {
        .baseAddr       = CRYPTO_BASE,
        .powerMngrId    = PowerCC26XX_PERIPH_CRYPTO,
        .intNum         = INT_CRYPTO_RESULT_AVAIL_IRQ,
        .intPriority    = ~0,
    }
};

const CryptoCC26XX_Config CryptoCC26XX_config[CC1310DK_7XD_CRYPTOCOUNT] = {
    {
         .object  = &cryptoCC26XXObjects[CC1310DK_7XD_CRYPTO0],
         .hwAttrs = &cryptoCC26XXHWAttrs[CC1310DK_7XD_CRYPTO0]
    },
};

/*
 *  =============================== Display ===============================
 */
#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>
#include <ti/display/DisplayDogm1286.h>
#include <ti/mw/lcd/LCDDogm1286.h>

#ifndef BOARD_DISPLAY_UART_STRBUF_SIZE
#define BOARD_DISPLAY_UART_STRBUF_SIZE    128
#endif

DisplayUart_Object        displayUartObject;
DisplayDogm1286_Object    displayDogm1286Object;
LCD_Object lcdObject;

static char uartStringBuf[BOARD_DISPLAY_UART_STRBUF_SIZE];

const DisplayUart_HWAttrs displayUartHWAttrs = {
    .uartIdx      = CC1310DK_7XD_UART0,
    .baudRate     = 115200,
    .mutexTimeout = (unsigned int)(-1),
    .strBuf       = uartStringBuf,
    .strBufLen    = BOARD_DISPLAY_UART_STRBUF_SIZE,
};

const LCD_HWAttrs lcdHWAttrs = {
    .LCD_initCmd = &LCD_initCmd,
    .lcdResetPin = CC1310DK_7XD_LCD_RST,       /* LCD reset pin */
    .lcdModePin  = CC1310DK_7XD_LCD_MODE,      /* LCD mode pin  */
    .lcdCsnPin   = CC1310DK_7XD_LCD_CSN,       /* LCD CSn pin   */
    .spiIndex    = CC1310DK_7XD_SPI0
};

const LCD_Config LCD_config = {
    .object  = &lcdObject,
    .hwAttrs = &lcdHWAttrs
};

const DisplayDogm1286_HWAttrs displayDogm1286HWattrs = {
    .lcdHandle = (LCD_Handle) & LCD_config,
    .powerPin  = CC1310DK_7XD_3V3_EN
};

#ifndef BOARD_DISPLAY_USE_UART
#define BOARD_DISPLAY_USE_UART 1
#endif
#ifndef BOARD_DISPLAY_USE_UART_ANSI
#define BOARD_DISPLAY_USE_UART_ANSI 0
#endif
#ifndef BOARD_DISPLAY_USE_LCD
#define BOARD_DISPLAY_USE_LCD 0
#endif

const Display_Config Display_config[] = {
#if (BOARD_DISPLAY_USE_UART)
    {
#  if (BOARD_DISPLAY_USE_UART_ANSI)
        .fxnTablePtr = &DisplayUartAnsi_fxnTable,
#  else /* Default to minimal UART with no cursor placement */
        .fxnTablePtr = &DisplayUartMin_fxnTable,
#  endif
        .object      = &displayUartObject,
        .hwAttrs     = &displayUartHWAttrs,
    },
#endif
#if (BOARD_DISPLAY_USE_LCD)
    {
        .fxnTablePtr = &DisplayDogm1286_fxnTable,
        .object      = &displayDogm1286Object,
        .hwAttrs     = &displayDogm1286HWattrs
    },
#endif
};

const uint_least8_t Display_count = sizeof(Display_config) / sizeof(Display_Config);

/*
 *  =============================== GPIO ===============================
 */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/*
 * Array of Pin configurations
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in CC1310DK_7XD.h
 * NOTE: Pins not used for interrupts should be placed at the end of the
 *       array. Callback entries can be omitted from callbacks array to
 *       reduce memory usage.
 */
GPIO_PinConfig gpioPinConfigs[CC1310DK_7XD_GPIOCOUNT] = {
    /* Input pins */
    GPIOCC26XX_DIO_19 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,  /* Button 0 */
    GPIOCC26XX_DIO_12 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,  /* Button 1 */

    /* Output pins */
    GPIOCC26XX_DIO_25 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* LED0 */
    GPIOCC26XX_DIO_27 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* LED1 */
    GPIOCC26XX_DIO_07 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* LED2 */
    GPIOCC26XX_DIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* LED3 */
};

/*
 * Array of callback function pointers
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in CC1310DK_7XD.h
 * NOTE: Pins not used for interrupts can be omitted from callbacks array to
 *       reduce memory usage (if placed at end of gpioPinConfigs array).
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,  /*  Button 0 */
    NULL,  /*  Button 1 */
};

const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs         = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks          = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = CC1310DK_7XD_GPIOCOUNT,
    .numberOfCallbacks  = sizeof(gpioCallbackFunctions)/sizeof(GPIO_CallbackFxn),
    .intPriority        = (~0)
};

/*
 *  =============================== GPTimer ===============================
 *  Remove unused entries to reduce flash usage both in Board.c and Board.h
 */
#include <ti/drivers/timer/GPTimerCC26XX.h>

GPTimerCC26XX_Object gptimerCC26XXObjects[CC1310DK_7XD_GPTIMERCOUNT];

const GPTimerCC26XX_HWAttrs gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMERPARTSCOUNT] = {
    { .baseAddr = GPT0_BASE, .intNum = INT_GPT0A, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT0, .pinMux = GPT_PIN_0A, },
    { .baseAddr = GPT0_BASE, .intNum = INT_GPT0B, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT0, .pinMux = GPT_PIN_0B, },
    { .baseAddr = GPT1_BASE, .intNum = INT_GPT1A, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT1, .pinMux = GPT_PIN_1A, },
    { .baseAddr = GPT1_BASE, .intNum = INT_GPT1B, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT1, .pinMux = GPT_PIN_1B, },
    { .baseAddr = GPT2_BASE, .intNum = INT_GPT2A, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT2, .pinMux = GPT_PIN_2A, },
    { .baseAddr = GPT2_BASE, .intNum = INT_GPT2B, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT2, .pinMux = GPT_PIN_2B, },
    { .baseAddr = GPT3_BASE, .intNum = INT_GPT3A, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT3, .pinMux = GPT_PIN_3A, },
    { .baseAddr = GPT3_BASE, .intNum = INT_GPT3B, .intPriority = (~0), .powerMngrId = PowerCC26XX_PERIPH_GPT3, .pinMux = GPT_PIN_3B, },
};

const GPTimerCC26XX_Config GPTimerCC26XX_config[CC1310DK_7XD_GPTIMERPARTSCOUNT] = {
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER0], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER0A], GPT_A },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER0], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER0B], GPT_B },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER1], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER1A], GPT_A },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER1], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER1B], GPT_B },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER2], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER2A], GPT_A },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER2], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER2B], GPT_B },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER3], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER3A], GPT_A },
    { &gptimerCC26XXObjects[CC1310DK_7XD_GPTIMER3], &gptimerCC26xxHWAttrs[CC1310DK_7XD_GPTIMER3B], GPT_B },
};

/*
 *  =============================== PIN ===============================
 */
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

const PIN_Config BoardGpioInitTable[] = {

    CC1310DK_7XD_PIN_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,  /* LED initially off               */
    CC1310DK_7XD_PIN_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,  /* LED initially off               */
    CC1310DK_7XD_PIN_LED3 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,  /* LED initially off               */
    CC1310DK_7XD_PIN_LED4 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,  /* LED initially off               */
    CC1310DK_7XD_KEY_SELECT | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS,                   /* Button is active low            */
    CC1310DK_7XD_KEY_UP | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS,                       /* Button is active low            */
    CC1310DK_7XD_KEY_DOWN | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS,                     /* Button is active low            */
    CC1310DK_7XD_KEY_LEFT | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS,                     /* Button is active low            */
    CC1310DK_7XD_KEY_RIGHT | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS,                    /* Button is active low            */
    CC1310DK_7XD_3V3_EN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW  | PIN_PUSHPULL,                /* 3V3 domain off initially        */
    CC1310DK_7XD_LCD_MODE | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,              /* LCD pin high initially          */
    CC1310DK_7XD_LCD_RST | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,               /* LCD pin high initially          */
    CC1310DK_7XD_LCD_CSN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,               /* LCD CSn deasserted initially    */
    CC1310DK_7XD_ALS_PWR | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL,                /* ALS power off initially         */
    CC1310DK_7XD_ACC_PWR | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL,                /* ACC power off initially         */
    CC1310DK_7XD_ACC_CSN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,               /* ACC CSn deasserted initially    */
    CC1310DK_7XD_SDCARD_CSN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,            /* SDCARD CSn deasserted initially */
    CC1310DK_7XD_UART_TX | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,               /* UART TX pin at inactive level   */

    PIN_TERMINATE
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = ~0,
    .swiPriority = 0
};

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>

const PowerCC26XX_Config PowerCC26XX_config = {
    .policyInitFxn      = NULL,
    .policyFxn          = &PowerCC26XX_standbyPolicy,
    .calibrateFxn       = &PowerCC26XX_calibrate,
    .enablePolicy       = TRUE,
    .calibrateRCOSC_LF  = TRUE,
    .calibrateRCOSC_HF  = TRUE,
};

/*
 *  =============================== PWM ===============================
 *  Remove unused entries to reduce flash usage both in Board.c and Board.h
 */
#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerCC26XX.h>

PWMTimerCC26XX_Object pwmtimerCC26xxObjects[CC1310DK_7XD_PWMCOUNT];

const PWMTimerCC26XX_HwAttrs pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWMCOUNT] = {
    { .pwmPin = CC1310DK_7XD_PWMPIN0, .gpTimerUnit = CC1310DK_7XD_GPTIMER0A },
    { .pwmPin = CC1310DK_7XD_PWMPIN1, .gpTimerUnit = CC1310DK_7XD_GPTIMER0B },
    { .pwmPin = CC1310DK_7XD_PWMPIN2, .gpTimerUnit = CC1310DK_7XD_GPTIMER1A },
    { .pwmPin = CC1310DK_7XD_PWMPIN3, .gpTimerUnit = CC1310DK_7XD_GPTIMER1B },
    { .pwmPin = CC1310DK_7XD_PWMPIN4, .gpTimerUnit = CC1310DK_7XD_GPTIMER2A },
    { .pwmPin = CC1310DK_7XD_PWMPIN5, .gpTimerUnit = CC1310DK_7XD_GPTIMER2B },
    { .pwmPin = CC1310DK_7XD_PWMPIN6, .gpTimerUnit = CC1310DK_7XD_GPTIMER3A },
    { .pwmPin = CC1310DK_7XD_PWMPIN7, .gpTimerUnit = CC1310DK_7XD_GPTIMER3B },
};

const PWM_Config PWM_config[CC1310DK_7XD_PWMCOUNT] = {
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM0], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM0] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM1], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM1] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM2], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM2] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM3], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM3] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM4], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM4] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM5], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM5] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM6], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM6] },
    { &PWMTimerCC26XX_fxnTable, &pwmtimerCC26xxObjects[CC1310DK_7XD_PWM7], &pwmtimerCC26xxHWAttrs[CC1310DK_7XD_PWM7] },
};

/*
 *  =============================== RF Driver ===============================
 */
#include <ti/drivers/rf/RF.h>

const RFCC26XX_HWAttrs RFCC26XX_hwAttrs = {
    .hwiCpe0Priority = ~0,
    .hwiHwPriority   = ~0,
    .swiCpe0Priority =  0,
    .swiHwPriority   =  0,
};

const uint_least8_t PWM_count = CC1310DK_7XD_PWMCOUNT;

/*
 *  =============================== SPI DMA ===============================
 */
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPICC26XXDMA.h>

SPICC26XXDMA_Object spiCC26XXDMAObjects[CC1310DK_7XD_SPICOUNT];

const SPICC26XXDMA_HWAttrsV1 spiCC26XXDMAHWAttrs[CC1310DK_7XD_SPICOUNT] = {
    {
        .baseAddr           = SSI0_BASE,
        .intNum             = INT_SSI0_COMB,
        .intPriority        = ~0,
        .swiPriority        = 0,
        .defaultTxBufValue  = 0,
        .powerMngrId        = PowerCC26XX_PERIPH_SSI0,
        .rxChannelBitMask   = 1<<UDMA_CHAN_SSI0_RX,
        .txChannelBitMask   = 1<<UDMA_CHAN_SSI0_TX,
        .mosiPin            = CC1310DK_7XD_SPI0_MOSI,
        .misoPin            = CC1310DK_7XD_SPI0_MISO,
        .clkPin             = CC1310DK_7XD_SPI0_CLK,
        .csnPin             = CC1310DK_7XD_SPI0_CSN
    },
    {
        .baseAddr           = SSI1_BASE,
        .intNum             = INT_SSI1_COMB,
        .intPriority        = ~0,
        .swiPriority        = 0,
        .defaultTxBufValue  = 0,
        .powerMngrId        = PowerCC26XX_PERIPH_SSI1,
        .rxChannelBitMask   = 1<<UDMA_CHAN_SSI1_RX,
        .txChannelBitMask   = 1<<UDMA_CHAN_SSI1_TX,
        .mosiPin            = CC1310DK_7XD_SPI1_MOSI,
        .misoPin            = CC1310DK_7XD_SPI1_MISO,
        .clkPin             = CC1310DK_7XD_SPI1_CLK,
        .csnPin             = CC1310DK_7XD_SPI1_CSN
    }
};

const SPI_Config SPI_config[CC1310DK_7XD_SPICOUNT] = {
    {
         .fxnTablePtr = &SPICC26XXDMA_fxnTable,
         .object      = &spiCC26XXDMAObjects[CC1310DK_7XD_SPI0],
         .hwAttrs     = &spiCC26XXDMAHWAttrs[CC1310DK_7XD_SPI0]
    },
    {
         .fxnTablePtr = &SPICC26XXDMA_fxnTable,
         .object      = &spiCC26XXDMAObjects[CC1310DK_7XD_SPI1],
         .hwAttrs     = &spiCC26XXDMAHWAttrs[CC1310DK_7XD_SPI1]
    },
};

const uint_least8_t SPI_count = CC1310DK_7XD_SPICOUNT;

/*
 *  =============================== UART ===============================
 */
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>

UARTCC26XX_Object uartCC26XXObjects[CC1310DK_7XD_UARTCOUNT];

const UARTCC26XX_HWAttrsV2 uartCC26XXHWAttrs[CC1310DK_7XD_UARTCOUNT] = {
    {
        .baseAddr       = UART0_BASE,
        .powerMngrId    = PowerCC26XX_PERIPH_UART0,
        .intNum         = INT_UART0_COMB,
        .intPriority    = ~0,
        .swiPriority    = 0,
        .txPin          = CC1310DK_7XD_UART_TX,
        .rxPin          = CC1310DK_7XD_UART_RX,
        .ctsPin         = PIN_UNASSIGNED,
        .rtsPin         = PIN_UNASSIGNED
    }
};

const UART_Config UART_config[CC1310DK_7XD_UARTCOUNT] = {
    {
        .fxnTablePtr = &UARTCC26XX_fxnTable,
        .object      = &uartCC26XXObjects[CC1310DK_7XD_UART0],
        .hwAttrs     = &uartCC26XXHWAttrs[CC1310DK_7XD_UART0]
    },
};

const uint_least8_t UART_count = CC1310DK_7XD_UARTCOUNT;

/*
 *  =============================== UDMA ===============================
 */
#include <ti/drivers/dma/UDMACC26XX.h>

UDMACC26XX_Object udmaObjects[CC1310DK_7XD_UDMACOUNT];

const UDMACC26XX_HWAttrs udmaHWAttrs[CC1310DK_7XD_UDMACOUNT] = {
    {
        .baseAddr    = UDMA0_BASE,
        .powerMngrId = PowerCC26XX_PERIPH_UDMA,
        .intNum      = INT_DMA_ERR,
        .intPriority = ~0
    }
};

const UDMACC26XX_Config UDMACC26XX_config[CC1310DK_7XD_UDMACOUNT] = {
    {
         .object  = &udmaObjects[CC1310DK_7XD_UDMA0],
         .hwAttrs = &udmaHWAttrs[CC1310DK_7XD_UDMA0]
    },
};

/*
 *  =============================== Watchdog ===============================
 */
#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogCC26XX.h>

WatchdogCC26XX_Object watchdogCC26XXObjects[CC1310DK_7XD_WATCHDOGCOUNT];

const WatchdogCC26XX_HWAttrs watchdogCC26XXHWAttrs[CC1310DK_7XD_WATCHDOGCOUNT] = {
    {
        .baseAddr    = WDT_BASE,
        .reloadValue = 1000 /* Reload value in milliseconds */
    },
};

const Watchdog_Config Watchdog_config[CC1310DK_7XD_WATCHDOGCOUNT] = {
    {
        .fxnTablePtr = &WatchdogCC26XX_fxnTable,
        .object      = &watchdogCC26XXObjects[CC1310DK_7XD_WATCHDOG0],
        .hwAttrs     = &watchdogCC26XXHWAttrs[CC1310DK_7XD_WATCHDOG0]
    },
};

const uint_least8_t Watchdog_count = CC1310DK_7XD_WATCHDOGCOUNT;

/*
 *  ======== CC1310DK_7XD_initGeneral ========
 */
void CC1310DK_7XD_initGeneral(void)
{
    Power_init();

    if (PIN_init(BoardGpioInitTable) != PIN_SUCCESS) {
        System_abort("Error with PIN_init\n");
    }
}
