#ifndef LED_H
#define LED_H

#include "timedio.h"

class Led : public TimedIO{
	public:
		Led(int pin) : TimedIO(pin){};
};

#endif
