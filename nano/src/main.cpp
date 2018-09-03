#include <Arduino.h>
#include "pins.h"
#include "esp.h"
#include "speaker.h"
#include "motor.h"
#include "rfidhandler.h"
#include "keypadhandler.h"
#include "shiftregister.h"

/*ESP *esp;
Speaker *speaker;
RFIDHandler *rfidHandler;
KeypadHandler *keypadHandler;*/
Motor *motors[2];
ShiftRegister *shiftRegister;

void setup(){
	/*esp = new ESP(speaker);
	speaker = new Speaker(SPEAKER_PIN);
	rfidHandler = new RFIDHandler(MFRC522_SS_PIN, MFRC522_RST_PIN, esp);
	keypadHandler = new KeypadHandler(KEYPAD_ROW_PINS, KEYPAD_COL_PINS, esp, speaker);*/
 	shiftRegister = new ShiftRegister(SHIFTREG_DATA_DIRECTION_REGISTER,
			SHIFTREG_DATA_REGISTER, SHIFTREG_DS_OFFSET, SHIFTREG_SHCP_OFFSET, SHIFTREG_STCP_OFFSET, 1);

	motors[0] = new Motor(shiftRegister, 0, 1);
	//motors[1] = new Motor(shiftRegister, 0, 1);

	//Play a boot tone
	//speaker->enable(BOOT_SOUND_FREQUENCY, BOOT_SOUND_DURATION);

	motors[0]->start(true, 5000);
}

void loop(){
	//Check for updates within these objects.
	/*rfidHandler->loop();
	keypadHandler->loop();*/

	motors[0]->loop();

	//esp->loop();
}
