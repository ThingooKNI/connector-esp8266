/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#ifndef ThingooConnector_h
#define ThingooConnector_h

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>

class ThingooConnector {

public:
    ThingooConnector(const char* host);

    void set_client_credentials(String client_id, String secret_key);
    void set_fingerprint(const char* fingerprint);
    void api_request();
    void connect();

    HTTPClient http;

    StaticJsonDocument<2048> doc;
    int https_port; //HTTPS=443
    const char* host;
    String register_endpoint;
    String readings;
    String devices;
    void _get_token();

private:
    const char* _host;
    const char* _fingerprint;
    String _secret_key;
    String _client_id;
    String _access_token;
};

#endif
