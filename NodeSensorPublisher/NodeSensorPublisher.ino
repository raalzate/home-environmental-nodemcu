
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
     Serial.flush();
     if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        inode.publish(data);
     }
     inode.loop();
   }
}

