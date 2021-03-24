/***************************************************************
   ThingooConnector is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/

#ifndef ThingooConnector_h
#define ThingooConnector_h

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>

class ThingooConnector 
{
        const char* host;
    public:
        ThingooConnector(const char* host);
        void set_client_credentials(String client_id, String secret_key);
        void set_ssl_certificate_fingerprint(const char* fingerprint);
        void connect();

        HTTPClient http;
        StaticJsonDocument<2048> doc;

        String register_endpoint = "/auth/realms/Thingoo/protocol/openid-connect/token";
        String readings = "/readings";
        String devices = "/devices";

    private:
        String _clean_end_point(String endpoint);
        String _get_token();
        
        String _host;
        const char* _fingerprint;
        String _secret_key;
        String _client_id;
        String _access_token;
};

class AccessTokenRetrievalException : public std::exception
{
	public:
		AccessTokenRetrievalException() : std::exception()
        {
        }
};


#endif
