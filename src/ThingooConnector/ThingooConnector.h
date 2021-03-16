/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#ifndef ThingooConnector_h
#define ThingooConnector_h

#include "Arduino.h"
#include "WiFiClientSecure.h"

#include <ArduinoJson.h>

class ThingooConnector {


    

  public:
    
    ThingooConnector();


    void set_client_credentials(String client_id, String secret_key);
    void connect();
    
    StaticJsonDocument<2048> doc;
    WiFiClientSecure httpsClient; 
    const char* fingerprint;
    const char* host;
    int https_port;  //HTTPS= 443 and HTTP = 80

    String token_endpoint;
    

    
   



  private:
    void _send_token_request();
    void _get_token();

    String _secret_key;
    String _client_id;
    String _access_token;
};





#endif


