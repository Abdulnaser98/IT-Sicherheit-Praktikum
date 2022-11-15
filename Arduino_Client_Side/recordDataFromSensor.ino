#define DIGITAL_PIN D1
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
const char *ssid = "";  //ENTER YOUR WIFI ssid
const char *password = "";  //ENTER YOUR WIFI password
WiFiClient wifiClient;
HTTPClient http;    //Declare object of class HTTPClient


boolean ldr = false;
String light;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
Serial.begin(9600);
pinMode(DIGITAL_PIN, INPUT);
connectWifi();
timeClient.begin();
timeClient.setTimeOffset(3600);


}

//function to connect to wifi
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

void loop() {
  ldr = digitalRead(DIGITAL_PIN);
  String formattedTime;
  String currentDate;
  if (ldr) {
    light = "No";
    formattedTime = getTime();
    Serial.print("Formatted Time: ");
    Serial.println(formattedTime);
    currentDate = getDate();
    Serial.print("Current date: ");
    Serial.println(currentDate);
  }
  else {
    light = "Yes";
    formattedTime = getTime();
    Serial.print("Formatted Time: ");
    Serial.println(formattedTime);
    currentDate = getDate();
    Serial.print("Current date: ");
    Serial.println(currentDate);
}
Serial.print("Light detected: ");
Serial.println(light);
delay(2000);


String sensorData,date,time,postData;
sensorData=light;
date=currentDate;
time=formattedTime;
//Post Data
postData = "sensorData=" +  sensorData + "&date=" + currentDate+ "&time=" + formattedTime;

http.begin(wifiClient,"http://IP-Adress:80/postData.php");            //change the ip to your computer ip address
http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

int httpCode = http.POST(postData);   //Send the request

String payload = http.getString();  //Get the response payload
Serial.println("httpCode is: ");
Serial.println(httpCode);   //Print HTTP return code
Serial.println(payload);    //Print request response payload


http.end();  //Close connection

delay(5000);  //Post Data at every 5 seconds

}


// extarct the current time
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

