/*
 * packets.h
 *
 *  Created on: Feb 27, 2017
 *      Author: curew
 */

#ifndef PACKETS_H_
#define PACKETS_H_

// This file defines the structure of packets sent between nodes
#include <stdint.h>

typedef enum
{
  DiscoveryMessage, // Initial ping from in-network nodes to undiscovered nodes
  UndiscoveredResponse, // Response from an undiscovered node after recieving DiscoveryMessage
  AssignAddress, // AddressAssignment originating from gateway node to undiscovered node after UndiscoveredResponse
  SensorData, // Data originating from a sensor node heading towards gateway node
  ReceiptConfirmation, // Response from a node confirming receipt of a given message
  ParentalPing // Check to see if parent sends ReceiptConfirmation
} packetType;

typedef struct
{
  uint64_t parentAddress; // Address of packet sender which the receiver will save as its parent
} DiscoveryMessageStruct;

typedef struct
{
  uint64_t childAddress; // Temporary address of packet sender which receiver will forward to its parent
} UndiscoveredResponseStruct;

typedef struct
{
  uint64_t temporaryNewAddress; // Address that child had assigned itself
  uint64_t finalNewAddress;     // Final address to assign to new end node
} AssignAddressStruct;

typedef struct
{
  uint16_t temp;        //14 bits from the HDC1010
  uint16_t humidity;   //14 bits from HDC1010
  uint16_t light;      //14 bits from OPT3001
  uint16_t amps; //16 bits ADC from Hall Effect Sensor
  uint16_t motions;    //Number of passerbys detected since last transmission
} SensorDataStruct;

typedef struct
{
  uint64_t confirmerAddress; // Address of node which is sending receipt confirmation
  uint64_t messageHash;
} ReceiptConfirmationStruct;



#endif /* PACKETS_H_ */
