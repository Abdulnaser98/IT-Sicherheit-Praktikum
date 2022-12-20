#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>

/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/

#ifndef STASSID
#define STASSID "MyAccessPoint"
#define STAPSK  "da433dcc"
#endif

//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "192.168.2.115:8000"
IPAddress remoteIP(192,168,2,115);
int remotePort=8000;

#define socket1 D1
#define socket2 D2
#define socket3 D3
#define socket4 D4


int socket4State = 0;
int socket2State = 0;
int socket3State = 0;
int socket1State = 0;

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);



  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

}


void loop() {

  String jsonStr="{ ";

  int socketStateNew = digitalRead(socket1);
  if (socketStateNew!=socket1State) {
    jsonStr = jsonStr + "\"socket1\":" + socketStateNew+ ",";
    socket1State=socketStateNew;
  }

  socketStateNew = digitalRead(socket2);
  if (socketStateNew!=socket2State) {
    jsonStr = jsonStr + "\"socket2\": " + socketStateNew + ",";
    socket2State=socketStateNew;
  }

  socketStateNew = digitalRead(socket3);
  if (socketStateNew!=socket3State) {
    jsonStr = jsonStr + "\"socket3\": " + socketStateNew + ",";
    socket3State=socketStateNew;
  }

  socketStateNew = digitalRead(socket4);
  if (socketStateNew!=socket4State) {
    jsonStr = jsonStr + "\"socket4\": " + socketStateNew + ",";
    socket4State=socketStateNew;
  }

  jsonStr = jsonStr + " }";


  const char* jsonChar = jsonStr.c_str();

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED) && (strlen(jsonChar)>4)) {

    
    WiFiUDP udp;

    Serial.println("Start to send via UDP");
    Serial.println(jsonStr);
    udp.beginPacket(remoteIP,remotePort);
    udp.write(jsonChar, strlen(jsonChar));
    udp.endPacket();
    
  }

  delay(10000);
}
