#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* mqtt_server = "192.168.1.155";//host of respberry
 
WiFiClient espClient;
PubSubClient client(espClient);

const byte ledStatusSend = 5;//D1
const byte ledStatusOutService = 4;//D2
const byte ledStatusInService= 0;//D3

const byte putRefPositive = 14; //D5
const byte putRefNegative = 12;//D6
const byte statusRefResponse = 13;//D7 

boolean running = false;

//for dummy
char buf[2];
unsigned  long  randNumber;
const char* pubTopic;

void setup() 
{
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  client.setServer(mqtt_server, 1883);
  
  pinMode(ledStatusSend, OUTPUT);
  pinMode(ledStatusOutService, OUTPUT);
  pinMode(ledStatusInService, OUTPUT);
  pinMode(putRefPositive, INPUT);
  pinMode(putRefNegative, INPUT);
  pinMode(statusRefResponse, OUTPUT);
 
  settingWifi();
  settingTopic();
}

void settingTopic()
{
  String topic;
  for (int i = 42; i < 68; ++i){
    char val = char(EEPROM.read(i));
    if(val) {
      topic+=char(EEPROM.read(i));
    }
  }
  topic.trim();
  pubTopic = topic.c_str();
}

void settingWifi()
{
  Serial.println("\nStartup");
  String esid, epass;
  for (int i = 0; i < 16; ++i){
    char val = char(EEPROM.read(i));
    if(val) {
      esid+=char(EEPROM.read(i));
    }
  }
  for (int i = 16; i < 42; ++i){
    char val = char(EEPROM.read(i));
    if(val) {
      epass+=char(EEPROM.read(i));
    }
  }


  if ( esid.length() > 1 ) {
      
      esid.trim();
      epass.trim();
      
      WiFi.begin(esid.c_str(), epass.c_str());
      if ( testWifi() == 20 ) { 
         Serial.println("\nConnected");
         running = true;
      } else {
         Serial.println("\nNo Connected");
      }
  }
  
}

int testWifi(void) 
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");  
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { 
      return(20); 
    } 
    delay(500);
    Serial.print(WiFi.status());    
    c++;
  }
  Serial.println("\nConnect timed out");
  return(10);
} 

void reconnect() 
{
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
    if (Serial.available() > 0)
    {
        String ssid  = Serial.readStringUntil(';');
        Serial.read(); 
        String password = Serial.readStringUntil(';');
        Serial.read(); 
        String topic = Serial.readStringUntil('\n');
        Serial.println("SSID:'"+ssid+"' PASS:'"+password+"' TOPIC:'"+topic+"'");
        cleanDataWifi();
        saveWifiAndTopic(ssid,password, topic);
        
    } 

    if(running) {
        if (!client.connected()) {
          reconnect();
        }
        client.loop();
        
        delay(10000);
        publishData();  
    }
}

void cleanDataWifi()
{
   Serial.println("clearing eeprom");
   for (int i = 0; i < 68; ++i) { EEPROM.write(i, 0); }
   EEPROM.commit();  
}

void saveWifiAndTopic(String ssid,  String password, String topic)
{
      
    for (int i = 0; i < ssid.length(); ++i){ 
       EEPROM.write(i, ssid[i]);
    }
    for (int i = 0; i < password.length(); ++i){
       EEPROM.write(16+i, password[i]);
    }

    for (int i = 0; i < topic.length(); ++i){
      if(topic[i] != '\n') {
        EEPROM.write(42+i, topic[i]);
      }
    }
    
    Serial.println("Save OK"); 
    EEPROM.commit();
}

void publishData()
{
  sleepIntro();
  client.publish(pubTopic, getSensor(), true);
  sleppOutput();
}


char* getSensor()
{//dummy
  
  randNumber = random(10, 35);

  //analogRead(putRefPositive);
  //analogRead(putRefNegative);
  
  return ltoa(randNumber, buf, 10);
}

void sleepIntro()
{
  digitalWrite(ledStatusSend, HIGH);
  delay(1000);
}

void sleppOutput()
{
  delay(600);
  digitalWrite(ledStatusSend, LOW);
}
