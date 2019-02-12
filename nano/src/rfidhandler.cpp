#include "rfidhandler.h"
#include <Arduino.h>
#include "settings.h"

RFIDHandler::RFIDHandler(int ss_pin, int rst_pin){
	SPI.begin();
	_reader = new MFRC522(ss_pin, rst_pin);
	_reader->PCD_Init();

	reset();
}

void RFIDHandler::loop(){
	if(!this->readerIsConnected()){
		return;
	}

	if(!this->cardIsShown()){
		return;
	}

	//Card is found
	this->saveUid();
}

void RFIDHandler::reset(){
	//Reset the uid
	for(int i = 0; i < UID_SIZE; i++){
		_uid[i] = 0;
	}
#ifdef ENABLE_SERIAL_RFID
	Serial.println("[RFID] Reset.");
#endif
}

void RFIDHandler::saveUid(){
#ifdef ENABLE_SERIAL_RFID
	Serial.print("[RFID] UID: ");
#endif

	for(int i = 0; i < UID_SIZE; i++){
		_uid[i] = (unsigned char)_reader->uid.uidByte[i];
#ifdef ENABLE_SERIAL_RFID
		Serial.print(_uid[i], DEC);
		Serial.print(" ");
#endif
	}
#ifdef ENABLE_SERIAL_RFID
	Serial.println("");
#endif

	_reader->PICC_HaltA();
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

unsigned char RFIDHandler::getIndex(int index){
	return _uid[index];
}
