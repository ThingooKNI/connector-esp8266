/***************************************************************
   ThingooConnector is a library for the ESP8266/Arduino platform
   to communicate with Thingoo API
   Built for KNI Project "Thingoo" https://github.com/ThingooKNI/
 **************************************************************/
#include "ThingooConnector.h"

ThingooConnector::ThingooConnector(const char *host)
{
	_host = _clean_end_point(String(host));
}

void ThingooConnector::set_client_credentials(String client_id, String secret_key)
{
	_client_id = client_id;
	_secret_key = secret_key;
}

void ThingooConnector::set_ssl_certificate_fingerprint(const char* fingerprint)
{
	_fingerprint = fingerprint;
}

struct AccessTokenRetrievalException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Some Exception";
    }
};

String ThingooConnector::connect()
{
	try
	{
		String token = _get_token();
	}
	catch (AccessTokenRetrievalException e)
	{
		Serial.println("Exception was caught");
		Serial.println(e.what());
	}	
}

String ThingooConnector::_get_token()
{
	std::unique_ptr<BearSSL::WiFiClientSecure > client(new BearSSL::WiFiClientSecure);
	client->setFingerprint(_fingerprint);
	String token_endpoint = "https://" + (String) _host + register_endpoint;
	http.begin(*client, token_endpoint);
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	String http_request_data = "grant_type=client_credentials&client_id=" + _client_id + "&client_secret=" + _secret_key;

	int http_response_code = http.POST(http_request_data);	//Send HTTP POST request

	if (http_response_code == 200)
	{
		String payload = http.getString();
		DeserializationError error = deserializeJson(doc, payload);

		if (error)
		{
			Serial.print(F("deserializeJson() failed: "));
			Serial.println(error.f_str());
		}

		String access_token = doc["access_token"];
		return access_token;
	}
	else
	{
		//String error_message = "[HTTP] POST... failed, error: " + String(http_response_code);
		// return error_message;	
		throw AccessTokenRetrievalException();
	}
	http.end();
}

String ThingooConnector::_clean_end_point(String endpoint)
{
	endpoint.trim();
	endpoint.replace("https://", "");
	endpoint.replace("http://", "");
	
	if (endpoint.charAt(endpoint.length()-1) == '/')
	{
		endpoint.setCharAt(endpoint.length()-1, ' ');
		endpoint.trim();
	}
	
	return endpoint;
}


