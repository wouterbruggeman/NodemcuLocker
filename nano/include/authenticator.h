#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <Arduino.h>
#include "lock.h"
#include "settings.h"

class Authenticator{
	public:
		Authenticator(Lock *lock);
		void authenticate();
		void authenticateMaster();
		void addUid(unsigned char uid[UID_SIZE]);
		void clearUid();
		void addKeyStroke(char key);
		void clearKeyStrokes();
		bool hasAccess();
		void logout();
		void loop();
	private:
		//Functions
		void setAccess(bool state);

		//Variables
		char _pressedKeys[PRESSED_KEYS_BUFFER_SIZE];
		int _pressedKeysCounter = 0;
		unsigned char _uid[UID_SIZE];
		bool _accessGranted = false;
		//unsigned long _timer = 0;

		Lock *_lock;
};

#endif
