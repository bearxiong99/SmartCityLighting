/******************************************************************************

 @file  mac.h

 @brief This file contains the data structures and APIs for CC13xx
        RF Core Firmware Specification for IEEE 802.15.4.

 Group: WCS, LPC
 Target Device: CC13xx

 ******************************************************************************
 
 Copyright (c) 2009-2016, Texas Instruments Incorporated
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
 PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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

#ifndef MAC_H
#define MAC_H

/*******************************************************************************
 * INCLUDES
 */
#include "hal_types.h"
#include "rf_common_cmd.h"
#include "rf_mailbox.h"
#include "saddr.h"
#include "boards/mac_user_config.h"
#include "rf_api.h"

/*******************************************************************************
 * CONSTANTS
 */

#define RAT_BASE                       RFC_RAT_BASE

/* Registers */
#define MAC_RAT_COUNT                  HWREG(RAT_BASE + 0x004)
#define MAC_RAT_ADJ                    HWREG(RAT_BASE + 0x008)

/* SDF callback status */
#define MAC_SFD_DETECTED               0
#define MAC_SFD_FRAME_RECEIVED         1
#define MAC_SFD_FRAME_DISCARDED        2
#define MAC_SFD_HALT_CLEANED_UP        3
#define MAC_SFD_CRC_ERROR              4


/*******************************************************************************
 * MACROS
 */

#define SET_FRAME_FILTER_PAN_COORDINATOR(x, v)                                \
  x |= ((x) & ~BV(7) | ((v) ? BV(7) : 0))

/*******************************************************************************
 * TYPEDEFS
 */

/* MAC Radio Operation Receive Queue Configuration
 * |     7     |     6    |    5    |  4   |  3  |   2     |         1         |         0           |
 * | Timestamp | SrcIndex | CorrCRC | RSSI | CRC | PhyHdr  | AutoFlush Ignored | AutoFlush CRC Error |
 */
typedef uint8  rxQCfg_t;

/* MAC Frame Filter Configuration
 * |         15        |    14..13     |      12..10       |     9..8      |
 * | ACK Length Filter | Modify Filter | FCF Reserved Mask | Max Frame Ver |
 * |
 * |     7     |       6       |      5       |     4     |     3       |    2     |   1         |      0       |
 * | PAN Coord | Pend Data Req | Default Pend | Auto Pend | Slotted ACK | Auto ACK | Filter Stop | Frame Filter |
 */
typedef uint16  frmFilterOpt_t;

/* MAC Frame Types Filtering
 * |      7       |      6       |      5       |      4       |     3       |   2     |    1     |     0      |
 * | FT7 Reserved | FT6 Reserved | FT5 Reserved | FT4 Reserved | FT3 MAC Cmd | FT2 ACK | FT1 Data | FT0 Beacon |
 */
typedef uint8  frmTypes_t;

/* MAC CCA Source Configuration
 * |    7     |      5..6      |      4        |     3         |     2      |     1      |        0        |
 * | Reserved | Corr Threshold | Sync operator | Corr Operator | Sync Found | Correlator | CCA Energy Scan |
 */
typedef uint8  ccaOpt_t;

/*
** MAC Output Command Structures
*/

/* RX command */
PACKED_TYPEDEF_STRUCT
{
  uint8             nTxAck;            /* RW: num ACK frames transmitted */
  uint8             nRxBeacon;         /* RW: num beacon frames received */
  uint8             nRxData;           /* RW: num data frames received */
  uint8             nRxAck;            /* RW: num ACK frames received */
  uint8             nRxMacCmd;         /* RW: num MAC command frames received */
  uint8             nRxReserved;       /* RW: num reserved type frames received */
  uint8             nRxNok;            /* RW: num frames with CRC error received */
  uint8             nRxIgnored;        /* RW: num ignored frames received */
  uint8             nRxBufFull;        /* RW: num frames discarded due to buffer full */
  uint8             lastRssi;          /* R:  RSSI of the last received frame */
  uint8             maxRssi;           /* R:  Highest RSSI observed in the operation */
  uint8             reserved;          /* X:  Reserved */
  uint32            beaconTimeStamp;   /* R:  Time stamp of the last received beacon frame */
} output_t;


/* FG Pttern Check Command */
typedef rfc_CMD_PATTERN_CHECK_t FGPatternCheckCmd_t;

/* IEEE 802.15.4 Update Radio Settings Command */
typedef rfc_CMD_RADIO_SETUP_t updateRadioSettingsCmd_t;

