#include "motor.h"
#include <Arduino.h>

//Create a motor. Byte is the allowed byte to write to on the shift register.
//Nibble is the allowed byte to write to on the byte.
Motor::Motor(ShiftRegister *shiftRegister, int byte, bool nibble){
	_shiftRegister = shiftRegister;
	_byte = byte;
	_nibble = nibble;
}

void Motor::loop(){
	//Return if the motor should not be running.
	if(millis() >= _timer){
		//return;
	}

	this->rotate();
}

void Motor::start(bool direction, unsigned long duration){
	_direction = direction;
	_timer = millis() + duration;
}

void Motor::rotate(){
	unsigned char bitmask = (128 >> phrase);
	unsigned char data = 0;

	//Loop through all bits
	for(int i = 0; i < 4; i++){
		//For every bit, check if the bit has to be true
		bool bit = !!(bitmask & MOTOR_PHRASES[i]);
		data |= (bit << i);
	}
	/*
	Serial.print("Phrase: ");
	Serial.print(phrase);
	Serial.print(" | ");
	Serial.println(data, BIN);
	*/

	//Update the data in the shift register
	_shiftRegister->setNibble(_byte, _nibble, data);
	_shiftRegister->updateRegister();

	//Go to the next phrase
	phrase++;
	if(phrase > 7){
		phrase = 0;
	}
}
