#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define MICROSECOND_DELAY 300

#define PHRASE_COUNT 8
const unsigned char MOTOR_PHRASES[PHRASE_COUNT] = {
	1,
	3,
	2,
	6,
	4,
	12,
	8,
	9
};

class Motor{
	public:
		Motor(int pin_0, int pin_1, int pin_2, int pin_3);
		void loop();
		void rotate(bool direction, unsigned int steps);
		bool isRotating();
	private:
		//Functions
		void step(int phrase);
		void turnOff();

		//Variables:
		bool _direction;
		unsigned int _steps = 0;

		int _pins[4];

};

#endif
