#include "ThingooConnector.h"

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>

const char* fingerprint = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";
const char* device_id = "thingoo-device";
const char* host = "dev.thingoo.xyz";
const char* secret_key = "101ed902-3a95-48b1-b8c6-9a4648151050";

ThingooConnector connector(host);

void setup()
{
    Serial.begin(115200);
    
    WiFiManager wifiManager;
    wifiManager.autoConnect("ThingooDevice");

    connector.set_client_credentials(device_id, secret_key);
    connector.set_ssl_certificate_fingerprint(fingerprint);
    Serial.println(connector._get_token());
}

void loop()
{
}