#include "nano.h"

Nano::Nano(CardDatabase *acceptedCards){

	//Start on the given baudrate
	Serial.begin(NANO_BAUDRATE);

	//Start the timer
	_KAPacketTimer = millis() + NANO_KEEP_ALIVE_INTERVAL;

	//Init variables
	_acceptedCards = acceptedCards;


	//DEBUG STUFF
	delay(1000);
	Serial.println("Hello world!");
	this->receiveUid();
}

void Nano::loop(){
	//Check if the Keep Alive packet has to be send.
	if(millis() >= _KAPacketTimer){
		this->sendKAPacket();
	}

	//Check serial
	this->checkSerial();
}

void Nano::sendMotorPacket(bool direction, int steps){
	Serial.println("Motor test");
}

void Nano::sendSpeakerPacket(int frequency, int duration){
	Serial.println("Speaker test");
}

void Nano::checkSerial(){
	//Check for incoming packets
	if(!Serial.available()){
		return;
	}
	//TODO: remove the line below to stop debugging.
	return;
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
		code[i] = 5 + i;
	}

	Serial.println("Checking DB");
	if(_acceptedCards->contains(uid, code)){
		Serial.println("DB contains UID");
	}else{
		Serial.println("DB doesn't contain UID");
		_acceptedCards->add(uid, code);
		Serial.println("Added uid.");
	}
}

void Nano::sendKAPacket(){
	//Send only the packet type (in this case just '0')
	//Serial.write(0);
	Serial.println("KA PACKET!");
}
