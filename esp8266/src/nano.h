#ifndef NANO_H
#define NANO_H

#include <Arduino.h>
#include "carddatabase.h"

//#define Nano_BAUDRATE 115200
#define NANO_BAUDRATE 9600
#define NANO_KEEP_ALIVE_INTERVAL 1000

class Nano{
	public:
		Nano(CardDatabase *cardDatabase);
		void init();
		void openLock();
		void closeLock();
		void loop();
	private:
		void sendMotorPacket(bool direction, int steps);
		void sendSpeakerPacket(int frequency, int duration);
		void checkSerial();
		void receiveKeystroke();
		void receiveUid();
		void sendKAPacket();

		//Variables:
		unsigned long _KAPacketTimer;
		CardDatabase *_acceptedCards;

		uint8_t _receivedPasscode[PASSCODE_SIZE];
		int _passcodeIteration = 0;
		uint8_t _receivedUid[UID_SIZE];

};

#endif
