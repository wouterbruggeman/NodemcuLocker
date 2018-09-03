#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <MFRC522.h>
#include "carddatabase.h"
#include "hardware.h"

class RFIDHandler{
	public:
		RFIDHandler(
				int ss_pin,
				int rst_pin,
				CardDatabase *acceptedCards,
				CardDatabase *cardLog,
				Hardware *hardware);
		void loop();
		void readUid();
		void logCurrentCard();
		bool cardIsShown();
		bool readerIsConnected();
		char getReaderVersion();
	private:
		MFRC522 *_reader;
		CardDatabase *_acceptedCards;
		CardDatabase *_cardLog;
		Hardware *_hardware;

		uint8_t _currentUid[UID_SIZE];

};

#endif
