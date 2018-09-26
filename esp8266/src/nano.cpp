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
}

void Nano::openLock(){

}

void Nano::closeLock(){

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
	uint8_t keyStroke = (uint8_t)Serial.read();

	switch(keyStroke){
		case 'A':
			break;
		case 'B':
			break;
		case 'C':
			break;
		case 'D':
			break;
		case '#':
			if(_acceptedCards->contains(_receivedUid, _receivedPasscode)){
				//Open the lock
				this->openLock();
			}
			break;
		case '*':
			//Clear the buffer
			for(int i = 0; i < PASSCODE_SIZE; i++){
				_receivedPasscode[i] = 0;
			}
			_passcodeIteration = 0;
			break;
		default:
			//Add to buffer
			_receivedPasscode[_passcodeIteration] = keyStroke;
			if(_passcodeIteration < PASSCODE_SIZE){
				_passcodeIteration++;
			}else{
				_passcodeIteration = 0;
			}
			break;
	}
}

void Nano::receiveUid(){
	for(int i = 0; i < UID_SIZE; i++){
		_receivedUid[i] = Serial.read();
	}
}

void Nano::sendKAPacket(){
	//Send only the packet type (in this case just '0')
	Serial.write(0);
}
