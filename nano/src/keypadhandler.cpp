#include "keypadhandler.h"

KeypadHandler::KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS]
		){
	_keypad = new Keypad(makeKeymap(KEYS), row_pins, col_pins, KEYPAD_ROWS, KEYPAD_COLS);
	reset();
}

void KeypadHandler::loop(){
	//Read the key if possible
	char key = _keypad->getKey();
	if(key == NO_KEY){
		return;
	}


#ifdef ENABLE_SERIAL_KEYPAD
	Serial.print("[KEYPAD] Key: ");
	Serial.print(key);
	Serial.println("");
#endif
	//Determine what to to on keypress
	switch(key){
		case 'A':
			//Change input mode
			_inputMode = INPUT_NORMAL;
#ifdef ENABLE_SERIAL_KEYPAD
	Serial.print("[KEYPAD] Input mode: ");
	Serial.println(_inputMode, DEC);
#endif
			break;
		case 'B':
			//Change input mode
			_inputMode = INPUT_MASTER;
#ifdef ENABLE_SERIAL_KEYPAD
	Serial.print("[KEYPAD] Input mode: ");
	Serial.println(_inputMode, DEC);
#endif
			break;
		case 'C':
		case 'D':
			_command = KeypadHandler::AUTH_LOGOUT;
			break;
		case '#':
			this->submit();
			break;
		case '*':
			reset();
			break;
		default:
			//Just add the keystroke.
			addKeyStroke(key);
			break;
	}
}

void KeypadHandler::reset(){
	//Reset keys
	for(int i = 0; i < PRESSED_KEYS_BUFFER_SIZE; i++){
		_pressedKeys[i] = 0;
	}
	_pressedKeysCounter = 0;

	//Reset command
	_command = KeypadHandler::WAIT;

	//Reset the input method
	_inputMode = INPUT_NORMAL;


#ifdef ENABLE_SERIAL_KEYPAD
	Serial.println("[KEYPAD] Input mode and keystrokes reset.");
#endif
}

int KeypadHandler::getCommand(){
	return _command;
}

unsigned char KeypadHandler::getIndex(int index){
	return _pressedKeys[index];
}

void KeypadHandler::addKeyStroke(char key){
	if(_pressedKeysCounter < PRESSED_KEYS_BUFFER_SIZE){
		_pressedKeys[_pressedKeysCounter] = key;
		_pressedKeysCounter++;
	}
}

void KeypadHandler::submit(){
	if(_inputMode == INPUT_NORMAL){
		_command = KeypadHandler::AUTH_NORMAL;
	}else if(_inputMode == INPUT_MASTER){
		_command = KeypadHandler::AUTH_MASTER;
	}
#ifdef ENABLE_SERIAL_KEYPAD
	Serial.print("[KEYPAD] Command: ");
	Serial.println(_command);
#endif
}
