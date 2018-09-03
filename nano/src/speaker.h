#ifndef SPEAKER_H
#define SPEAKER_H

#define BOOT_SOUND_DURATION 500
#define BOOT_SOUND_FREQUENCY 500

class Speaker{
	public:
		Speaker(unsigned char pin);
		void enable(unsigned int frequency, unsigned long duration);
		void disable();

		//Warning: blocking function!!
		void playBootSound();
	private:
		unsigned char _pin;
};

#endif
