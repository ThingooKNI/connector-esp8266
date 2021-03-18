/***************************************************************
   esp8266Thingoo is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#include "ThingooConnector.h"



//OUTSIDE LIBRARIES:
#include <Arduino.h>

#include <WiFiClientSecure.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <WiFiManager.h>

#include <WiFiClientSecureBearSSL.h>


ThingooConnector::ThingooConnector() 
  {
    
    fingerprint = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";  
    host = "dev.thingoo.xyz";
    https_port = 443;//HTTPS= 443 and HTTP = 80
    token_endpoint = "/auth/realms/Thingoo/protocol/openid-connect/token";

  }

void ThingooConnector::connect() {
   


  httpsClient.setFingerprint(fingerprint);
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int retry_counter=0;
  
  while((!httpsClient.connect(host, https_port)) && (retry_counter < 30)){
      delay(100);
      Serial.print(".");
      retry_counter++;
  }
  if(retry_counter==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  

  Serial.print("Requesting URL: ");
  Serial.println(host);

}


void ThingooConnector::set_client_credentials(String client_id, String secret_key)
{
  _secret_key = secret_key;
  _client_id = client_id;

}




void ThingooConnector::_send_token_request() {
  
  httpsClient.print(String("POST ") + token_endpoint + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +
               "Content-Length: 105" + "\r\n\r\n" +
               "grant_type=client_credentials&client_id=" + _client_id + "&client_secret=" + _secret_key + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");


}



void ThingooConnector::_get_token() {
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
  
  _access_token = access_token;
  
  Serial.println("==========");
  Serial.println("closing connection");


}