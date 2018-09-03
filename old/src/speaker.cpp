#include "speaker.h"
#include "settings.h"
#include <Arduino.h>

Speaker::Speaker(int pin){
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

void Speaker::enable(unsigned long frequency, unsigned long duration){
	_timer = millis() + duration;
	digitalWrite(_pin, HIGH);
}

void Speaker::disable(){
	digitalWrite(_pin, LOW);

}

void Speaker::loop(){
	if(millis() >= _timer){
		this->disable();
	}
}
