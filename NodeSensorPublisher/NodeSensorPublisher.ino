
#include "INodeUH/INodeUH.h";

INodeUH inode("node001-clima", "temperatura,humedad,calidad");

void setup() {
  inode.setup();
}

void loop() {

   if(inode.isConfigurable()) {
      inode.handleClient(); 
   } else {
     if (!inode.isConnected()) {
       inode.reconnect();
     }

     if (Serial.available() > 0) {
         String data = Serial.readStringUntil('\n');
         inode.addDataToSensor("temperatura", data.toFloat());
         inode.addDataToSensor("humedad", data.toFloat());
         inode.publishData();
     }
    
     inode.loop();
   }
}


double getSensorTemperature(){
  return 1;
}

double getSensorHumedad(){
  return 1;
}

double getSensorCalidad(){
  return 1;
}
