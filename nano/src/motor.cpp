#include "motor.h"
#include <Arduino.h>

//Create a new motor on the 4 given pins.
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
}

void Motor::loop(){
	//If the motor has steps to do:
	if(_steps > 0){
		this->rotate();
		_steps--;
	}
}

void Motor::step(bool direction, unsigned int steps){
	//Set the direction and the amount of steps
	_direction = direction;
	_steps = steps;
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
