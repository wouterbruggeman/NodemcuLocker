#include "main.h"

RFIDHandler *rfidHandler;
KeypadHandler *keypadHandler;
Lock *lock;
Authenticator *authenticator;

void setup(){
#ifdef ENABLE_SERIAL
	//Start serial on 9600 baud, if serial is enabled in the config
	Serial.begin(9600);
#endif
	//Create input handlers
	rfidHandler = new RFIDHandler(MFRC522_SS_PIN, MFRC522_RST_PIN);
	keypadHandler = new KeypadHandler(KEYPAD_ROW_PINS, KEYPAD_COL_PINS);

	//Create lock and authenticator
	lock = new Lock(MOTOR_PIN_0, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3);
	authenticator = new Authenticator(rfidHandler, keypadHandler, lock);
}

void loop(){
	if(!lock->isRotating()){
		//Loop the handlers, if the lock is not rotating.
		rfidHandler->loop();
		keypadHandler->loop();
		authenticator->loop();
	}
	lock->loop();

}
