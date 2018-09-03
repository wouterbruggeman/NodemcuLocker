#ifndef HARDWARE_H
#define HARDWARE_H

#include "lock.h"
#include "led.h"
#include "speaker.h"

struct Hardware{
	Lock *lock;
	Led *led;
	Speaker *speaker;
};

#endif
