/*
 * mesh.h
 *[]
 *  Created on: Mar 11, 2017
 *      Author: Chris
 */

#ifndef MESH_H_
#define MESH_H_

#include <stdbool.h>

#define DEFAULT_NODE_ADDRESS 0x00
#define MAX_PING_ATTEMPTS 4 // 1 just for debugging purposes
#define MIN_PING_INTERVAL 2 // Min interval between ping attempts in seconds
#define MIN_TIME_TO_REMOVE_CHILD (MAX_PING_ATTEMPTS+1)*MIN_PING_INTERVAL // Parent must receive ping from child within this time
#define SENSOR_TRANSMISSION_INTERVAL 10 // Min # of seconds between each collection and transmission of new sensor data
#define DISCOVERY_MESSAGE_INTERVAL 3 // Min # of seconds between each discovery ping
#define BLOCKING_RECEIVE_TIMEOUT_MS 300 // Timeout for receive in milliseconds

typedef struct address {
    uint8_t addr[8]; // Change this to chosen address length
} address;

typedef struct nodeInfo {
    address own_address; // Address this node is listening on
    address parent_address; // Address of this node's parent node
    int undiscoveredID; // ID of this node if it has not been undiscovered
    bool hasChildOne; // true if node has a child at this address
    bool childOnePinged; // true if child one has pinged since last checked
    bool hasChildTwo;
    bool childTwoPinged;
    bool hasChildThree;
    bool childThreePinged;
    bool inNetwork;
} nodeInfo;

typedef struct gatewayInfo {
    address own_address; // Address this node is listening on
    bool hasChild[6]; // Can have up to 6 children, whose address is index+1
    bool childPinged[6];
} gatewayInfo;

void initMesh();

#endif /* MESH_H_ */
