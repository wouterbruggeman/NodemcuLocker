#include <Arduino.h>
#include "pins.h"
#include "rfidhandler.h"
#include "keypadhandler.h"
#include "lock.h"

//Speaker *speaker;
RFIDHandler *rfidHandler;
Authenticator *authenticator;
KeypadHandler *keypadHandler;
Lock *lock;
Speaker *speaker;

bool t = false;

void setup(){
	//Create the handlers
	rfidHandler = new RFIDHandler(MFRC522_SS_PIN, MFRC522_RST_PIN, authenticator, speaker);
	keypadHandler = new KeypadHandler(KEYPAD_ROW_PINS, KEYPAD_COL_PINS, authenticator, speaker, lock);
	authenticator = new Authenticator(lock, speaker);

	//Create other objects
	lock = new Lock(MOTOR_PIN_0, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3);
	speaker = new Speaker(SPEAKER_PIN);

	//Boot sound.
	//speaker->playBootSound();

#ifdef ENABLE_SERIAL
	//Start serial on 9600 baud, if serial is enabled in the config
	Serial.begin(9600);
#endif

}

void loop(){
	if(!lock->isRotating()){
		//Loop the handlers, if the lock is not rotating.
		rfidHandler->loop();
		keypadHandler->loop();
		authenticator->loop();
		lock->rotate(t, 1000);
		t = !t;
	}
	lock->loop();
}
