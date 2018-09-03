#include "motor.h"
#include <Arduino.h>

//Create a motor. Byte is the allowed byte to write to on the shift register.
//Nibble is the allowed byte to write to on the byte.
Motor::Motor(int pin_0, int pin_1, int pin_2, int pin_3){
	_pins[0] = pin_0;
	_pins[1] = pin_1;
	_pins[2] = pin_2;
	_pins[3] = pin_3;

	pinMode(pin_0, OUTPUT);
	pinMode(pin_1, OUTPUT);
	pinMode(pin_2, OUTPUT);
	pinMode(pin_3, OUTPUT);

	_steps = 0;
	_timer = 0;
}

void Motor::loop(){

	//If the motor has steps to do:
	if(_steps > 0){
		this->rotate();
		_steps--;
	}

	//If the motor has some rotation time todo:
	if(millis() >= _timer){
		//Return if the motor shouldn't be running
		return;
	}

	//Rotate the motor
	this->rotate();
}


void Motor::start(bool direction, unsigned long duration){
	//Set the direction and the timer
	_direction = direction;
	_timer = millis() + duration;
}

void Motor::startStep(bool direction, unsigned int steps){
	//Set the direction and the amount of steps
	_direction = direction;
	_steps = steps;

	//Set the timer to 0, to avoid unnecessary rotations
	_timer = 0;
}

void Motor::rotate(){
	//Create a bitmask for the current motor phrase
	//DEC == BIN
	//128 == 10000000
	unsigned char bitmask = (128 >> _phrase);

	//Loop through all bits
	for(int i = 0; i < 4; i++){
		//For every bit, check if the bit has to be true
		bool bit = !!(bitmask & MOTOR_PHRASES[i]);

		//Write the bit to the pin
		digitalWrite(_pins[i], bit);
		delayMicroseconds(MICROSECOND_DELAY);
	}

	//Go to the next phrase
	_phrase++;
	if(_phrase > 7){
		_phrase = 0;
	}
}
