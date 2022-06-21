#include <WiFiTools.h>

IPAddress apIP(192, 168, 4, 1);

String _ssid1 = "SAURES_R1";      //
String _password1 = "1400266140"; //
String _ssid2 = "MGTS_GPON_1E14";
String _password2 = "yWbP7Ckp";
String _ssidAP = "ESP8266_testing";
String _passwordAP = "";

bool tryConnect(String ssid, String pass, byte tries)
{
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.printf("Try to connect to %s\n", ssid.c_str());
    while (--tries && WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    if(WiFi.status() != WL_CONNECTED){
        Serial.printf("\nConnect to %s failed\n", ssid.c_str());
        WiFi.disconnect();
        return false;
    }
    Serial.printf("\nConnected to %s\n", ssid.c_str());
    Serial.print("IP address: http://");
    Serial.println(WiFi.localIP());
    return true;
}

bool StartAPMode()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
    return true;

}

void WIFIinit()
{
    WiFi.mode(WIFI_STA);
    byte tries = 20;
    
    if(!tryConnect(_ssid1,_password1, tries)){
        if(!tryConnect(_ssid2, _password2,tries)){
            StartAPMode();
        }
    }


}