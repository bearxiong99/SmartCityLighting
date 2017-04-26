/*
  PubNub sample client

  This sample client will publish raw (JSON pre-encoded) PubNub messages.

  Circuit:
  * (Optional.) Analog sensors on pins A0 to A5.
  * (Optional.) LED on pin 9 for success indication.

  created 23 October 2012
  by Petr Baudis

  https://github.com/pubnub/pubnub-api/tree/master/arduino
  This code is in the public domain.
  */

#include "sensorDataQueue.h"
#include "packets.h"
#include <SPI.h>
#include <WiFi.h>
#include <PubNub.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Timestamp.h>
extern Semaphore_Handle WaitForWiFi;
extern Semaphore_Handle WaitForPacket;

extern uint16_t value[6];
extern unsigned long startPublish;

const int pubLedPin = RED_LED;

char pubkey[] = "pub-c-0fc9c75c-df2f-4962-a505-590dc291f714";
char subkey[] = "sub-c-87a6994c-1ae8-11e7-aca9-02ee2ddab7fe";
char channel[] = "scls";

SensorDataStruct dataPacket;

// your network name also called SSID
char ssid[] = "Justin's iPhone";
// your network password
char password[] = "launchpad";

void setup()
{
  initGlobals();

  Serial.begin(115200);

  pinMode(pubLedPin, OUTPUT);
  digitalWrite(pubLedPin, LOW);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  unsigned long StartTime = millis();
  WiFi.begin(ssid, password);
  Serial.acquire();
  
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  Serial.release();
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  unsigned long EndTime = millis();

  Serial.println("\nIP Address obtained");
  // We are connected and have an IP address.
  // Print the WiFi status.
  printWifiStatus();

  Serial.print("Time to connect (in ms): ");
  unsigned long ElapsedTime = EndTime - StartTime;
  Serial.println(ElapsedTime);

  PubNub.begin(pubkey, subkey);
  Serial.println("PubNub set up");

  Semaphore_post(WaitForWiFi);
}

void flash(int ledPin)
{
  /* Flash LED three times. */
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

void loop()
{

    if(deQueue(&dataPacket)) {
        WiFiClient *client;
        value[0] = dataPacket.temp;
        value[1] = dataPacket.humidity;
        value[2] = dataPacket.light;
        value[3] = dataPacket.operational;
        value[4] = dataPacket.motions;
        value[5] = dataPacket.id;
        char msg[64] = "{\"sensor_data\":[";
        System_sprintf(msg + strlen(msg), "%d", value[0]);
        strcat(msg, ",");
        System_sprintf(msg + strlen(msg), "%d", value[1]);
        strcat(msg, ",");
        System_sprintf(msg + strlen(msg), "%d", value[2]);
        strcat(msg, ",");
        System_sprintf(msg + strlen(msg), "%d", value[3]);
        strcat(msg, ",");
        System_sprintf(msg + strlen(msg), "%d", value[4]);
        strcat(msg, ",");
        System_sprintf(msg + strlen(msg), "%d", value[5]);
        strcat(msg, "]}");
        #ifdef __DEBUGGING__
        Serial.print("publishing message: ");
        Serial.println(msg);
        #endif
        client = PubNub.publish(channel, msg);
        if (!client) {
          Serial.println("publishing error");
        } else {
          unsigned long publishTime = millis() - startPublish;
          flash(pubLedPin);
          client->stop();
        }
    }
}
  
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

