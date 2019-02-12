#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <MFRC522.h>
#include "settings.h"

class RFIDHandler{
	public:
		RFIDHandler(int ss_pin, int rst_pin);
		void loop();
		void reset();

		void saveUid();
		bool cardIsShown();
		bool readerIsConnected();
		char getReaderVersion();

		unsigned char getIndex(int index);

	private:
		MFRC522 *_reader;
		//Authenticator *_authenticator;
		unsigned char _uid[UID_SIZE];
};

#endif
