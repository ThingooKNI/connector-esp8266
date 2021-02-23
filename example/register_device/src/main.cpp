#include <Arduino.h>


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 

#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "huawei";  //YOUR WIFI SETTINGS
const char *password = "12345678";

//Server address
const char *host = "dev.thingoo.xyz";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate
const char fingerprint[] PROGMEM = "95 E1 00 D0 43 BC CE 7E 24 67 71 BC 43 77 15 23 78 74 FF C5";
//=========================================================
//                    Setup                               =
//=========================================================

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



//==========================================================
//              Requesting http                            =
//==========================================================

  WiFiClientSecure httpsClient;    

  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  
  while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
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
  
  String getData, Link;
  
  //POST endpoint
  Link = "/auth/realms/Thingoo/protocol/openid-connect/token";

  Serial.print("requesting URL: ");
  Serial.println(host);
  /*

POST /auth/realms/Thingoo/protocol/openid-connect/token HTTP/1.1
Host: https://dev.thingoo.xyz
Content-Type: application/x-www-form-urlencoded
Content-Length: 105

grant_type=client_credentials&client_id=thingoo-device&client_secret=0bb4187d-56d5-4f2c-87e3-90d8807f2e85
```
    
   */

  httpsClient.print(String("POST ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +
               "Content-Length: 105" + "\r\n\r\n" +
               "grant_type=client_credentials&client_id=thingoo-device&client_secret=0bb4187d-56d5-4f2c-87e3-90d8807f2e85" + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");
    
  









}

//=======================================================================
//                    Main Loop
//=======================================================================
void loop() {
  
}
//=======================================================================