/*
** MAC Radio Immediate Commands
*/

/* Modify CCA Command */
PACKED_TYPEDEF_STRUCT
{
  uint16            cmdNum;            /* W:  radio command number */
  ccaOpt_t          newCcaOpt;         /* W:  new CCA option for the running background operation */
  uint8             newCcaRssiThr;     /* W:  new CCA RSSI threshold */
} macModifyCcaCmd_t;

/* Modify Frame Filtering Command */
PACKED_TYPEDEF_STRUCT
{
  uint16            cmdNum;            /* W:  radio command number */
  frmFilterOpt_t    newFrmFiltOpt;     /* W:  new frame filtering option for the running background operation */
  uint8             newFrmTypes;       /* W:  new frame types */
} macModifyFrmFiltCmd_t;

/* MAC frame filter */
typedef struct
{
  frmFilterOpt_t    filterOpt;         /* frame filter option */
  frmTypes_t        frmTypes;          /* frame types to receive */
  sAddrExt_t        localExtAddr;      /* local externded address */
  uint16            localShortAddr;    /* local short address */
  uint16            localPanID;        /* local PAN ID */
} macFrmFilter_t;

/* Software SFD detected callback */
typedef void (*macSfdDetectCBack_t)(uint8 status);

typedef struct
{
    uint16    rxAckPkt;
    uint16    rxAckPktCb;
    uint16    rxDataPktARQ;
    uint16    txAck;
    uint16    txAckCancel;
    uint16    txReqAckTimerStart;
    uint16    ackTimeOut;
    uint16    txAckCancelTimer;
    uint16    ackCbErr;
} MAC_ACK_DBG;

#ifdef FH_HOP_DEBUG
typedef struct
{
    uint16    num_sfd_rx_stop;
    uint16    num_sfd_rx_abort;
} MAC_SFD_DBG;
extern MAC_SFD_DBG macSfdDbg;
#endif
extern MAC_ACK_DBG macAckDbg;


/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
/* Track the last RF post cmd */
extern uint32_t* lastPostCmd;

/* Number of pending RF command */
extern volatile int8_t numRfCmd;

/* MAC radio command active */
extern volatile uint8_t macRxCmdActive;
extern volatile uint8_t macTxCmdActive;
extern volatile uint8_t macFsCmdActive;

/* MAC TX timestamp */
extern uint32_t macTxTimestamp;

/* MAC Reveive output buffer */
extern rfc_propRxOutput_t macRxOutput;

/* MAC RF front end configuration. Use a pointer to void since
 * the format changes from package to package.
 */
extern macUserCfg_t *pMacRadioConfig;

/* MAC frame filter */
extern macFrmFilter_t macFrmFilter;

/* RX command handle and callback event mask */
extern RF_CmdHandle rxCmdHandle;
extern RF_EventMask rxCbEventMask;
/* Fs command handle */
extern RF_CmdHandle fsCmdHandle;

/* SFD registration */
extern void macRegisterSfdDetect( macSfdDetectCBack_t sfdCback );

/* SFD callbcak */
extern macSfdDetectCBack_t macSfdDetectCback;

/* WA for reinitiate RAT compare on the channel in use */
extern volatile int8_t lastRatChanA;
extern volatile int8_t lastRatChanB;

/* Pointer to RF patch table */
extern RF_Mode *pRfPropTable;

/*******************************************************************************
 * APIs
 */
extern void macSetupReceiveCmd( void );
extern bool macSendReceiveCmd( void );
extern void macSetupRxAckTimeout( void );
extern void macStopCmd( bool bGraceful );
extern void macRxQueueFlushCmd ( void );
extern void macFreqSynthCmd( uint8 channel );
extern uint8 macGetCurrRssi( void );
extern void macSetupRATChanCompare( RF_Callback ratCb, uint32 compareTime );
extern void macSetupFsCmd( uint8 channel );
extern bool macSendFsCmd( uint8 channel );
extern void macSetTxPowerVal( uint16 txPowerVal );
extern void macRatCb_A( RF_Handle h, RF_CmdHandle ch, RF_EventMask e );
extern void macRatCb_B( RF_Handle h, RF_CmdHandle ch, RF_EventMask e );
extern void macSfdDetected( RF_Handle h, RF_CmdHandle ch, RF_EventMask e );
extern uint32 macRatCount(void);
extern void macRatDisableChannels(void);
/*******************************************************************************
 */

#endif /* MAC_H */
