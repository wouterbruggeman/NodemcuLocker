#include "authenticator.h"

Authenticator::Authenticator(RFIDHandler *rfidHandler, KeypadHandler *keypadHandler, Lock *lock){
	_rfidHandler = rfidHandler;
	_keypadHandler = keypadHandler;
	_lock = lock;

	_accessGranted = false;
	_timer = 0;

}

void Authenticator::loop(){
	if(millis() > _timer && _timer != 0){
		this->setAccess(false);
	}

	//Check if the keypadhandler is ready
	if(_keypadHandler->getCommand() == KeypadHandler::AUTH_NORMAL){
		this->authenticate();
	}else if(_keypadHandler->getCommand() == KeypadHandler::AUTH_MASTER){
		this->authenticateMaster();
	}else if(_keypadHandler->getCommand() == KeypadHandler::AUTH_LOGOUT){
		this->setAccess(false);
	}
}

void Authenticator::authenticate(){
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] Authenticating...");
#endif
	for(int i = 0; i < UID_SIZE; i++){
		if(_rfidHandler->getIndex(i) != AUTH_UID[i]){
			Serial.print(_rfidHandler->getIndex(i), DEC);
			Serial.print(" != ");
			Serial.println(AUTH_UID[i], DEC);

			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] UID accepted.");
#endif

	for(int i = 0; i < AUTH_CODE_SIZE; i++){
		if(_keypadHandler->getIndex(i) != AUTH_NORMAL_CODE[i]){
			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] Code accepted.");
#endif
	//Open the lock
	this->setAccess(true);
}

void Authenticator::authenticateMaster(){
/*#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] Authenticating master...");
#endif
	for(int i = 0; i < PRESSED_KEYS_BUFFER_SIZE; i++){
		if(_pressedKeys[i] != AUTH_MASTER_CODE[i]){
			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] Master code accepted.");
#endif

	//Open the lock
	this->setAccess(true);*/
}

void Authenticator::setAccess(bool access){
	//Reset the devices
	_rfidHandler->reset();
	_keypadHandler->reset();

	//Check if the previous state was the same
	if(access == _accessGranted){
		return;
	}

	//Update the state
	_accessGranted = access;

	//If access was granted
	if(_accessGranted){
		//Open the lock for some time
		_timer = millis() + LOGOUT_TIME;
		_lock->open();
	}else{
		//Close the lock
		_timer = 0;
		_lock->close();
	}




#ifdef ENABLE_SERIAL_AUTHENTICATOR
	if(_accessGranted){
		Serial.println("[AUTH] Access set to granted.");
	}else{
		Serial.println("[AUTH] Access set to denied.");
	}
#endif
}

bool Authenticator::hasAccess(){
	return _accessGranted;
}
