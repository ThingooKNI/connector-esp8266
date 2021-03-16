/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#ifndef esp8266Thingoo_h
#define esp8266Thingoo_h

#include "Arduino.h"
#include "WiFiClientSecure.h"

#include <ArduinoJson.h>

class esp8266Thingoo {


    

  public:
    
    esp8266Thingoo();
    void _send_token_request();


    void client_credentials(String client_id, String secret_key);
    void connect();
    void _get_token();
    
    StaticJsonDocument<2048> doc;
    WiFiClientSecure httpsClient; 
    const char* fingerprint;
    const char* HOST;
    int httpsPort;  //HTTPS= 443 and HTTP = 80

    String END_POINT;
    

    
   



  private:
    String _SECRET_KEY;
    String _CLIENT_ID;
    String _ACCESS_TOKEN;
};





#endif


