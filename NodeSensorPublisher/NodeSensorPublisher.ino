#include <ESP8266WiFi.h>
#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  settingWifi();
 
}

void settingWifi()
{
  Serial.println("\nStartup");
  String esid, epass, topic;
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

  for (int i = 42; i < 68; ++i){
    char val = char(EEPROM.read(i));
    if(val) {
      topic+=char(EEPROM.read(i));
    }
  }

  if ( esid.length() > 1 ) {
      
      esid.trim();
      epass.trim();
      topic.trim();
      
      WiFi.begin(esid.c_str(), epass.c_str());
      if ( testWifi() == 20 ) { 
         Serial.println("\nConnected");
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
  Serial.println("Connect timed out");
  return(10);
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
