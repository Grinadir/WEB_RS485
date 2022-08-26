#include <Arduino.h>
#include <WiFiTools.h>
#include <WebServer.h>
#include <RS485.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);
  WIFIinit();
  initWebServer();

}

void loop() {
  // put your main code here, to run repeatedly:
  //handleClient();
  //delay(5000);
  #if 1
  intitRS485();
  transmitRS485();
  listeningАnswer();




  #endif
}