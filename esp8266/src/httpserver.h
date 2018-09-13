#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "carddatabase.h"
#include "nano.h"

#ifdef ESP8266
	extern "C"{
		#include "user_interface.h"
	}
#endif

class HTTPServer{
	public:
		HTTPServer(const char *ssid, const char *password,
				CardDatabase *acceptedCards, Nano *nano);
		void init();
		void enableWifi();
		void disableWifi();
		void loop();

		//Page handling functions
		void handlePageRequest();
	private:
		void initPages();

		//Variables
		ESP8266WebServer *_webserver;
		CardDatabase *_acceptedCards;
		//CardDatabase *_cardLog;
		Nano *_nano;
		const char *_ssid;
		const char *_password;

	protected:
		static void pageRequest(HTTPServer *server);

};

#endif
