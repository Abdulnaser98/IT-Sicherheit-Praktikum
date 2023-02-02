#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "MyAccessPoint"
#define STAPSK  "0123asdf"
#endif

// imaginary server address
#define SERVER_IP "192.168.2.115:8000"
IPAddress remoteIP(192,168,2,115);
int remotePort=8000;

#define socket1 D1
#define socket2 D2
#define socket3 D3
#define socket4 D4

String deviceName = "Optokoppler-Arduino";

String socket1State = "undefined";
String socket2State = "undefined";
String socket3State = "undefined";
String socket4State = "undefined";

void setup() {

  Serial.begin(115200);

  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  
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

String newState(int state) {
  if (state == 1) return "off";
  if (state == 0) return "on";
  else return "undefined";
}

String makePayload(const String &value, const String &sensor) {
    DynamicJsonDocument payload(1024);
    payload["device"] = deviceName;
    payload["sensor"] = sensor.c_str();
    payload["value"] = value.c_str();

    char result[1024];
    serializeJson(payload, result);
    return result;
}

void sendMessage(const String &str) {
    // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    
    WiFiUDP udp;

    Serial.println("Start to send via UDP");
    udp.begin(8888);
    udp.beginPacket(remoteIP,remotePort);
    udp.write(str.c_str(), strlen(str.c_str()));
    udp.endPacket();
    
  }
}

void printConsole(const String &newState, const String &oldState, const int socket){
  Serial.print("socket");
  Serial.print(socket);
  Serial.print(" old: ");
  Serial.print(oldState);
  Serial.print(" ; ");
  Serial.print(" new: ");
  Serial.print(newState);
  Serial.println("");
}

void loop() {


  String socketStateNew = newState(digitalRead(socket1));
  // printConsole(socketStateNew, socket1State, 1);
  if (socketStateNew!=socket1State) {
    String payload = makePayload(socketStateNew,"SmartSocket1");
    Serial.println(payload);
    sendMessage(payload);
    socket1State=socketStateNew;
  }

  socketStateNew = newState(digitalRead(socket2));
  // printConsole(socketStateNew, socket2State, 2);
  if (socketStateNew!=socket2State) {
    String payload = makePayload(socketStateNew,"Lampe1");
    Serial.println(payload);
    sendMessage(payload);
    socket2State=socketStateNew;
  }

  socketStateNew = newState(digitalRead(socket3));
  // printConsole(socketStateNew, socket3State, 3);
  if (socketStateNew!=socket3State) {
    String payload = makePayload(socketStateNew,"SmartSocket2");
    Serial.println(payload);
    sendMessage(payload);
    socket3State=socketStateNew;
  }

  socketStateNew = newState(digitalRead(socket4));
  // printConsole(socketStateNew, socket4State, 4);

  if (socketStateNew!=socket4State) {
    String payload = makePayload(socketStateNew,"Lampe2");
    Serial.println(payload);
    sendMessage(payload);
    socket4State=socketStateNew;
  }

  delay(100);
}
