#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "carddatabase.h"
#include "nano.h"

#define FILENAME_MAX_LENGTH 32
const String HTML_DATA_TYPE  = "text/html";
const String RESTRICTED_FILES[1] = {"/rfid_accepted"};

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
		void handlePageNotFound();
	private:
		void initPages();
	 	void showPage(String pagename, int statusCode);

		//Variables
		ESP8266WebServer *_webserver;
		CardDatabase *_acceptedCards;
		//CardDatabase *_cardLog;
		Nano *_nano;
		const char *_ssid;
		const char *_password;

	protected:
		static void pageRequest(HTTPServer *server);
		static void notFoundRequest(HTTPServer *server);

};

#endif
