#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


// Globals
const char *ssid = "MyAccessPoint1";  //ENTER YOUR WIFI ssid
const char *password = "da433dcc";  //ENTER YOUR WIFI password
const int lightLowerThreshold = 690;
const int lightUpperThreshold = 705;
int prevLightStatus = 0;

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


WiFiClient wifiClient;
HTTPClient http;    //Declare object of class HTTPClient

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");



void setup() {
  Serial.begin(9600);
  connectWifi();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void connectWifi(){
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);   //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);  //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);    //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("trying to connect to wifi router");
  }
  //If connection successful show IP address in serial monitor
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}


String getTime()
{
    timeClient.update();
    String formattedTime = timeClient.getFormattedTime();
    return formattedTime;
}

String getDate()
{
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    time_t rawtime = epochTime;
    struct tm *ptm = gmtime(&rawtime);
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon+1;
    int currentYear = ptm->tm_year+1900;
    String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
    return currentDate;
}

void loop() {
  int sensorValue = analogRead(A0);
  int lightStatus = 0;
  String formattedTime;
  String currentDate;
  if (sensorValue < lightLowerThreshold) {
    lightStatus = 1;
  } else if (sensorValue > lightUpperThreshold) {
    lightStatus = 0;
  } else {
    lightStatus = prevLightStatus;
  }
  
  if (lightStatus != prevLightStatus) {
    String sensorData,currentDate,formattedTime,postData;
    if (lightStatus == 0) {
      sensorData = "No";
    } else {
      sensorData = "Yes";
    }

    formattedTime = getTime();
    Serial.print("Formatted Time: ");
    Serial.println(formattedTime);
    currentDate = getDate();
    Serial.print("Current date: ");
    Serial.println(currentDate);
    
    postData = "sensorData=" +  sensorData + "&date=" + currentDate+ "&time=" + formattedTime;
    Serial.println(postData);
    
    http.begin(wifiClient,"http://192.168.178.35/postData.php");            //change the ip to your computer ip address
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
    
    int httpCode = http.POST(postData);   //Send the request
    
    String payload = http.getString();  //Get the response payload
    Serial.println("httpCode is: ");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    
    
    http.end();  //Close connection
  }

  prevLightStatus = lightStatus;
}