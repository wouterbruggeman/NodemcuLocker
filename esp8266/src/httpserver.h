#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifdef ESP8266
	extern "C"{
		#include "user_interface.h"
	}
#endif

class HTTPServer{
	public:
		HTTPServer();
		void wifiInit(char *ssid, char *password);
		void enableWifi();
		void disableWifi();
		void loop();
	private:
		void initPages();
		void showWebpage(int page);
		void handlePageRequest();
		void handlePageNotFound();

		//Variables
		ESP8266WebServer *_webserver;

};

#endif
