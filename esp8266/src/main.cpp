#include <Arduino.h>
#include "FS.h"
#include "settings.h"
#include "filenames.h"
#include "nano.h"
#include "httpserver.h"
#include "carddatabase.h"

HTTPServer *server;
CardDatabase *acceptedCards;
Nano *nano;

void setup(){
	//Mount the filesystem
	SPIFFS.begin();

	//Create the objects
	server = new HTTPServer(AP_SSID, AP_PASSWORD, acceptedCards, nano);
	acceptedCards = new CardDatabase(FILE_ACCEPTED_CARDS);
	nano = new Nano(acceptedCards);

	//Initialize the objects
	nano->init();
	//Start the webserver after the serial communication has been started
	server->init();
}

void loop(){
	//Execute the serial communication stuff first
	nano->loop();
	server->loop();
}

