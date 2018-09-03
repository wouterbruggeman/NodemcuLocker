#include "esp.h"

ESP::ESP(Speaker *speaker){
	_speaker = speaker;
	Serial.begin(ESP_BAUDRATE);
}

void ESP::loop(){
	this->checkSerial();
}

void ESP::sendKeystroke(char key){
	Serial.print("KEY PRESSED: ");
	Serial.println(key);
}

void ESP::sendUid(uint8_t uid[UID_SIZE]){
	Serial.println("UID FOUND!");
}

bool ESP::isConnected(){
	if((millis() - _lastKAPacket) > (ESP_KEEP_ALIVE_INTERVAL + ESP_KEEP_ALIVE_THRESHOLD)){
		return false;
	}
	return true;
}

void ESP::checkSerial(){
	if(!Serial.available()){
		return;
	}

	//First byte contains type
	switch(Serial.read()){
		case 0:
			receiveKAPacket();
			break;
		case 1:
			receiveMotorPacket();
			break;
		case 2:
			receiveSpeakerPacket();
			break;
		case 3:
			receiveLedPacket();
			break;
		default:
			break;
	}
}

void ESP::receiveKAPacket(){
	_lastKAPacket = millis();
}

void ESP::receiveMotorPacket(){

}

void ESP::receiveSpeakerPacket(){

}

void ESP::receiveLedPacket(){

}
