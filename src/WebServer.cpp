#include <WebServer.h>
#include <FileSystem.h>
#include <Utils.h>
#include <RS485.h>

ESP8266WebServer webserver(80);
byte adress;

void handleRoot()
{

    SPIFFS.begin();
    // webserver.send(200, "text/html", SPIFFS.open("/file.txt", "r"));
    File file = SPIFFS.open("/index.html", "r");
    size_t sent = webserver.streamFile(file, "text/html");
    file.close();
}

void handleCSS()
{
    SPIFFS.begin();
    // webserver.send(200, "text/html", SPIFFS.open("/file.txt", "r"));
    File file = SPIFFS.open("/style.css", "r");
    size_t sent = webserver.streamFile(file, "text/css");
    file.close();
}

void handleJSON()
{
    SPIFFS.begin();
    // webserver.send(200, "text/html", SPIFFS.open("/file.txt", "r"));
    File file = SPIFFS.open("/info.json", "r");
    size_t sent = webserver.streamFile(file, "text/json");
    file.close();
}

void handleSaveJSON()
{

    String str = webserver.arg("adress");
    adress = stringToByte(str);
    Serial.print("\nadress=");
    Serial.print(adress);

    transmitRS485(adress);
    

    //String answer = webserver.arg("answer");
    float answer=listeningАnswer();
    writeJson(adress, answer);
    webserver.send(200, "text/plain", "OK");
}

void initWebServer()
{

    webserver.on("/", handleRoot);
    webserver.on("/style.css", handleCSS);
    webserver.on("/info.json", handleJSON);
    webserver.on("/saveJSON", handleSaveJSON);
    Serial.println("\nStart webserver");
    webserver.begin();
}

void handleClient()
{
    webserver.handleClient();
    delay(1);
}