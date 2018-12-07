#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <MFRC522.h>
#include "authenticator.h"

class RFIDHandler{
	public:
		RFIDHandler(int ss_pin, int rst_pin, Authenticator *authenticator);
		void loop();
		void saveUid();
		bool cardIsShown();
		bool readerIsConnected();
		char getReaderVersion();
	private:
		MFRC522 *_reader;
		Authenticator *_authenticator;

};

#endif
