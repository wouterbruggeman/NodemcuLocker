#include "timedio.h"
#include <Arduino.h>

TimedIO::TimedIO(int pin){
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

void TimedIO::on(unsigned long duration){
	_timer = millis() + duration;
	digitalWrite(_pin, HIGH);
}

void TimedIO::off(){
	digitalWrite(_pin, LOW);

}

void TimedIO::loop(){
	if(millis() >= _timer){
		this->off();
	}
}
