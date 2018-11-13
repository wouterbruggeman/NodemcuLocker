#ifndef KEYPADHANDLER_H
#define KEYPADHANDLER_H

#include <Keypad.h>
#include "authenticator.h"
#include "settings.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

const char KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

#define INPUT_NORMAL 0
#define INPUT_MASTER 1

class KeypadHandler{
	public:
		KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS],
				Authenticator *authenticator,
				Speaker *speaker
			     );
		void loop();
	private:
		void submit();

		//Variables:
		Keypad *_keypad;
		Speaker *_speaker;
		Authenticator *_authenticator;
		char _inputMode = INPUT_NORMAL;

};

#endif
