#ifndef KEYPADHANDLER_H
#define KEYPADHANDLER_H

#include <Keypad.h>
#include "esp.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define KEYPAD_SOUND_DURATION 500
#define KEYPAD_SOUND_FREQUENCY 800

const char KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

//static const char *MASTER_CODE = "612381";

class KeypadHandler{
	public:
		KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS],
				ESP *esp,
				Speaker *speaker
			     );
		void loop();
	private:
		Keypad *_keypad;
		ESP *_esp;
		Speaker *_speaker;

};

#endif
