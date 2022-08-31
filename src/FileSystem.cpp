#include <FileSystem.h>
#include <ArduinoJson.h>

void initFileSystem()
{
    SPIFFS.begin();
}



void writeJson(byte adress, String answer) {
  DynamicJsonDocument jsonDynDoc(1024);
  File file = SPIFFS.open("/info.json", "r");
  DeserializationError error = deserializeJson(jsonDynDoc, file);
  if (error) {
    Serial.print(F("deserializeJson() Error: "));
    Serial.println(error.f_str());
    return;
  }
  file.close();
  jsonDynDoc["adress_RS485"]=adress;
  jsonDynDoc["answer_RS485"]=answer;
  file = SPIFFS.open("/info.json", "w");
  if (serializeJsonPretty(jsonDynDoc, file)) {
    Serial.println("\nJSON file is written!");
  } else {
    Serial.print ("\nJSON file is not written. :(");
  }
  file.close();
}

