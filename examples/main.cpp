#include "ThingooConnector.h"

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>
#include <exception>

const char* fingerprint = "XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX";
const char* device_id = "device_1";
const char* host = "website_address_without_https_or_http"; //example: google.com
const char* secret_key = "some_secret_letters";

ThingooConnector connector(host);

void setup()
{
    Serial.begin(115200);
    
    WiFiManager wifiManager;
    wifiManager.autoConnect("ThingooDevice");

    connector.set_client_credentials(device_id, secret_key);
    connector.set_ssl_certificate_fingerprint(fingerprint);
    connector.connect();
}

void loop()
{
}
