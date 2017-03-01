/******************************************************************************

 @file  mac_settings.c

 @brief This file contains CM0 radio command variables.

 Group: WCS, LPC
 Target Device: CC13xx

 ******************************************************************************
 
 Copyright (c) 2015-2016, Texas Instruments Incorporated
 All rights reserved.

 IMPORTANT: Your use of this Software is limited to those specific rights
 granted under the terms of a software license agreement between the user
 who downloaded the software, his/her employer (which must be your employer)
 and Texas Instruments Incorporated (the "License"). You may not use this
 Software unless you agree to abide by the terms of the License. The License
 limits your use, and you acknowledge, that the Software may not be modified,
 copied or distributed unless embedded on a Texas Instruments microcontroller
 or used solely and exclusively in conjunction with a Texas Instruments radio
 frequency transceiver, which is integrated into your product. Other than for
 the foregoing purpose, you may not use, reproduce, copy, prepare derivative
 works of, modify, distribute, perform, display or sell this Software and/or
 its documentation for any purpose.

 YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
 PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
 NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
 TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
 NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
 LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
 INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
 OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
 OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
 (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 Should you have any questions regarding your right to use this Software,
 contact Texas Instruments Incorporated at www.TI.com.

 ******************************************************************************
 Release Name: simplelink_cc13x0_sdk_1_00_00_13"
 Release Date: 2016-11-21 18:05:36
 *****************************************************************************/

//*********************************************************************************
// Default parameter summary
// Address: N/A
// Frequency: 920.00000 MHz
// Data Format: Serial mode disable
// Deviation: 25.000 kHz
// Packet Length Config: Variable
// Max Packet Length: 1040
// Packet Length: Variable
// RX Filter BW: 110 kHz
// Symbol Rate: 50.00000 kBaud
// Sync Word Length: 16 Bits
// Whitening: Whitening Enabled

/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */

#include <stdint.h>
#include <driverlib/rf_mailbox.h>
#include <driverlib/rf_common_cmd.h>
#include <driverlib/rf_prop_cmd.h>
#include "rf_api.h"
#include "mac_settings.h"

// Overrides for CMD_PROP_RADIO_DIV_SETUP
uint32_t pOverridesPG20[] =
{
    // override_use_patch_prop_genfsk.xml
    // PHY: Use MCE ROM, RFE RAM patch
    MCE_RFE_OVERRIDE(0,4,0,1,0,0),
    // override_synth_prop_863_970_div5.xml
    // Synth: Set recommended RTRIM to A
	HW_REG_OVERRIDE(0x4038,0x003A),
    // Synth: Set Fref to 4 MHz
    (uint32_t)0x000684A3,
    // Synth: Configure fine calibration setting
    HW_REG_OVERRIDE(0x4020,0x7F00),
    // Synth: Configure fine calibration setting
    HW_REG_OVERRIDE(0x4064,0x0040),
    // Synth: Configure fine calibration setting
    (uint32_t)0xB1070503,
    // Synth: Configure fine calibration setting
    (uint32_t)0x05330523,
    // Synth: Set loop bandwidth after lock to 20 kHz
    (uint32_t)0x0A480583,
    // Synth: Set loop bandwidth after lock to 20 kHz
    (uint32_t)0x7AB80603,
    // Synth: Configure VCO LDO (in ADI1, set VCOLDOCFG=0x9F to use voltage input reference)
    ADI_REG_OVERRIDE(1,4,0x9F),
    // Synth: Configure synth LDO (in ADI1, set SLDOCTL0.COMP_CAP=1)
    ADI_HALFREG_OVERRIDE(1,7,0x4,0x4),
    // Synth: Use 24 MHz XOSC as synth clock, enable extra PLL filtering
    (uint32_t)0x02010403,
    // Synth: Configure extra PLL filtering
    (uint32_t)0x00108463,
    // Synth: Increase synth programming timeout
    (uint32_t)0x04B00243,
    // override_phy_gfsk_rx_rssi.xml
    // Rx: Set LNA bias current trim offset to 3
    (uint32_t)0x00038883,
    // Rx: Set RSSI offset to adjust reported RSSI by +5 dB
    (uint32_t)0x00FB88A3,
    // Rx: Freeze RSSI on sync found event
    HW_REG_OVERRIDE(0x6084,0x35F1),
    // override_phy_agc_reflevel_0x1a.xml
    // Tx: Enable PA ramping (0x41). Rx: Set AGC reference level to 0x1A.
    HW_REG_OVERRIDE(0x6088,0x411A),
    // Tx: Configure PA ramping setting and RSSI measurement period of 34us. This may change for different data rate.
    HW_REG_OVERRIDE(0x608C,0x8223),  // Edited for TIMAC
    // override_phy_rx_aaf_bw_0xd.xml
    // Rx: Set anti-aliasing filter bandwidth to 0xD (in ADI0, set IFAMPCTL3[7:4]=0xD)
    ADI_HALFREG_OVERRIDE(0,61,0xF,0xD),
    (uint32_t)0x00000943, // Correct CRC initialization for 16-bit CRC
    (uint32_t)0x00000963, // Correct CRC initialization for 16-bit CRC
    (uint32_t)0xFFFFFFFF,
};

