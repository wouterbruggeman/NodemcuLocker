#ifndef TIMEDIO_H
#define TIMEDIO_H

class TimedIO{
	public:
		TimedIO(int pin);
		void on(unsigned long duration);
		void off();
		void loop();
	protected:
		unsigned long _timer = 0;
		int _pin;
};

#endif
