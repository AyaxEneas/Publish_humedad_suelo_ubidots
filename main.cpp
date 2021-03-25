#include <Arduino.h>
/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include "PubSubClient.h"
//#define espresssif8266  "605bbf621d847227d4932a04"  // Put here your Ubidots device label
//#define HUMEDAD  "605bbf891d84722a88fa1676"  // Put here your Ubidots variable l
/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-ioOJegGELrwRZCiITyDCYco2Xpuj1h" // Your Ubidots TOKEN
#define WIFINAME "Fibertel WiFi629 2.4GHz" //Your SSID
#define WIFIPASS "0043413909" // Your Wifi Pass
#define Blue_led 2
Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0]=='1'){
    digitalWrite(led, HIGH);
  }
  else{
  digitalWrite(led, LOW);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  //client.ubidotsSetBroker("industrial.api.ubidots.com"); // Sets the broker properly for the industrial account
  //client.ubidotsSetBroker("industrial.api.ubidots.com"); // Sets the broker properly for the Industrial account
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client.ubidotsSubscribe(interruptor, LED);
  pinMode(Blue_led,OUTPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe(interruptor, LED);
      }

 // float Hum = analogRead(A0);
  //client.add("HUMEDAD", Hum);
  //client.ubidotsPublish("espresssif8266");
  client.loop();



}
