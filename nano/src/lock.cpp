#include "lock.h"

void Lock::open(){
	if(_state){
		return;
	}
	this->rotate(true, 1000);
	_state = true;

#ifdef ENABLE_SERIAL_LOCK
	Serial.println("[LOCK] Lock open.");
#endif
}

void Lock::close(){
	if(!_state){
		return;
	}
	this->rotate(false, 1000);
	_state = false;

#ifdef ENABLE_SERIAL_LOCK
	Serial.println("[LOCK] Lock closed.");
#endif
}

bool Lock::getState(){
	return _state;
}
