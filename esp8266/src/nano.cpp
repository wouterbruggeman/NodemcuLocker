#include "nano.h"

Nano::Nano(CardDatabase *acceptedCards){
	//Init variables
	_acceptedCards = acceptedCards;
}

void Nano::init(){
	//Start on the given baudrate
	Serial.begin(NANO_BAUDRATE);

	//Start the timer
	_KAPacketTimer = millis() + NANO_KEEP_ALIVE_INTERVAL;


	//DEBUG STUFF
	delay(2500);
	Serial.println("Hello world!");
	this->receiveUid();
}

void Nano::sendMotorPacket(bool direction, int steps){
	Serial.println("Motor test");
}

void Nano::sendSpeakerPacket(int frequency, int duration){
	Serial.println("Speaker test");
}

void Nano::loop(){
	//Check if the Keep Alive packet has to be send.
	if(millis() >= _KAPacketTimer){
		this->sendKAPacket();
		_KAPacketTimer = millis() + NANO_KEEP_ALIVE_INTERVAL;
	}

	//Check serial
	this->checkSerial();
}

void Nano::checkSerial(){
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

void Nano::receiveKeystroke(){

}

void Nano::receiveUid(){
	uint8_t uid[UID_SIZE];
	uint8_t code[PASSCODE_SIZE];

	for(int i = 0; i < UID_SIZE; i++){
		uid[i] = 1 + i;
	}
	for(int i = 0; i < PASSCODE_SIZE; i++){
		code[i] = 5 + i;
	}
	_acceptedCards->mountFs(true);
	_acceptedCards->add(uid, code);
	_acceptedCards->mountFs(false);

}

void Nano::sendKAPacket(){
	//Send only the packet type (in this case just '0')
	//Serial.write(0);
	//Serial.println("KA PACKET!");
}

