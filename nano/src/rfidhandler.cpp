#include "rfidhandler.h"
#include <Arduino.h>
#include "settings.h"

RFIDHandler::RFIDHandler(int ss_pin, int rst_pin, Authenticator *authenticator){
	SPI.begin();
	_reader = new MFRC522(ss_pin, rst_pin);
	_reader->PCD_Init();
	_authenticator = authenticator;
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

void RFIDHandler::saveUid(){
#ifdef ENABLE_SERIAL_RFID
	Serial.print("[RFID] UID: ");
#endif

	unsigned char currentUid[UID_SIZE];
	for(int i = 0; i < UID_SIZE; i++){
		currentUid[i] = (unsigned char)_reader->uid.uidByte[i];
#ifdef ENABLE_SERIAL_RFID
		Serial.print(currentUid[i], DEC);
		Serial.print(" ");
#endif
	}
#ifdef ENABLE_SERIAL_RFID
	Serial.println("");
#endif

	//Send the uid
	_authenticator->addUid(currentUid);

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
