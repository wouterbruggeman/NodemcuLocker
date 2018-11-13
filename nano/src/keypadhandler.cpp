#include "keypadhandler.h"

KeypadHandler::KeypadHandler(
				const char row_pins[KEYPAD_ROWS],
				const char col_pins[KEYPAD_COLS],
				Authenticator *authenticator,
				Speaker *speaker
		){
	_keypad = new Keypad(makeKeymap(KEYS), row_pins, col_pins, KEYPAD_ROWS, KEYPAD_COLS);
	_speaker = speaker;
	_authenticator = authenticator;
}

void KeypadHandler::loop(){
	//Read the key
	char key = _keypad->getKey();
	if(key == NO_KEY){
		return;
	}
#ifdef ENABLE_SERIAL
	Serial.print("Key: ");
	Serial.println(key);
#endif
	_speaker->buttonBeep();
	switch(key){
		case 'A':
			//Switch input mode
			if(_inputMode == INPUT_MASTER){
				_inputMode = INPUT_NORMAL;
			}else{
				_inputMode = INPUT_MASTER;
			}
		case 'B':
			if(_authenticator->hasAccess()){
				//Do something that requires access
			}
			break;
		case 'C':
			if(_authenticator->hasAccess()){
				//Do something that requires access
			}
			break;
		case 'D':
			//Do nothing.
			break;
		case '#':
			//Log in or out, depending on the access state
			if(_authenticator->hasAccess()){
				_authenticator->logout();
			}else{
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
#ifdef ENABLE_SERIAL
	Serial.print("Input mode: ");
	Serial.println(_inputMode);
#endif
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
	_inputMode = INPUT_NORMAL;
	return;
}
