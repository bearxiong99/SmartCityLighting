#ifndef SENSORDATAQUEUE_H_
#define SENSORDATAQUEUE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sysbios/knl/Semaphore.h>
#include "packets.h"


void sensorDataQueueInit();
void enQueue(SensorDataStruct data);
bool deQueue(SensorDataStruct *dataDest);
#ifdef __cplusplus
}
#endif

#endif /* SENSORDATAQUEUE_H_ */
