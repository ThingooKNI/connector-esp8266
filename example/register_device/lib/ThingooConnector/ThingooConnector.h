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
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>


class ThingooConnector {


    

  public:
    
    ThingooConnector();

    
    void set_client_credentials(String client_id, String secret_key);
    void set_fingerprint(uint8_t fingerprint);
    void connect();
    
    DynamicJsonDocument doc();
    WiFiClientSecure httpsClient; 
    const char* fingerprint;
    const char* host;
    int https_port;  //HTTPS= 443 and HTTP = 80

    String token_endpoint;
    

    
   



  private:
    void _send_token_request();
    void _get_token();
    
    uint8_t _fingerprint;
    String _secret_key;
    String _client_id;
    String _access_token;
};





#endif


