
#ifndef INodeUH_h

#define INodeUH_h

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "IConstants.h"

class INodeUH
{
  
	public: INodeUH(String nameNode);

	void setup();

	void reconnect();

	bool isInterrupt(void);

	bool isConnected(void);

	void handleClient();

	void publish(String data);

	void loop();

	private: void settingPinMode();
	private: void settingWifi();
	private: void publishRegister();
	private: void sleepIntro();
	private: void sleppOutput();
	private: int isValidWifi();
	private: void findSsidAndPassword();
	private: void settingAccessPoint();
	private: void cleanDataWifi();
	private: void saveWifiAndTopic(String ssid,  String password);
	private: void handleRegisterAuthWiFi();

	private: String _essid; 
	private: String _epass;
	private: String _nameNode;
	private: bool _interrupt;
	
};

#endif

