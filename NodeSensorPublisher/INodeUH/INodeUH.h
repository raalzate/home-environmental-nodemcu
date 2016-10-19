
#ifndef INodeUH_h

#define INodeUH_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Wire.h>
#include <WiFiClient.h> 
#include <PubSubClient.h>

#include "IConstants.h"

class INodeUH
{
  
	public: INodeUH();

	void setup();

	void reconnect();

	bool isInterrupt(void);

	void handleClient();

	void publish(String data);

	private: String _essid; 
	private: String _epass;
	private: String _nameNode;
	private: bool _interrupt;
	
};

#endif

