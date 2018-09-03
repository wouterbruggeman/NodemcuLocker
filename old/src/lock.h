#ifndef LOCK_H
#define LOCK_H

#include "timedio.h"

class Lock : public TimedIO{
	public:
		Lock(int pin) : TimedIO(pin){};
		void open() : TimedIO::on();
		void close() : TimedIO::off();
};

#endif
