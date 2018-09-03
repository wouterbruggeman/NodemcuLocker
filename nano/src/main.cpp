#include <Arduino.h>
#include "pins.h"
#include "esp.h"
#include "rfidhandler.h"
#include "keypadhandler.h"
#include "motor.h"

ESP *esp;
Speaker *speaker;
RFIDHandler *rfidHandler;
KeypadHandler *keypadHandler;
Motor *motors;

void setup(){
	esp = new ESP(speaker);
	speaker = new Speaker(SPEAKER_PIN);
	rfidHandler = new RFIDHandler(MFRC522_SS_PIN, MFRC522_RST_PIN, esp, speaker);
	keypadHandler = new KeypadHandler(KEYPAD_ROW_PINS, KEYPAD_COL_PINS, esp, speaker);

	motors = new Motor(MOTOR_PIN_0, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3);

	//Boot sound.
	speaker->playBootSound();
	speaker->disable();

	motors->start(true, 2000);
}

void loop(){
	rfidHandler->loop();
	keypadHandler->loop();
	motors->loop();
}
