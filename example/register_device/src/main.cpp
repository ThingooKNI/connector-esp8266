#include "ThingooConnector.h"

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>

//SHA1 finger print of certificate
const char* fingerprint = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";

const char* host = "dev.thingoo.xyz";
const char* secret_key = "101ed902-3a95-48b1-b8c6-9a4648151050";

ThingooConnector connector(host);

//=========================================================
//                    Setup                               =
//=========================================================

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting WiFi");
    WiFiManager wifiManager;
    wifiManager.autoConnect("ThingooDevice");

    // connector.set_client_credentials("thingoo-device", SECRET_KEY);
    // connector.set_fingerprint(fingerprint);
    // connector.connect();

    connector.set_client_credentials("thingoo-device", secret_key);
    connector.set_fingerprint(fingerprint);
    Serial.println(connector._get_token());
}

//=======================================================================
//                    Main Loop
//=======================================================================

void loop()
{
}
