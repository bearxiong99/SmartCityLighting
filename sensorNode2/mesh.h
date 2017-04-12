/*
 * mesh.h
 *
 *  Created on: Mar 11, 2017
 *      Author: Chris
 */

#ifndef MESH_H_
#define MESH_H_

#include <stdbool.h>

#define DEFAULT_NODE_ADDRESS 0x00
#define MAX_PING_ATTEMPTS 4 // 1 just for debugging purposes
#define MIN_PING_INTERVAL 2 // Min interval between ping attempts in seconds

#define BLOCKING_RECEIVE_TIMEOUT_MS 300 // Timeout for receive in milliseconds

typedef struct address {
    uint8_t addr[8]; // Change this to chosen address length
} address;

typedef struct nodeInfo {
    address own_address; // Address this node is listening on
    address parent_address; // Address of this node's parent node
    int undiscoveredID; // ID of this node if it has not been undiscovered
    bool hasChildOne;
    bool hasChildTwo;
    bool hasChildThree;
    bool inNetwork;
} nodeInfo;




void initMesh();

#endif /* MESH_H_ */
