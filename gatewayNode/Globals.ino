#include "sensorDataQueue.h"

Semaphore_Handle WaitForPacket;
Semaphore_Handle WaitForWiFi;
Semaphore_Handle queueSem;

bool initialized = false;

void initGlobals()
{
  if(initialized) return;
  initialized = true;
  
  WaitForWiFi = Semaphore_create(0, NULL, NULL);
  WaitForPacket = Semaphore_create(0, NULL, NULL);
  queueSem = Semaphore_create(0, NULL, NULL);
  
  Semaphore_post(queueSem);
  Serial.print("Globalsinitialized");
  sensorDataQueueInit();
}

