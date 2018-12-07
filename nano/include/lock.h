#ifndef LOCK_H
#define LOCK_H

#include "motor.h"
#include "settings.h"

class Lock: public Motor{
	public:
		Lock(int pin_0, int pin_1, int pin_2, int pin_3)
			: Motor(pin_0, pin_1, pin_2, pin_3){};
		void open();
		void close();
		bool getState();
	private:
		bool _state = false;
};

#endif
