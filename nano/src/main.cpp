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

void setup(){
	authenticator = new Authenticator(lock, speaker);
	speaker = new Speaker(SPEAKER_PIN);
	rfidHandler = new RFIDHandler(MFRC522_SS_PIN, MFRC522_RST_PIN, authenticator, speaker);
	keypadHandler = new KeypadHandler(KEYPAD_ROW_PINS, KEYPAD_COL_PINS, authenticator, speaker);
	lock = new Lock(MOTOR_PIN_0, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3);

	//Boot sound.
	speaker->playBootSound();

	//Start serial, for debugging.
	Serial.begin(9600);
}

void loop(){
	rfidHandler->loop();
	keypadHandler->loop();
	lock->loop();
}
