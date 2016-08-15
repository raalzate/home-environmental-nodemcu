# Cliente Nodemcu / Home Environmental

Para poder realizar el censo de los datos ambientales se realiza un pequeño cliente que permite obtener la lectura de un sensor, utilizando el IDE de Arduino para el desarrollo del Software y el Hardware Nodemcu/ESP8266 para la comunicación por medio de una red doméstica WIFI. 

## Dependencias
  - Nodemcu v3
  - Arduino IDE
  - Librerias ESP8266
 
Para mas indicaciones de las librerias puedes ingresa aquí: [Quick Start to Nodemcu (ESP8266) on Arduino IDE](http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/).


## Configuración
Cuando tengamos todo instalado en nuestro PC debemos quemas el Software utilizando el IDE de Arduino, luego de grabar el firmware debemos continuar los siguiente pasos:

1. Abrir una consula o una terminal putty con una frecuencia de velocidad 115200. 
2. Ingresar los datos de tu red de la siguiete forma SSID;PASSWORD;TOPIC, ejemplo FamAlzate;111222333;temperatura.
3. Realizamos un reset al Nodemcu.

**Nota:** El sistema se conecta a un servidor local con una ip estatica, que seria nuestro sistema Raspberry configurado con el proyecto: [Home Environmental](https://github.com/raalzate/home-environmental) trabajado con nodejs.

## Diagrama de flujo setup
![Diagrama de flujo setup](https://raw.githubusercontent.com/raalzate/home-environmental-nodemcu/master/asserts/img_setup.png)

## Diagrama de flujo loop
![Diagrama de flujo setup](https://raw.githubusercontent.com/raalzate/home-environmental-nodemcu/master/asserts/img_loop.png)

