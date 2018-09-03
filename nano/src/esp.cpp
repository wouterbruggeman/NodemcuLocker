#include "esp.h"

ESP::ESP(Speaker *speaker, Motor *motor){
	//Initialize the ESP object.
	_speaker = speaker;
	_motor = motor;
	Serial.begin(ESP_BAUDRATE);
}

void ESP::loop(){
	//Check for serial packets every loop
	this->checkSerial();
}

void ESP::sendKeystroke(char key){
	//Send the data
	Serial.write(0);
	Serial.write(key);

	/*Serial.print("Keystroke: ");
	Serial.println(key);*/
}

void ESP::sendUid(uint8_t uid[UID_SIZE]){
	Serial.write(1);
	for(int i = 0; i < UID_SIZE; i++){
		Serial.write(uid[i]);
	}

	/*Serial.print("UID: ");
	for(int i = 0; i < UID_SIZE; i++){
		Serial.print(uid[i], DEC);
	}
	Serial.println();*/
}

bool ESP::isConnected(){
	//Check if the last received keep alive packet has been send less than the given threshold.
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
	bool direction = Serial.read();
	int steps = 0;
	for(int i = 0; i < 4; i++){
		steps = steps << (8*i);
		steps |= Serial.read();
	}
	_motor->startStep(direction, steps);
}

void ESP::receiveSpeakerPacket(){

	//Read the frequency
	int freq = 0;
	for(int i = 0; i < 4; i++){
		freq = freq << (8*i);
		freq |= Serial.read();
	}

	//Read the duration
	int duration = 0;
	for(int i = 0; i < 4; i++){
		duration = duration << (8*i);
		duration |= Serial.read();
	}
}

void ESP::receiveLedPacket(){
	bool state = Serial.read();
}
