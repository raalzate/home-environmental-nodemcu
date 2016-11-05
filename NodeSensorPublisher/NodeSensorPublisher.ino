
#include "INodeUH/INodeUH.h";

#include <DHT.h>

#define DHTPIN 12 //D6
#define PUT_QUALITY A0
#define DHTTYPE DHT11 

INodeUH inode("node002-ambiente", "temperatura,humedad,calidad");
DHT dht(DHTPIN, DHTTYPE);

void setup() {
   dht.begin();
  inode.setup();
}

void loop() {

   if(inode.isConfigurable()) {
      inode.handleClient(); 
   } else {
     if (!inode.isConnected()) {
       inode.reconnect();
     }
     delay(5000);
     inode.addDataToSensor("temperatura", getSensorTemperature());
     inode.addDataToSensor("humedad", getSensorHumedad());
     inode.addDataToSensor("calidad", getSensorCalidad());
     inode.publishData();
     inode.loop();
   }
}


double getSensorTemperature()
{
  double t = dht.readTemperature();
  if (isnan(t)) {
      getSensorTemperature();
  } 
  return t;
}

double getSensorHumedad()
{
  double h = dht.readHumidity();
  if (isnan(h)) {
     getSensorHumedad();
  }
  return h;
}

double getSensorCalidad()
{
  return String(analogRead(PUT_QUALITY)).toFloat();
}
