# Cliente Nodemcu / Home Environmental

Para poder realizar el censo de los datos ambientales se realiza un pequeño cliente que permite obtener la lectura de un sensor, utilizando el IDE de Arduino para el desarrollo del Software y el Hardware Nodemcu/ESP8266 para la comunicación por medio de una red doméstica WIFI. 

## Dependencias
 - EEPROM
 - ESP8266WiFi
 - PubSubClient
 - Wire
 - WiFiClient 
 - ESP8266WebServer
 
Para mas indicaciones de la libreria del nodemcu para arduino ingresa aquí: [Quick Start to Nodemcu (ESP8266) on Arduino IDE](http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/).


## Configuración
Cuando tengamos todo instalado en nuestro PC debemos quemar el Software utilizando el IDE de Arduino, 
utilizamos la APK para configurar nuestro nodemcu, debemos descargar aquí:

1. Conecte el nodemcu al PC y abra la aplicación en Android, luego precione el boton de buscar, es posible que no encuentre al instante el dispositivo, intente varias veces. 
2. Ingresar los datos de tu red para configurar el nodemcu.
3. Realizar un reset al Nodemcu.
4. Verificar estado en el nodemcu.

**Nota:** El sistema se conecta a un servidor local/remoto con una ip estática, que sería nuestro sistema Raspberry u otro configurado con el proyecto: [Home Environmental](https://github.com/raalzate/home-environmental) trabajado con nodejs.

## Ejemplo

```c++
#include "INodeUH/INodeUH.h"

INodeUH inode("temperatura");//nombre del nodo

void setup() {
  inode.setup();
}

void loop() {

   if(inode.isInterrupt()) { // si aun no se ha configurado
      inode.handleClient(); 
   } else {
     if (!inode.isConnected()) {//se intenta reconectar si no esta conectado
       inode.reconnect();
     }
     //este nodo tiene dos sensores
	 inode.addDataToSensor("temperatura", 20); //agrega el valor para el sensor de temperatura
     inode.addDataToSensor("humedad", 15);//agrega el valor para el sensor de humedad
	 
	 //envia todos los datos de cada sensor, realizado una publicacion 
     inode.publishData();
     
     inode.loop();
   }
}
```

## Diagrama de flujo setup
![Diagrama de flujo setup](https://raw.githubusercontent.com/raalzate/home-environmental-nodemcu/master/asserts/img_setup.png)

## Diagrama de flujo loop
![Diagrama de flujo setup](https://raw.githubusercontent.com/raalzate/home-environmental-nodemcu/master/asserts/img_loop.png)

