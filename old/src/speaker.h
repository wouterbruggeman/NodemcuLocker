#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker{
	public:
		Speaker(int pin);
		void enable(unsigned long frequency, unsigned long duration);
		void disable();
		void loop();
	private:
		unsigned long _timer = 0;
		int _pin;
};

#endif
