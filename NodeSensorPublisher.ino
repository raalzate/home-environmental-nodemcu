#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
 
// Connect to the WiFi
const char* ssid = "ALZATE";
const char* password = "1115069076";

const char* mqtt_server = "192.168.1.155";//host of respberry

//Feature drive
const char* topic = "temperatura";
 
WiFiClient espClient;
PubSubClient client(espClient);

const byte ledStatusSend = 5;//D1
const byte ledStatusOutService = 4;//D2
const byte ledStatusInService= 0;//D3

const byte putRefPositive = 14; //D5
const byte putRefNegative = 12;//D6
const byte statusRefResponse = 13;//D7  

//for dummy
char buf[2];
unsigned  long  randNumber;

void setup()
{
 
 Serial.begin(9600);
 
 client.setServer(mqtt_server, 1883);
 
 pinMode(ledStatusSend, OUTPUT);
 pinMode(ledStatusOutService, OUTPUT);
 pinMode(ledStatusInService, OUTPUT);
 pinMode(putRefPositive, INPUT);
 pinMode(putRefNegative, INPUT);
 pinMode(statusRefResponse, OUTPUT);
 
}

void reconnect() {
 while (!client.connected()) {
 Serial.println("Server MQTT connection...");
 if (client.connect("ESP8266 Client")) {
    Serial.println("connected");
    digitalWrite(ledStatusOutService, LOW);
    digitalWrite(ledStatusInService, HIGH);
 } else {
    digitalWrite(ledStatusOutService, HIGH);
    digitalWrite(ledStatusInService, LOW);
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    delay(5000);
  }
 }
}
 
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  delay(10000);
  publishData();
}

void publishData(){
  sleepIntro();
  client.publish(topic, getSensor(), true);
  sleppOutput();
}


char* getSensor(){//dummy
  
  randNumber = random(10, 35);

  //analogRead(putRefPositive);
  //analogRead(putRefNegative);
  
  return ltoa(randNumber, buf, 10);
}

void sleepIntro(){
  digitalWrite(ledStatusSend, HIGH);
  delay(1000);
}

void sleppOutput(){
  delay(600);
  digitalWrite(ledStatusSend, LOW);
}
