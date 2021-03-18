// #include "ThingooConnector.h"

#include <Arduino.h>
#include <WiFiClientSecure.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>




//SHA1 finger print of certificate
const uint8_t fingerprint[20] = {0xF6, 0x23, 0x3E, 0xAC, 0x7A, 0x1D, 0x03, 0x63, 0x15, 0xE2, 0x4F, 0x57, 0xB6, 0x10, 0x23, 0x2E, 0x22, 0x53, 0x51, 0x4E};


const char* SECRET_KEY = "101ed902-3a95-48b1-b8c6-9a4648151050";


//=========================================================
//                    Setup                               =
//=========================================================



// ThingooConnector connector;


void setup() {
    Serial.begin(115200);

  
    Serial.begin(115200);
    Serial.println("Starting WiFi");
 
    WiFiManager wifiManager;
    wifiManager.autoConnect("ThingooDevice");

    
    // connector.set_client_credentials("thingoo-device", SECRET_KEY);
    // connector.set_fingerprint(fingerprint);
    // connector.connect();

    



}




//=======================================================================
//                    Main Loop
//=======================================================================
void loop() {
  
}
//=======================================================================