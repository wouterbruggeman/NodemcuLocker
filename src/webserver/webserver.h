#ifndef WEBSERVER_H
#define WEBSERVER_H

#ifdef ESP8266
	extern "C" {
	#include "user_interface.h"
}
#endif

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "../rfid/rfid.h"
#include "../memory/memory.h"
#include "../main.h"

#define DATA_TYPE "text/html"
#define EEPROM_POSITIVE_PREFIX "<span class='g'>"
#define EEPROM_POSITIVE_SUFFIX "</span>"

#define HEX_UPPERCASE 65
#define HEX_LOWERCASE 97

//other usefull functions
String charToHex(char c);

//webpages
String showMainMenu();
void handleRootPage();
void handleEEPROMDumpPage();
void handleLastTagRequest();
void handleNotFoundPage();

//other functions
void setupWebserver();
void handleWebserver();

#endif