// Overrides for CMD_PROP_RADIO_DIV_SETUP
uint32_t pOverridesPG21[] =
{
    // override_use_patch_prop_genfsk.xml
    // PHY: Use MCE ROM, RFE RAM patch
    MCE_RFE_OVERRIDE(0,4,0,1,0,0),
    // override_synth_prop_863_970_div5.xml
    // Synth: Set recommended RTRIM to 7
    HW_REG_OVERRIDE(0x4038,0x0037),
    // Synth: Set Fref to 4 MHz
    (uint32_t)0x000684A3,
    // Synth: Configure fine calibration setting
    HW_REG_OVERRIDE(0x4020,0x7F00),
    // Synth: Configure fine calibration setting
    HW_REG_OVERRIDE(0x4064,0x0040),
    // Synth: Configure fine calibration setting
    (uint32_t)0xB1070503,
    // Synth: Configure fine calibration setting
    (uint32_t)0x05330523,
    // Synth: Set loop bandwidth after lock to 20 kHz
    (uint32_t)0x0A480583,
    // Synth: Set loop bandwidth after lock to 20 kHz
    (uint32_t)0x7AB80603,
    // Synth: Configure VCO LDO (in ADI1, set VCOLDOCFG=0x9F to use voltage input reference)
    ADI_REG_OVERRIDE(1,4,0x9F),
    // Synth: Configure synth LDO (in ADI1, set SLDOCTL0.COMP_CAP=1)
    ADI_HALFREG_OVERRIDE(1,7,0x4,0x4),
    // Synth: Use 24 MHz XOSC as synth clock, enable extra PLL filtering
    (uint32_t)0x02010403,
    // Synth: Configure extra PLL filtering
    (uint32_t)0x00108463,
    // Synth: Increase synth programming timeout
    (uint32_t)0x04B00243,
    // override_phy_gfsk_rx_rssi.xml
    // Rx: Set LNA bias current trim offset to 3
    (uint32_t)0x00038883,
    // Rx: Set RSSI offset to adjust reported RSSI by +5 dB
    (uint32_t)0x00FB88A3,
    // Rx: Freeze RSSI on sync found event
    HW_REG_OVERRIDE(0x6084,0x35F1),
    // override_phy_agc_reflevel_0x1a.xml
    // Tx: Enable PA ramping (0x41). Rx: Set AGC reference level to 0x1A.
    HW_REG_OVERRIDE(0x6088,0x411A),
    // Tx: Configure PA ramping setting and RSSI measurement period of 34us. This may change for different data rate.
    HW_REG_OVERRIDE(0x608C,0x8223),  // Edited for TIMAC
    // override_phy_rx_aaf_bw_0xd.xml
    // Rx: Set anti-aliasing filter bandwidth to 0xD (in ADI0, set IFAMPCTL3[7:4]=0xD)
    ADI_HALFREG_OVERRIDE(0,61,0xF,0xD),
    (uint32_t)0x00000943, // Correct CRC initialization for 16-bit CRC
    (uint32_t)0x00000963, // Correct CRC initialization for 16-bit CRC
    (uint32_t)0xFFFFFFFF,
};

