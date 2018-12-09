#include "authenticator.h"

Authenticator::Authenticator(Lock *lock){
	_lock = lock;
	this->clearUid();
	this->clearKeyStrokes();
}

void Authenticator::authenticate(){
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] Authenticating...");
#endif
	for(int i = 0; i < UID_SIZE; i++){
		//if(_uid[i] != AUTH_UID[i]){

			Serial.print(this->_uid[i], DEC);
			Serial.print(" =?= ");
			Serial.println(AUTH_UID[i], DEC);
			//No access
			//this->setAccess(false);
			//return;
		//}
	}
#ifdef ENABLE_SERIAL_AUTHENTICATOR
	Serial.println("[AUTH] UID accepted.");
#endif

	for(int i = 0; i < AUTH_CODE_SIZE; i++){
		if(_pressedKeys[i] != AUTH_CODE[i]){
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
	_lock->open();
}

void Authenticator::authenticateMaster(){
#ifdef ENABLE_SERIAL_AUTHENTICATOR
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
	this->setAccess(true);
	_lock->open();
}

void Authenticator::addUid(unsigned char uid[UID_SIZE]){
	Serial.print("[AUTH] UID added: ");
	for(int i = 0; i < UID_SIZE; i++){
		_uid[i] = uid[i];
		Serial.print(_uid[i], DEC);
		Serial.print(" ");
	}
	Serial.println("EXTRA LOOP: ");
	this->loop();
	Serial.println("");
}

void Authenticator::clearUid(){
	for(int i = 0; i < UID_SIZE; i++){
		_uid[i] = 0;
	}
}

void Authenticator::addKeyStroke(char key){
	if(_pressedKeysCounter < PRESSED_KEYS_BUFFER_SIZE){
		_pressedKeys[_pressedKeysCounter] = key;
		_pressedKeysCounter++;
	}
}

void Authenticator::clearKeyStrokes(){
	for(int i = 0; i < PRESSED_KEYS_BUFFER_SIZE; i++){
		_pressedKeys[i] = 0;
	}
	_pressedKeysCounter = 0;
}

void Authenticator::setAccess(bool access){
	/*if(access){
		_timer = millis() + LOGOUT_TIME;
	}*/
	this->clearKeyStrokes();
	this->clearUid();
	_accessGranted = access;

	//BUG CAN BE FOUND HERE.....

#ifdef ENABLE_SERIAL_AUTHENTICATOR
	if(_accessGranted){
		Serial.println("[AUTH] Access set to granted.");
	}else{
		Serial.println("[AUTH] Access set to denied.");
	}
#endif
}

void Authenticator::logout(){
	_lock->close();
	_accessGranted = false;
}

bool Authenticator::hasAccess(){
	return _accessGranted;
}

void Authenticator::loop(){
	/*if(millis() > _timer && _timer != 0){
		this->logout();
	}
	Serial.print("[AUTH] Looped. UID: ");
	for(int i = 0; i < UID_SIZE; i++){
		Serial.print((unsigned char)_uid[i], DEC);
		Serial.print(" ");
	}
	Serial.println("");*/
}
