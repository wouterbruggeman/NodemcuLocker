#include "motor.h"

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

	this->turnOff();
}

void Motor::loop(){
	//If the motor has steps to do:
	if(_steps > 0){
		if(_direction){
			for(int i = 0; i < PHRASE_COUNT; i++){
				this->step(i);
			}
		}else{
			for(int i = PHRASE_COUNT; i > 0; i--){
				this->step(i);
			}
		}


		_steps--;
	}else{
		this->turnOff();
	}
}

bool Motor::isRotating(){
	return (_steps > 0);
}

void Motor::rotate(bool direction, unsigned int steps){
	//Set the direction and the amount of steps
	_direction = direction;
	_steps = steps;
}

void Motor::step(int phrase){
	//Loop the 4 pins
	for(int i = 0; i < 4; i++){
		//For every bit, check if the bit has to be true
		unsigned char bitmask = (1 << i);

		//Calculate the value for the current pin
		bool bit = !!(bitmask & MOTOR_PHRASES[phrase]);

		//Write the bit to the pin
		digitalWrite(_pins[i], bit);

		//Delay for some time
		delayMicroseconds(MICROSECOND_DELAY);
		//delay(MICROSECOND_DELAY);
	}
}

void Motor::turnOff(){
	for(int i = 0; i < 4; i++){
		digitalWrite(_pins[i], 0);
	}
}
