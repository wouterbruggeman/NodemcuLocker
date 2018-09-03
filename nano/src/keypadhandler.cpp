#include "keypadhandler.h"

KeypadHandler::KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS],
				ESP *esp,
				Speaker *speaker
		){
	_keypad = new Keypad(makeKeymap(KEYS), row_pins, col_pins, KEYPAD_ROWS, KEYPAD_COLS);
	_esp = esp;
	_speaker = speaker;
}

void KeypadHandler::loop(){
	//Read the key
	char key = _keypad->getKey();
	if(key == NO_KEY){
		return;
	}


	if(!_esp->isConnected()){
		//use master code to unlock.
	}
	//Esp is connected. Proceed as usual.
	_esp->sendKeystroke(key);
	_speaker->enable(KEYPAD_SOUND_FREQUENCY, KEYPAD_SOUND_DURATION);
}
