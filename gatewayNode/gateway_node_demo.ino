
/*
  EasyLinkRx
  
  A basic EasyLink Receive example..
  Receive a packet and print the 16-bit value stored in the payload.
  This Sketch is the counterpart of the EasyLinkTx example.
  
  Hardware Required:
  * CC1310 LaunchPad
  
  This example code is in the public domain.
*/

#include "EasyLink.h"
#include "packets.h"
#include "sensorDataQueue.h"
#include <WiFi.h>

EasyLink_RxPacket rxPacket;
EasyLink myLink;

extern Semaphore_Handle WaitForWiFi;
extern Semaphore_Handle WaitForPacket;

uint32_t dataIndex;

uint8_t gateway_addr[8] = {0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
SensorDataStruct dPacket;

void setup() {

  initGlobals();

  Serial.begin(9600);
  Serial.acquire();
  Serial.println("\nWaiting for WiFi...");

  Serial.release();
  
  Semaphore_pend(WaitForWiFi, BIOS_WAIT_FOREVER);

  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  int result1 = EasyLink_setCtrl(EasyLink_Ctrl_AddSize, 8);
  int result2 = EasyLink_enableRxAddrFilter(&gateway_addr[0], 8, 1);
  Serial.print("result1: ");
  Serial.print(result1);
  Serial.print("  result2: ");
  Serial.println(result2);
  Serial.println(myLink.version());
  
}

uint16_t value[6];
unsigned long startPublish; 
uint16_t i = 1;


/*void loop() {

  value[0] = i; //value[0] contains test packet id 
  value[1] = i;
  value[2] = i;
  value[3] = i;
  value[4] = i;
  Semaphore_post(WaitForPacket);
  i++;
  
}*/

void loop() {
  // Wait / block for 2 second to receive a packet.
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(2000);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);

  EasyLink_Status status = myLink.receive(&rxPacket);
  
  if (status == EasyLink_Status_Success) {    

    
    uint16_t temp = ((uint16_t)rxPacket.payload[2]<<8) + rxPacket.payload[3];
    uint16_t humidity = ((uint16_t)rxPacket.payload[4]<<8) + rxPacket.payload[5];
    uint16_t light = ((uint16_t)rxPacket.payload[6]<<8) + rxPacket.payload[7];
    uint16_t operational = ((uint16_t)rxPacket.payload[8]<<8) + rxPacket.payload[9];
    uint16_t motion = ((uint16_t)rxPacket.payload[10]<<8) + rxPacket.payload[11];
    uint16_t id = ((uint16_t) rxPacket.payload[12]<<8) + rxPacket.payload[13];

    dPacket.temp = temp;
    dPacket.humidity = humidity;
    dPacket.light = light;
    dPacket.operational = operational;
    dPacket.motions = motion;
    dPacket.temp = temp;
    dPacket.id = id;
    
    Serial.print("Packet received with length ");
    Serial.print(rxPacket.len);
    Serial.print(" and value ");
    Serial.print(temp);
    Serial.print(", ");
    Serial.print(humidity); 
    Serial.print(", ");
    Serial.print(light); 
    Serial.print(", ");
    Serial.print(operational);
    Serial.print(", ");
    Serial.print(motion);
    Serial.print(", ");
    Serial.print(id);
    
    Serial.println();

    enQueue(dPacket);

  } else {

    Serial.print("Error receiving packet with status code: ");
    Serial.print(status);
    Serial.print(" (");
    Serial.print(myLink.getStatusString(status));
    Serial.println(")");
  }

  /*
  dPacket.id = 4;

  dPacket.temp = 10000;
  dPacket.light = 89;
  dPacket.operational = 1;
  dPacket.motions = 100000;



  enQueue(dPacket);
  delay(10000);
  */
}
