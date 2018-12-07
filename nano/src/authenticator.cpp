#include "authenticator.h"

Authenticator::Authenticator(Lock *lock, Speaker *speaker){
	_speaker = speaker;
	_lock = lock;
}

void Authenticator::authenticate(){
#ifdef ENABLE_SERIAL
	Serial.println("[AUTH] Authenticating...");
#endif
	for(int i = 0; i < UID_SIZE; i++){
		if(_uid[i] != AUTH_UID[i]){
			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL
	Serial.println("[AUTH] UID accepted.");
#endif

	for(int i = 0; i < AUTH_CODE_SIZE; i++){
		if(_pressedKeys[i] != AUTH_CODE[i]){
			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL
	Serial.println("[AUTH] Code accepted.");
#endif
	//Open the lock
	this->setAccess(true);
	_lock->open();
}

void Authenticator::authenticateMaster(){
#ifdef ENABLE_SERIAL
	Serial.println("[AUTH] Authenticating master...");
#endif
	for(int i = 0; i < PRESSED_KEYS_BUFFER_SIZE; i++){
		if(_pressedKeys[i] != AUTH_MASTER_CODE[i]){
			//No access
			this->setAccess(false);
			return;
		}
	}
#ifdef ENABLE_SERIAL
	Serial.println("[AUTH] Master code accepted.");
#endif

	//Open the lock
	this->setAccess(true);
	_lock->open();
}

void Authenticator::addUid(uint8_t uid[UID_SIZE]){
	for(int i = 0; i < UID_SIZE; i++){
		_uid[i] = (unsigned char)uid[i];
	}
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
		_pressedKeys[i] = '0';
	}
	_pressedKeysCounter = 0;
}

void Authenticator::setAccess(bool access){
	if(access){
		_speaker->beepPositive();
		_timer = millis() + LOGOUT_TIME;
	}else{
		_speaker->beepNegative();
	}
	this->clearKeyStrokes();
	this->clearUid();
	_accessGranted = access;

#ifdef ENABLE_SERIAL
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
	if(millis() > _timer){
		this->logout();
	}
}
