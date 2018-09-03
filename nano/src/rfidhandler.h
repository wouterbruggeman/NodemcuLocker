#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <MFRC522.h>
#include "esp.h"

#define UID_SIZE 4

class RFIDHandler{
	public:
		RFIDHandler(int ss_pin, int rst_pin, ESP *esp);
		void loop();
		void readUid();
		bool cardIsShown();
		bool readerIsConnected();
		char getReaderVersion();
	private:
		MFRC522 *_reader;
		ESP *_esp;
		uint8_t _currentUid[UID_SIZE];

};

#endif
