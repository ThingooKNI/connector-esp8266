#include <Arduino.h>


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 

#include <ESP8266HTTPClient.h>

#include "ThingooConnector.h"

#include <ArduinoJson.h>


/* Set these to your desired credentials. */
const char *ssid = "huawei";  //YOUR WIFI SETTINGS
const char *password = "12345678";



//SHA1 finger print of certificate
const char fingerprint[] PROGMEM = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";



StaticJsonDocument<2048> doc;


const char* SECRET_KEY = "101ed902-3a95-48b1-b8c6-9a4648151050";


//=========================================================
//                    Setup                               =
//=========================================================



ThingooConnector connector;


void setup() {
    Serial.begin(115200);

  
    WiFi.begin(ssid, password);     //Connect to your WiFi
    Serial.println("");

    Serial.print("Connecting");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    //If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
    
    connector.set_client_credentials("thingoo-device", SECRET_KEY);
    connector.connect();

    



}




//=======================================================================
//                    Main Loop
//=======================================================================
void loop() {
  
}
//=======================================================================