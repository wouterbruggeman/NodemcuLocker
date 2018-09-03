#include "speaker.h"
#include <Arduino.h>
#include "pins.h"

Speaker::Speaker(unsigned char pin){
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

void Speaker::enable(unsigned int frequency, unsigned long duration){
	tone(_pin, frequency, duration);
}

void Speaker::disable(){
	noTone(_pin);
}

void Speaker::playBootSound(){
	for(int i = 0; i < 250; i++){
		tone(_pin, i + 500);
		delay(5);
	}
	noTone(_pin);
}
