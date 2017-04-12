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
#include "mesh.h"
extern uint8_t* dataArray;
typedef enum
{
  DiscoveryMessage = 0, // Initial ping from in-network nodes to undiscovered nodes
  UndiscoveredResponse = 1, // Response from an undiscovered node after receiving DiscoveryMessage
  AssignAddress = 2, // AddressAssignment originating from gateway node to undiscovered node after UndiscoveredResponse
  SensorData = 3, // Data originating from a sensor node heading towards gateway node
  ReceiptConfirmation = 4, // Response from a node confirming receipt of a given message
  ParentalPing = 5 // Check to see if parent sends ReceiptConfirmation
} packetType;

typedef struct
{
    address parentAddress; // Address of packet sender which the receiver will save as its parent
} DiscoveryMessageStruct;

typedef struct
{
    int undiscoveredID; // Self assigned ID of packet sender which receiver will forward to its parent
} UndiscoveredResponseStruct;

typedef struct
{
    int undiscoveredID; // Self assigned ID that child had send to parent
    address parentAddress;
    address finalAddress;     // Final address to assign to new child node
} AssignAddressStruct;

typedef struct
{
    uint16_t temp;        //14 bits from the HDC1010
    uint16_t humidity;   //14 bits from HDC1010
    uint16_t light;      //14 bits from OPT3001
    uint16_t amps; //16 bits ADC from Hall Effect Sensor
    uint16_t motions;    //Number of passers-by detected since last transmission
} SensorDataStruct;

typedef struct {
    packetType t; // The type of packet that was just received
} ReceiptConfirmationStruct;

typedef struct
{
    address childAddress;
} ParentalPingStruct;

#endif /* PACKETS_H_ */
