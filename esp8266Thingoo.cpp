/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#include "esp8266Thingoo.h"



//OUTSIDE LIBRARIES:
#include <Arduino.h>

#include <WiFiClientSecure.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>



esp8266Thingoo::esp8266Thingoo() 
  {
    
    fingerprint = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";  
    HOST = "dev.thingoo.xyz";
    httpsPort = 443;//HTTPS= 443 and HTTP = 80
    END_POINT = "/auth/realms/Thingoo/protocol/openid-connect/token";

  }

void esp8266Thingoo::connect() {
   


  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000);
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  
  while((!httpsClient.connect(HOST, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  

  Serial.print("Requesting URL: ");
  Serial.println(HOST);

}


void esp8266Thingoo::client_credentials(String client_id, String secret_key)
{
  _SECRET_KEY = secret_key;
  _CLIENT_ID = client_id;

}




void esp8266Thingoo::_send_token_request() {
  
  httpsClient.print(String("POST ") + END_POINT + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +
               "Content-Length: 105" + "\r\n\r\n" +
               "grant_type=client_credentials&client_id=" + _CLIENT_ID + "&client_secret=" + _SECRET_KEY + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");


}



void esp8266Thingoo::_get_token() {
  String line;
  while (httpsClient.connected()) {
    line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("reply was:");
  Serial.println("==========");
  
  
//==========================================================
//              FIX getting answer from server !!!   !!    =
//==========================================================

  for (int i = 0; i<2; i++){        
    line = httpsClient.readStringUntil('\n'); //Read only line with JSON
  }
  
  
  
  
  DeserializationError error = deserializeJson(doc, line);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    Serial.println("BLADDDDDD");
    return;
  }

  const char* access_token = doc["access_token"];
  int expires_in = doc["expires_in"]; // 300
  int refresh_expires_in = doc["refresh_expires_in"]; // 0
  // const char* token_type = doc["token_type"]; // "Bearer"
  // int not_before_policy = doc["not-before-policy"]; // 0
  // const char* scope = doc["scope"]; // "email profile"
  
  Serial.println("ACCESS TOKEN:  ");
  Serial.println(access_token);
  
  _ACCESS_TOKEN = access_token;
  
  Serial.println("==========");
  Serial.println("closing connection");


}