#ifndef ESP_H
#define ESP_H

#include <Arduino.h>
#include "speaker.h"
#include "motor.h"

#define UID_SIZE 4
//#define ESP_BAUDRATE 115200
#define ESP_BAUDRATE 9600
#define ESP_KEEP_ALIVE_INTERVAL 1000
#define ESP_KEEP_ALIVE_THRESHOLD 500

/* Incoming packet data:
 *
 * 0 - Keep alive (send every second)
 * 1 - Rotate motor [0:motor] [1:direction] [2:duration]
 * 2 - Enable speaker [0:frequency] [1:duration]
 * 3 - Led state [0:state]
 *
 */

/* Outgoing packet data:
 *
 * 0 - KeyStroke
 * 1 - UID
 *
 */

class ESP{
	public:
		ESP(Speaker *speaker, Motor *motor);
		void loop();
		void sendKeystroke(char key);
		void sendUid(uint8_t uid[UID_SIZE]);
		bool isConnected();

	private:
		void checkSerial();
		void receiveKAPacket();
		void receiveMotorPacket();
		void receiveSpeakerPacket();
		void receiveLedPacket();

		//Variables
		unsigned long _lastKAPacket;
		Speaker *_speaker;
		Motor *_motor;


};

#endif
