#ifndef SPEAKER_H
#define SPEAKER_H

#define BOOT_SOUND_DURATION 500
#define BOOT_SOUND_FREQUENCY 500

class Speaker{
	public:
		Speaker(unsigned char pin);

		//Warning: blocking function!!
		void playBootSound();

		//Some sounds
		void beepPositive();
		void beepNegative();
		void shortBeep();
		void longBeep();
		void buttonBeep();
	private:
		void enable(unsigned int frequency, unsigned long duration);
		void disable();
		unsigned char _pin;
};

#endif
