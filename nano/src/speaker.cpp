#include "speaker.h"
#include <Arduino.h>

Speaker::Speaker(int pin){
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

void Speaker::enable(unsigned long frequency, unsigned long duration){
	noTone(_pin);
	tone(_pin, frequency, duration);
}