// CMD_PROP_RADIO_DIV_SETUP
rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup =
{
    .commandNo = 0x3807,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .modulation.modType = 0x1, // GFSK
    .modulation.deviation = 0x64, // 100
    .symbolRate.preScale = 0xf, // 15
    .symbolRate.rateWord = 0x8000, // 32768
    .rxBw = 0x23, // 88 kHz
    .preamConf.nPreamBytes = 0x7, // 7 bytes
    .preamConf.preamMode = 0x0, // Send 0 as first bit in 2FSK
    .formatConf.nSwBits = 24, // 24-bit of syncword
    .formatConf.bBitReversal = 0x0,
    .formatConf.bMsbFirst = 0x1,
    .formatConf.fecMode = 0x0,
    .formatConf.whitenMode = 0x7,
    .config.frontEndMode = 0x0,
    .config.biasMode = 0x1,
    .config.bNoFsPowerUp = 0x0,
    .txPower = 0xa73f,
    .pRegOverride = pOverridesPG21,
    .centerFreq = 915, // 915 MHz
    .intFreq = 0x8000, // Use default
    .loDivider = 0x05,
};

// CMD_NOP
rfc_CMD_NOP_t RF_cmdNop =
{
    .commandNo = 0x0801,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
};

// CMD_FS
rfc_CMD_FS_t RF_cmdFs =
{
    .commandNo = 0x0803,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .frequency = 920, // 920 MHz
    .fractFreq = 0x0000,
    .synthConf.bTxMode = 0x0,
    .synthConf.refFreq = 0x0,
    .__dummy0 = 0x00,
    .__dummy1 = 0x00,
    .__dummy2 = 0x00,
    .__dummy3 = 0x0000,
};

// CMD_PROP_TX_ADV
rfc_CMD_PROP_TX_ADV_t RF_cmdPropTxAdv =
{
    .commandNo = 0x3803,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = TRIG_NOW,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .pktConf.bFsOff = 0x0,
    .pktConf.bUseCrc = 0x1,
    .pktConf.bCrcIncSw = 0x0,
    .pktConf.bCrcIncHdr = 0x0,
    .numHdrBits = 16,
    .pktLen = 0,
    .startConf.bExtTxTrig = 0,
    .startConf.inputMode = 0,
    .startConf.source = 0,
    .preTrigger.triggerType = TRIG_REL_START, // CC13_RF_ROM_FW_CPE--BUG00016
    .preTrigger.bEnaCmd = 0,
    .preTrigger.triggerNo = 0,
    .preTrigger.pastTrig = 1,
    .preTime = 0,
    .syncWord = 0x0055904e,
    .pPkt = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
};

// CMD_PROP_CS for CSMA or LBT
rfc_CMD_PROP_CS_t RF_cmdPropCs =
{
    .commandNo = 0x3805,
    .status = 0x0000,
    .pNextOp = (rfc_radioOp_t *)&RF_cmdPropTxAdv,
    .startTime = 0x00000000,
    .startTrigger.triggerType = TRIG_REL_SUBMIT,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = COND_STOP_ON_TRUE,
    .condition.nSkip = 0,
    .csFsConf.bFsOffIdle = 0x0,
    .csFsConf.bFsOffBusy = 0x0,
    .__dummy0 = 0x0,
    .csConf.bEnaRssi = 0x1,
    .csConf.bEnaCorr = 0x0, /* CC13xx sub-G can only support CCA mode 1 */
    .csConf.operation = 0x0,
    .csConf.busyOp = 0x1,
    .csConf.idleOp = 0x1,
    .csConf.timeoutRes = 0x0,
    .rssiThr = -83, /* -83 dBm */
    .numRssiIdle = 0x00,
    .numRssiBusy = 0x00,
    .corrPeriod = 640, /* Filler, used for correlation only */
    .corrConfig.numCorrInv = 0x03,
    .corrConfig.numCorrBusy = 0x00,
    .csEndTrigger.triggerType = TRIG_REL_START,
    .csEndTrigger.bEnaCmd = 0x0,
    .csEndTrigger.triggerNo = 0x0,
    .csEndTrigger.pastTrig = 0x0,
    .csEndTime = 8000, /* 2 ms timeout as a fallback */
};

