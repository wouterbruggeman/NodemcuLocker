#include "lock.h"

void Lock::open(){
	if(_state){
		return;
	}
	this->step(true, 1000);
	_state = true;
}

void Lock::close(){
	if(!_state){
		return;
	}
	this->step(false, 1000);
	_state = false;
}

bool Lock::getState(){
	return _state;
}
