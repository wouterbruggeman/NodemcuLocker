#ifndef MOTOR_H
#define MOTOR_H

#include "shiftregister.h"

const unsigned char MOTOR_PHRASES[4] = {
	193,
	112,
	28,
	7
};

class Motor{
	public:
		Motor(ShiftRegister *shiftRegister, int byte, bool nibble);
		void loop();
		void start(bool direction, unsigned long duration);
	private:
		//Functions
		void rotate();

		//Variables:
		ShiftRegister *_shiftRegister;
		bool _direction;
		int _byte;
		bool _nibble;

		unsigned long _timer;
		unsigned char phrase = 0;

};

#endif
