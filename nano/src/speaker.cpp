#include "speaker.h"
#include <Arduino.h>
#include "pins.h"

Speaker::Speaker(unsigned char pin){
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

void Speaker::enable(unsigned int frequency, unsigned long duration){
	//tone(_pin, frequency, duration);
}

void Speaker::disable(){
	//noTone(_pin);
}

void Speaker::playBootSound(){
	/*for(int i = 0; i < 250; i++){
		tone(_pin, i + 500);
		delay(5);
	}
	this->disable();*/
}

void Speaker::beepPositive(){
	this->shortBeep();
	this->disable();
}

void Speaker::beepNegative(){
	this->longBeep();
	this->disable();
}

void Speaker::shortBeep(){
	this->enable(SPEAKER_SHORTBEEP_FREQUENCY, SPEAKER_SHORTBEEP_DURATION);
	this->disable();
}

void Speaker::longBeep(){
	this->enable(SPEAKER_LONGBEEP_FREQUENCY, SPEAKER_LONGBEEP_DURATION);
	this->disable();
}

void Speaker::buttonBeep(){
	this->enable(SPEAKER_BTNBEEP_FREQUENCY, SPEAKER_BTNBEEP_DURATION);
	this->disable();
}
