#include "nano.h"

NANO::NANO(){

	//Start on the given baudrate
	Serial.begin(NANO_BAUDRATE);

	//Start the timer
	_KAPacketTimer = millis() + NANO_KEEP_ALIVE_INTERVAL;
}

void NANO::loop(){
	//Check if the Keep Alive packet has to be send.
	if(millis() >= _KAPacketTimer){
		this->sendKAPacket();
	}
}

void NANO::sendMotorPacket(int direction, int steps){

}

void NANO::sendSpeakerPacket(int frequency, int duration){

}

void NANO::checkSerial(){
	//Check for incoming packets
	if(!Serial.available()){
		return;
	}
	//First byte in packet contains type
	switch(Serial.read()){
		case 0:
			receiveKeystroke();
			break;
		case 1:
			receiveUid();
			break;
		default:
			break;
	}
}

void NANO::receiveKeystroke(){

}

void NANO::receiveUid(){

}

void NANO::sendKAPacket(){
	//Send only the packet type (in this case just '0')
	Serial.write(0);
}
