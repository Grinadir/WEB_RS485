#include <FileSystem.h>
#include <ArduinoJson.h>

void initFileSystem()
{
    SPIFFS.begin();
}



void writejson(String request, String answer) {
  DynamicJsonDocument jsonDynDoc(1024);
  File file = SPIFFS.open("/info.json", "r");
  DeserializationError error = deserializeJson(jsonDynDoc, file);
  if (error) {
    Serial.print(F("deserializeJson() Error: "));
    Serial.println(error.f_str());
    return;
  }
  file.close();
  jsonDynDoc["request_RS485"]=request;
  jsonDynDoc["answer_RS485"]=answer;
  file = SPIFFS.open("/info.json", "w");
  if (serializeJsonPretty(jsonDynDoc, file)) {
    Serial.println("\nJSON file is written!");
  } else {
    Serial.print ("\nJSON file is not written. :(");
  }
  file.close();
}

