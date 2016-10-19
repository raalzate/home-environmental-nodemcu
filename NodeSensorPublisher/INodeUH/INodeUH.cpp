#include "INodeUH.h"


WiFiClient       espClient;
ESP8266WebServer server(80);
PubSubClient     client(espClient);

INodeUH::INodeUH(String nameNode)
{
	_nameNode = nameNode;
}

void INodeUH::setup()
{
  delay(1000);
  Serial.begin(9600);

  settingPinMode();
  settingWifi();
}

bool INodeUH::isInterrupt(void)
{
 	return _interrupt;
}

void INodeUH::handleClient()
{
	 inode.handleClient(); 
}

void INodeUH::reconnect()
{
   Serial.println("\nServer MQTT Connecting..");
   while (!client.connected()) {
     Serial.print(".");
     if (client.connect("ESP8266 Client")) {
        Serial.println(" Connected MQTT!");
        digitalWrite(LED_STATUS_OUTSERVICE, LOW);
        digitalWrite(LED_STATUS_INSERVICE, HIGH);
        publishRegister();
        delay(1000); 
        Serial.swap();
     } else {
        digitalWrite(LED_STATUS_OUTSERVICE, HIGH);
        digitalWrite(LED_STATUS_INSERVICE, LOW);
        Serial.print(" failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);
      }
   }
}

void INodeUH::publish(String data)
{
   sleepIntro();
   client.publish(_nameNode.c_str(),data.c_str(), true);
   sleppOutput();
}


void publishRegister()
{
  client.publish("register",_nameNode.c_str(), true);
}

void sleepIntro()
{
  digitalWrite(LED_STATUS_SEND, HIGH);
  delay(10);
}

void sleppOutput()
{
  delay(600);
  digitalWrite(LED_STATUS_SEND, LOW);
}

void settingPinMode()
{
  pinMode(LED_STATUS_SEND, OUTPUT);
  pinMode(LED_STATUS_OUTSERVICE, OUTPUT);
  pinMode(LED_STATUS_INSERVICE, OUTPUT);
}

void settingWifi()
{

  client.setServer(MQTT_SERVER, 1883);
  Serial.println("\nStartup");  
  findSsidAndPassword();
  if (_essid.length() > 1 ) {
      WiFi.begin(_essid.c_str(), _epass.c_str());
      if (isValidWifi() == 20 ) { 
         Serial.print("\nConnected WIFI.");
      } else {
         Serial.println("\nNo Connected. {"+_essid+"}");
         _interrupt = 1;
         settingAccessPoint();
      }
  }  else {
      _interrupt = 1;
      Serial.println("\nNo Connected.");
      settingAccessPoint();
  }

}

int isValidWifi(void) 
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");  
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { 
      return(20); 
    } 
    delay(500);
    Serial.print(".");    
    c++;
  }
  Serial.println("\nConnect timed out");
  return(10);
} 

void findSsidAndPassword()
{

  EEPROM.begin(512);
  for (int i = 0; i < 16; ++i){
    _essid+=char(EEPROM.read(i));    
  }
  for (int i = 16; i < 42; ++i){
    _epass+=char(EEPROM.read(i));
  }
  EEPROM.end();
}



void settingAccessPoint()
{

  WiFi.softAP(AP_SSID, AP_PASSWORD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRegisterAuthWiFi);
  server.begin();
  Serial.println("HTTP server started");
}


void cleanDataWifi()
{
   EEPROM.begin(512);
   Serial.println("Clearing eeprom");
   for (int i = 0; i < 68; ++i) { EEPROM.write(i, 0); }
   EEPROM.commit(); 
   EEPROM.end();
}

void saveWifiAndTopic(String ssid,  String password)
{
  EEPROM.begin(512);  
  for (int i = 0; i < ssid.length(); ++i){ 
    EEPROM.write(i, ssid[i]);
  }
  for (int i = 0; i < password.length(); ++i){
    EEPROM.write(16+i, password[i]);
  }

  Serial.println("Save OK"); 
  EEPROM.commit();
  EEPROM.end(); 
}

void handleRegisterAuthWiFi() {

  String argSSID     = server.arg("ssid");
  String argPassword = server.arg("password");
  String reqJson     = "{'status':'success', 'ssid': '"+argSSID+"', 'password': '"+argPassword+"'}";
  cleanDataWifi();
  saveWifiAndTopic(argSSID,argPassword);
  
  server.send(200, "application/json",  reqJson);
  
  WiFi.disconnect();
  delay(1000);
  ESP.restart();
}



