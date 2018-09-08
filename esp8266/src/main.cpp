#include <Arduino.h>
#include "settings.h"
#include "filenames.h"
#include "nano.h"
//#include "httpserver.h"
#include "carddatabase.h"

CardDatabase *acceptedCards;
Nano *nano;

void setup(){
	acceptedCards = new CardDatabase(FILE_ACCEPTED_CARDS);
	nano = new Nano(acceptedCards);
}

void loop(){
	nano->loop();
}
