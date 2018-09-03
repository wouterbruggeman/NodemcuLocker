#ifndef NANO_H
#define NANO_H

#include <Arduino.h>

#define UID_SIZE 4
//#define NANO_BAUDRATE 115200
#define NANO_BAUDRATE 9600
#define NANO_KEEP_ALIVE_INTERVAL 1000

class NANO{
	public:
		NANO();

		void loop();
		void sendMotorPacket(bool direction, int steps);
		void sendSpeakerPacket(int frequency, int duration);

	private:
		void checkSerial();
		void receiveKeystroke();
		void receiveUid();

		void sendKAPacket();

		//Variables:
		unsigned long _KAPacketTimer;
}


#endif
