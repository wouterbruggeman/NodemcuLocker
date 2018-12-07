#include "keypadhandler.h"

KeypadHandler::KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS],
				Authenticator *authenticator,
				Lock *lock
		){
	_keypad = new Keypad(makeKeymap(KEYS), row_pins, col_pins, KEYPAD_ROWS, KEYPAD_COLS);
	_authenticator = authenticator;
	_lock = lock;
}

void KeypadHandler::loop(){
	//Read the key if possible
	char key = _keypad->getKey();
	if(key == NO_KEY){
		return;
	}


#ifdef ENABLE_SERIAL
	Serial.print("[KEYPAD] Key: ");
	Serial.print(key);
	Serial.println("");
#endif
	//Determine what to to on keypress
	switch(key){
		case 'A':
			//Change input mode
			_inputMode = INPUT_NORMAL;
#ifdef ENABLE_SERIAL
	Serial.print("[KEYPAD] Input mode: ");
	Serial.println(_inputMode, DEC);
#endif
			break;
		case 'B':
			//Change input mode
			_inputMode = INPUT_MASTER;
#ifdef ENABLE_SERIAL
	Serial.print("[KEYPAD] Input mode: ");
	Serial.println(_inputMode, DEC);
#endif
			break;
		case 'C':
			//Move the lock
			if(_authenticator->hasAccess()){
#ifdef ENABLE_SERIAL
	Serial.println("[KEYPAD] Moving lock right.");
#endif
				_lock->rotate(true, 10);
			}
			break;
		case 'D':
			//Move the lock
			if(_authenticator->hasAccess()){
#ifdef ENABLE_SERIAL
	Serial.println("[KEYPAD] Moving lock left.");
#endif
				_lock->rotate(false, 10);
			}
			break;
		case '#':
			//Log in or out, depending on the access state
			if(_authenticator->hasAccess()){
				//Logout.
				_authenticator->logout();
			}else{
				//Check for access and login if possible
				this->submit();
			}
			break;
		case '*':
			//Reset the input method and clear all keystrokes
			_inputMode = INPUT_NORMAL;
			_authenticator->clearKeyStrokes();
			break;
		default:
			//Just add the keystroke.
			_authenticator->addKeyStroke(key);
			break;
	}
}

void KeypadHandler::submit(){
	//Check input mode
	if(_inputMode == INPUT_NORMAL){
		//Authenticate as usual
		_authenticator->authenticate();
		return;
	}

	//Authenticate as master
	_authenticator->authenticateMaster();
	//Reset the input mode
	_inputMode = INPUT_NORMAL;
}
