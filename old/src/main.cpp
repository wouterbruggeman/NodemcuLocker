#include "Arduino.h"
#include "rfidhandler.h"
#include "carddatabase.h"
#include "pins.h"
#include "filenames.h"
#include "hardware.h"

CardDatabase *acceptedCards = new CardDatabase(ACCEPTED_CARD_STR);
CardDatabase *cardLog = new CardDatabase(CARD_LOG_STR);
Hardware *hardware;
RFIDHandler *rfidHandler = new RFIDHandler(
		MFRC522_SS_PIN,
		MFRC522_RST_PIN,
		acceptedCards,
		cardLog,
		hardware);

void setup(){
	hardware->lock = new Lock(LOCK_PIN);
	hardware->led = new Led(LOCK_PIN);
	hardware->speaker = new Speaker(SPEAKER_PIN);
}

void loop(){
	rfidHandler->loop();
	//webServer->loop();
	hardware->lock->loop();
	hardware->led->loop();
	hardware->speaker->loop();
}
