#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>

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
