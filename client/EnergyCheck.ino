#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/

#ifndef STASSID
#define STASSID "[ssid]"
#define STAPSK  "[pw]"
#endif

//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "[server-ip]"

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

  DynamicJsonDocument changedValues(1024);

  int socketStateNew = digitalRead(socket1);
  if (socketStateNew!=socket1State) {
    changedValues["socket1"] = socketStateNew;
    socket1State=socketStateNew;
  }

  socketStateNew = digitalRead(socket2);
  if (socketStateNew!=socket2State) {
    changedValues["socket2"] = socketStateNew;
    socket2State=socketStateNew;
  }

  socketStateNew = digitalRead(socket3);
  if (socketStateNew!=socket3State) {
    changedValues["socket3"] = socketStateNew;
    socket3State=socketStateNew;
  }

  socketStateNew = digitalRead(socket4);
  if (socketStateNew!=socket4State) {
    changedValues["socket4"] = socketStateNew;
    socket4State=socketStateNew;
  }

  String changedJson;
  serializeJson(changedValues, changedJson); 

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED) && (changedJson!="null")) {

    WiFiClient client;
    HTTPClient http;

    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/postplain/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");

    // start connection and send HTTP header and body
    int httpCode = http.POST(changedJson);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
