#include <WebServer.h>

ESP8266WebServer webserver(80);

void handleRoot(){
    SPIFFS.begin();
    Serial.println("\nSend 200 on root");
    //webserver.send(200, "text/html", SPIFFS.open("/file.txt", "r"));
    File file = SPIFFS.open("/index.html", "r");
    size_t sent = webserver.streamFile(file, "text/html");
    file.close();

}

void handleCSS(){
    SPIFFS.begin();
    Serial.println("\nSend 200 on root");
    //webserver.send(200, "text/html", SPIFFS.open("/file.txt", "r"));
    File file = SPIFFS.open("/style.css", "r");
    size_t sent = webserver.streamFile(file, "text/css");
    file.close();

}




void initWebServer(){
    
    webserver.on("/", handleRoot);
    webserver.on("/style.css", handleCSS);
    Serial.println("\nStart webserver");
    webserver.begin();

}

void handleClient(){
    webserver.handleClient();
    delay(1);
}