#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <Arduino.h>
#include "settings.h"
#include "lock.h"
#include "rfidhandler.h"
#include "keypadhandler.h"

class Authenticator{
	public:
		Authenticator(RFIDHandler *rfidHandler, KeypadHandler *keypadHandler, Lock *lock);
		void loop();

		void authenticate();
		void authenticateMaster();

		bool hasAccess();
	private:
		//Functions
		void setAccess(bool state);

		//Variables
		bool _accessGranted;
		unsigned long _timer;


		RFIDHandler *_rfidHandler;
		KeypadHandler *_keypadHandler;
		Lock *_lock;
};

#endif
