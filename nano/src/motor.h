#ifndef MOTOR_H
#define MOTOR_H

#define MICROSECOND_DELAY 500

const unsigned char MOTOR_PHRASES[4] = {
	193,
	112,
	28,
	7
};

class Motor{
	public:
		Motor(int pin_0, int pin_1, int pin_2, int pin_3);
		void loop();
		void start(bool direction, unsigned long duration);
	private:
		//Functions
		void rotate();

		//Variables:
		bool _direction;
		unsigned long _timer;
		unsigned char _phrase = 0;

		int _pins[0];

};

#endif
