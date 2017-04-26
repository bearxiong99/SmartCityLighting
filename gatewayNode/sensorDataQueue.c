#include "packets.h"
#include "sensorDataQueue.h"
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>

#define QUEUE_CAPACITY 4
extern Semaphore_Handle queueSem;

SensorDataStruct s[QUEUE_CAPACITY];
uint32_t firstUsed;
uint32_t firstFree;
bool full;

void sensorDataQueueInit() {
  firstUsed = 0;
  firstFree = 0;
  full = false;
}

void enQueue(SensorDataStruct dPacket) {
    Semaphore_pend(queueSem, BIOS_WAIT_FOREVER);
    if(!full) {
      s[firstFree].temp =  dPacket.temp;
      s[firstFree].humidity = dPacket.humidity;
      s[firstFree].light = dPacket.light;
      s[firstFree].operational = dPacket.operational;
      s[firstFree].motions = dPacket.motions;
      s[firstFree].temp = dPacket.temp;
      s[firstFree].id = dPacket.id;

      firstFree = (firstFree + 1) % QUEUE_CAPACITY;
      if(firstFree == firstUsed) {
        full = true;
      }
    }

    else {
      s[firstFree].temp =  dPacket.temp;
      s[firstFree].humidity = dPacket.humidity;
      s[firstFree].light = dPacket.light;
      s[firstFree].operational = dPacket.operational;
      s[firstFree].motions = dPacket.motions;
      s[firstFree].temp = dPacket.temp;
      s[firstFree].id = dPacket.id;
      firstUsed = (firstUsed + 1) % QUEUE_CAPACITY;
      firstFree = (firstFree + 1) % QUEUE_CAPACITY;
    }

    Semaphore_post(queueSem);
}

// Returns false if nothing to dequeue
bool deQueue(SensorDataStruct *dataDest) {
    Semaphore_pend(queueSem, BIOS_WAIT_FOREVER);
    if(firstUsed == firstFree) {
      if(!full) {

        Semaphore_post(queueSem);
        return false;
      }
    }

    dataDest->temp = s[firstUsed].temp;
    dataDest->humidity =s[firstUsed].humidity;
    dataDest->light = s[firstUsed].light;
    dataDest->operational = s[firstUsed].operational;
    dataDest->motions = s[firstUsed].motions;
    dataDest->temp = s[firstUsed].temp;
    dataDest->id = s[firstUsed].id;
    
    full = false;
    firstUsed = (firstUsed + 1) % QUEUE_CAPACITY;
    Semaphore_post(queueSem);
}

