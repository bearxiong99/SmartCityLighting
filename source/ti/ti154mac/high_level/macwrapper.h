/******************************************************************************

 @file  macwrapper.h

 @brief MAC Wrapper function interface defintion used by MLE.

 Group: WCS, LPC
 Target Device: CC13xx

 ******************************************************************************
 
 Copyright (c) 2014-2016, Texas Instruments Incorporated
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

#ifndef MACWRAPPER_H
#define MACWRAPPER_H

/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_types.h"
#include "api_mac.h"

/**
 * Adds a new MAC device table entry in such a way as not to hinder the incoming or outgoing
 * packets.
 *
 * It is ideal that the whole operation is done exclusive of any other MAC operation,
 * via use of critical section on the processor where MAC is implemented, in which case
 * implementation of this function will differ whether the MLE resides in the same processor
 * or in another processor.
 *
 * @param panId       PAN ID of the new device
 * @param shortAddr   short address of the new device
 * @param extAddr     extended address of the new device in little-endian
 * @param exempt      device descriptor exempt field value (TRUE or FALSE)
 * @param keyIdLookupDataSize  key ID lookup data size as it is stored in PIB,
 *                             i.e., 0 for 5 bytes, 1 for 9 bytes.
 * @param keyIdLookupData      key ID lookup data, to look for the key table entry
 *                             and create proper key device descriptor for this device.
 * @param frameCounter frame counter
 * @param uniqueDevice key device descriptor uniqueDevice field value (TRUE or FALSE)
 * @param duplicateDevFlag     a flag (TRUE or FALSE) to indicate whether the device
 *                             entry should be duplicated even for the keys that do
 *                             not match the key ID lookup data.
 *                             The device descriptors that are pointed by the key
 *                             device descriptors that do not match the key ID
 *                             lookup data shall not update the frame counter
 *                             based on the frameCounter argument to this function
 *                             or shall set the frame counter to zero when the entry
 *                             is newly created.
 */
extern unsigned char macWrapperAddDevice(ApiMac_secAddDevice_t *param);

  /**
   * Removes MAC device table entries in such a way as not to hinder the incoming or outgoing
   * packet for the device table entries other than the one being removed.
   *
   * It is ideal that the whole operation is done exclusive of any other MAC operation,
   * via use of critical section on the processor where MAC is implemented, in which case
   * implementation of this function will differ whether the MLE resides in the same processor
   * or in another processor.
   *
   * @param extAddr  extended address of the device table entries that shall be removed,
   *                 in little-endian.
   * @return MAC error code
   */
  extern unsigned char macWrapperDeleteDevice(ApiMac_sAddrExt_t *param);

  /**
   * Removes the key at the specified key Index and removes all
   * MAC device table enteries associated with this key. Also
   * removes(initializes) the key lookup list associated with
   * this key.
   *
   * @param keyIndex      mac secuirty key table index of the key
   *                      to be removed.
   *
   * @return              zero when successful. Non-zero,
   *                      otherwise.
   */
  extern unsigned char macWrapperDeleteKeyAndAssociatedDevices( uint8 keyIndex );

  /**
   * Removes all MAC device table entries in such a way as not to hinder the incoming or outgoing
   * packet for the device table entries other than the one being removed.
   *
   * It is ideal that the whole operation is done exclusive of any other MAC operation,
   * via use of critical section on the processor where MAC is implemented, in which case
   * implementation of this function will differ whether the MLE resides in the same processor
   * or in another processor.
   *
   * @return MAC error code
   */
  extern unsigned char macWrapperDeleteAllDevices(void);

  /**
   * Reads the frame counter value associated with a MAC security key
   * indexed by the designated key identifier and the default key source.
   * @param keyid         key id
   * @param pFrameCounter pointer to a buffer to store the outgoing frame counter of the key
   * @return Zero when successful. Non-zero, otherwise.
   */
  extern unsigned char macWrapperGetDefaultSourceKey(unsigned char keyid,
                                                     unsigned long *pFrameCounter);

  /**
   * Adds the MAC security key, adds the associated lookup list
   * for the key, initializes the frame counter to the value
   * provided. It also duplicates the device table enteries
   * (associated with the previous key if any) if available based
   * on the flag dupDevFlag value and associates the device
   * descriptor with this key.
   *
   * @param pKey            pointer to the buffer containing the
   *                        key data.
   * @param frameCounter    value of the frame counter.
   * @param replaceKeyIndex internal key index of the mac security
   *                        key table where the key needs to be
   *                        written.
   * @param newKeyFlag      If set to one, the function will
   *                        duplicate the device table enteries
   *                        associated with the previous key, and
   *                        associate it with the key.
   *                        If set to zero, the function will
   *                        not alter device table entries associated
   *                        with whatever key that was stored in
   *                        the key table location as designated
   *                        by replaceKeyIndex.
   *
   * @param lookupList      list of lookup data which needs to be
   *                        associated with this key. The lookup
   *                        data should be in the following form.
   *                        count (1byte): number of lookup data,
   *                        followed by the lookup data which
   *                        consists of,
   *                        datasize (1byte): size of the lookup
   *                        data, data (actual lookup data)
   *
   * @return                zero when successful. Non-zero
   *                        otherwise.
   */
  extern unsigned char macWrapperAddKeyInitFCtr( ApiMac_secAddKeyInitFrameCounter_t *param );

#ifdef __cplusplus
}
#endif

#endif /* MACWRAPPER_H */
