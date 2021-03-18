/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#include "ThingooConnector.h"

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>

ThingooConnector::ThingooConnector(const char* host)
{

    https_port = 443; //HTTPS= 443
    register_endpoint = "/auth/realms/Thingoo/protocol/openid-connect/token";
    readings = "/readings";
    devices = "/devices";
    _host = host;
}

void ThingooConnector::set_client_credentials(String client_id, String secret_key)
{

    _client_id = client_id;
    _secret_key = secret_key;
}

void ThingooConnector::set_fingerprint(const char* fingerprint)
{
    _fingerprint = fingerprint;
}

void ThingooConnector::_get_token()
{
    /*
        Get OAuth access token
        :return: :class:`Token`
        :raises: :class:`RetrieveTokenException`
        */
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    Serial.println("Sending HTTPS request");
    client->setFingerprint(_fingerprint);
    String token_endpoint = "https://" + (String)_host + register_endpoint;
    http.begin(*client, token_endpoint);
    //http.addHeader("Content-Type", "application/json");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String http_request_data = "grant_type=client_credentials&client_id=" + _client_id + "&client_secret=" + _secret_key;

    // Send HTTP POST request
    int http_response_code = http.POST(http_request_data);

    if (http_response_code > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", http_response_code);

        // file found at server
        if (http_response_code == HTTP_CODE_OK) {
            const String& payload = http.getString();
            Serial.println("received payload:\n<<");
            Serial.println(payload);
            Serial.println(">>");
        }
    }
    else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(http_response_code).c_str());
    }

    http.end();
}

void ThingooConnector::connect()
{
    return;
}