// CMD_PROP_CS
rfc_CMD_PROP_CS_t RF_cmdPropCsSlotted =
{
    .commandNo = 0x3805,
    .status = 0x0000,
    .pNextOp = (rfc_radioOp_t *)&RF_cmdPropCs,
    .startTime = 0x00000000,
    .startTrigger.triggerType = TRIG_ABSTIME,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = COND_STOP_ON_TRUE,
    .condition.nSkip = 0x0,
    .csFsConf.bFsOffIdle = 0x0,
    .csFsConf.bFsOffBusy = 0x0,
    .__dummy0 = 0x0,
    .csConf.bEnaRssi = 0x1,
    .csConf.bEnaCorr = 0x0, /* CC13xx sub-G can only support CCA mode 1 */
    .csConf.operation = 0x0,
    .csConf.busyOp = 0x1,
    .csConf.idleOp = 0x1,
    .csConf.timeoutRes = 0x0,
    .rssiThr = -83, /* -83 dBm */
    .numRssiIdle = 0x00,
    .numRssiBusy = 0x00,
    .corrPeriod = 640, /* Filler, used for correlation only */
    .corrConfig.numCorrInv = 0x03,
    .corrConfig.numCorrBusy = 0x00,
    .csEndTrigger.triggerType = TRIG_REL_START,
    .csEndTrigger.bEnaCmd = 0x0,
    .csEndTrigger.triggerNo = 0x0,
    .csEndTrigger.pastTrig = 0x0,
    .csEndTime = 8000, /* 2 ms timeout as a fallback */
};

// CMD_PROP_RX_ADV
rfc_CMD_PROP_RX_ADV_t RF_cmdPropRxAdv =
{
    .commandNo = 0x3804,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .pktConf.bFsOff = 0x0,
    .pktConf.bRepeatOk = 0x0, // TODO
    .pktConf.bRepeatNok = 0x0, // TODO
    .pktConf.bUseCrc = 0x1,
    .pktConf.bCrcIncSw = 0x0,
    .pktConf.bCrcIncHdr = 0x0,
    .pktConf.endType = 0x0, // TODO
    .pktConf.filterOp = 0x1, // TODO
    .rxConf.bAutoFlushIgnored = 0x0,
    .rxConf.bAutoFlushCrcErr = 0x1,
    .rxConf.bIncludeHdr = 0x1,
    .rxConf.bIncludeCrc = 0x0,
    .rxConf.bAppendRssi = 0x1,
    .rxConf.bAppendTimestamp = 0x1,
    .rxConf.bAppendStatus = 0x0,
    .syncWord0 = 0x0055904e,
    .syncWord1 = 0x00000000,
    .maxPktLen = 500,/* Will be re-initialized in RX init */
    .hdrConf.numHdrBits = 16,
    .hdrConf.lenPos = 0,
    .hdrConf.numLenBits = 11,
    .addrConf.addrType = 0,
    .addrConf.addrSize = 0, // TODO: no address is used for now
    .addrConf.addrPos = 0,
    .addrConf.numAddr = 0,
    .lenOffset = -4,
#ifdef RFCORE49
    .endTrigger.triggerType = 0x4,
    .endTrigger.bEnaCmd = 0x0,
    .endTrigger.triggerNo = 0x0,
    .endTrigger.pastTrig = 0x0,
    .endTime = 1680000000,   //7 minutes
#else
    .endTrigger.triggerType = 0x1,
    .endTrigger.bEnaCmd = 0x0,
    .endTrigger.triggerNo = 0x0,
    .endTrigger.pastTrig = 0x0,
    .endTime = 0x00000000,   
#endif
    .pAddr = 0,
    .pQueue = 0, // INSERT APPLICABLE POINTER: (dataQueue_t*)&xxx
    .pOutput = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
};

// CMD_SET_RAT_CMP
rfc_CMD_SET_RAT_CMP_t RF_cmdRat =
{
    .commandNo = 0x000A,
    .ratCh = 0,
    .__dummy0 = 0,
    .compareTime = 0,
};
