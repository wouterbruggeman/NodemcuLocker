#ifndef SPEAKER_H
#define SPEAKER_H

#define BOOT_SOUND_DURATION 500
#define BOOT_SOUND_FREQUENCY 500

class Speaker{
	public:
		Speaker(int pin);
		void enable(unsigned long frequency, unsigned long duration);
	private:
		int _pin;
};

#endif
