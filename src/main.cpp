#include <Arduino.h>
#include <WiFiTools.h>
#include <WebServer.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);
  WIFIinit();
  initWebServer();

}

void loop() {
  // put your main code here, to run repeatedly:
  handleClient();
}