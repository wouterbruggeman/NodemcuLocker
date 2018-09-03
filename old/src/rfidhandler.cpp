#include "rfidhandler.h"
#include <Arduino.h>

RFIDHandler::RFIDHandler(int ss_pin, int rst_pin){
	_reader = new MFRC522(ss_pin, rst_pin);
	_reader->PCD_Init();

}

void RFIDHandler::loop(){
	if(!this->readerIsConnected()){
		return;
	}
	if(this->cardIsShown()){
		readUid();
	}
}

void RFIDHandler::readUid(){
	for(int i = 0; i < UID_SIZE; i++){
		_currentUid[i] = _reader->uid.uidByte[i];
	}
	_reader->PICC_HaltA();
}

void RFIDHandler::logCurrentCard(){
	_cardLog->add(_currentUid);
}

bool RFIDHandler::cardIsShown(){
	if(!_reader->PICC_IsNewCardPresent()){
		return false;
	}
	if(!_reader->PICC_ReadCardSerial()){
		return false;
	}
	return true;
}

bool RFIDHandler::readerIsConnected(){
	char v = getReaderVersion();
	if((v == 0x00) || (v == 0xFF)){
		return false;
	}
	return true;
}

char RFIDHandler::getReaderVersion(){
	return _reader->PCD_ReadRegister(_reader->VersionReg);
}
