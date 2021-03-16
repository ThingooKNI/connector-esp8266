#include <Arduino.h>


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 

#include <ESP8266HTTPClient.h>

#include "esp8266Thingoo.h"

#include <ArduinoJson.h>


/* Set these to your desired credentials. */
const char *ssid = "huawei";  //YOUR WIFI SETTINGS
const char *password = "12345678";

//Server address
const char *host = "dev.thingoo.xyz";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate
const char fingerprint[] PROGMEM = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";



StaticJsonDocument<2048> doc;


//const char SECRET_KEY = "101ed902-3a95-48b1-b8c6-9a4648151050";


//=========================================================
//                    Setup                               =
//=========================================================



esp8266Thingoo connector;


void setup() {
    Serial.begin(115200);

  
    WiFi.begin(ssid, password);     //Connect to your WiFi
    Serial.println("");

    Serial.print("Connecting");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    //If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
    
    connector.client_credentials("thingoo-device", "101ed902-3a95-48b1-b8c6-9a4648151050");
    connector.connect();

    connector._send_token_request();
    connector._get_token();

//==========================================================
//              Requesting http                            =
//==========================================================

}

  /*







POST /auth/realms/Thingoo/protocol/openid-connect/token HTTP/1.1
Host: https://dev.thingoo.xyz
Content-Type: application/x-www-form-urlencoded
Content-Length: 105

grant_type=client_credentials&client_id=thingoo-device&client_secret=0bb4187d-56d5-4f2c-87e3-90d8807f2e85
```
    
   */

  
  
//   httpsClient.print(String("POST ") + Link + " HTTP/1.1\r\n" +
//                "Host: " + host + "\r\n" +
//                "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +
//                "Content-Length: 105" + "\r\n\r\n" +
//                "grant_type=client_credentials&client_id=thingoo-device&client_secret=" + SECRET_KEY + "\r\n" +
//                "Connection: close\r\n\r\n");

//   Serial.println("request sent");

  
//   // Skip HTTP headers
//   // char endOfHeaders[] = "\r\n\r\n";
//   // if (!httpsClient.find(endOfHeaders)) {
//   //   Serial.println(F("Invalid response"));
//   //   httpsClient.stop();
//   //   return;
//   // }

//   // Allocate the JSON document
//   // Use arduinojson.org/v6/assistant to compute the capacity.
//   //StaticJsonDocument<1536> doc;
  

  

//   // Extract values
//   //Serial.println(F("Response:"));
//   //Serial.println(doc["access_token"].as<char*>());
//   // Serial.println(doc["expires_in"].as<int>());
//   // Serial.println(doc["refresh_expires_in"].as<int>());

 

  
//   String line;
//   while (httpsClient.connected()) {
//     line = httpsClient.readStringUntil('\n');
//     if (line == "\r") {
//       Serial.println("headers received");
//       break;
//     }
//   }

//   Serial.println("reply was:");
//   Serial.println("==========");
  
  
// //==========================================================
// //              FIX getting answer from server !!!   !!    =
// //==========================================================

//   for (int i = 0; i<2; i++){        
//     line = httpsClient.readStringUntil('\n'); //Read only line with JSON
//   }
  
  
  
  
//   DeserializationError error = deserializeJson(doc, line);
//   if (error) {
//     Serial.print(F("deserializeJson() failed: "));
//     Serial.println(error.f_str());
//     Serial.println("BLADDDDDD");
//     return;
//   }

//   const char* access_token = doc["access_token"];
//   int expires_in = doc["expires_in"]; // 300
//   int refresh_expires_in = doc["refresh_expires_in"]; // 0
//   // const char* token_type = doc["token_type"]; // "Bearer"
//   // int not_before_policy = doc["not-before-policy"]; // 0
//   // const char* scope = doc["scope"]; // "email profile"
  
//   Serial.println("ACCESS TOKEN:  ");
//   Serial.println(access_token);
  
  
//   Serial.println("==========");
//   Serial.println("closing connection");
    
//}









//=======================================================================
//                    Main Loop
//=======================================================================
void loop() {
  
}
//=======================================================================