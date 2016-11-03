
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

     delay(90000);
     //obtener datos de los sensores
     inode.addDataToSensor("temperatura", getSensorTemperature());
     inode.addDataToSensor("humedad", getSensorHumedad());
     inode.addDataToSensor("calidad", getSensorCalidad());
     
     inode.publishData();
     
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
