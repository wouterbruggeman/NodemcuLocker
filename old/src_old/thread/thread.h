#include <Arduino.h>

#ifndef THREAD_H
#define THREAD_H

class Thread
{
	unsigned long _triggerOnMillis;
	unsigned long _delay;
	bool _enabled;
	void (*fcnPtr)();
	public:
		Thread(void (*functionPointer)());
		void check();
		void setDelay(unsigned long delayMillis);
		void disable();
		int getCounter();
};
#endif
