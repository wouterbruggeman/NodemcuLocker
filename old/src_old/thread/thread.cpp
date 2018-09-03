#include "thread.h"

Thread::Thread(void (*functionPointer)())
{
	//store the functionpointer and the delay
	fcnPtr = functionPointer;
}

void Thread::check()
{
	if(!_enabled){
		return;
	}
	if(millis() >= _triggerOnMillis)
	{
		//Execute given function:
		fcnPtr();

		//Update the timer
		_triggerOnMillis = _delay + millis();
	}
}
void Thread::setDelay(unsigned long delayMillis){
	//set the delay
	_delay = delayMillis;
	_triggerOnMillis = _delay + millis();
	_enabled = true;

	//Set the counter to 0
	_counter = 0;
}
void Thread::disable(){
	_enabled = false;

	//Set the counter to 0
	_counter = 0;
}
int Thread::getCounter(){
	return _counter;
}
