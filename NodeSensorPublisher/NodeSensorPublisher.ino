
#include "INodeUH/INodeUH.h"

INodeUH inode("temperatura");

void setup() {
  inode.setup();
}

void loop() {

   if(inode.isInterrupt()) {
      inode.handleClient(); 
   } else {
     if (!inode.isConnected()) {
       inode.reconnect();
     }
     if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        inode.addDataToSensor("temperatura", 20);
        inode.addDataToSensor("humedad", 15);
        inode.publishData();
     }
     inode.loop();
   }
}

