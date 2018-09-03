#ifndef PINS_H
#define PINS_H

#include "keypadhandler.h"

/* RFID Device */
#define MFRC522_SS_PIN 10
#define MFRC522_RST_PIN A0

/* Keypad */
const char KEYPAD_COL_PINS[KEYPAD_COLS] = {5,4,3,2};
const char KEYPAD_ROW_PINS[KEYPAD_ROWS] = {9,8,7,6};

/* Shift register(s) */
#define SHIFTREG_DATA_DIRECTION_REGISTER DDRC
#define SHIFTREG_DATA_REGISTER PORTC
#define SHIFTREG_DS_OFFSET 1
#define SHIFTREG_SHCP_OFFSET 2
#define SHIFTREG_STCP_OFFSET 3

/* Other hardware */
#define SPEAKER_PIN A5
#define LED_PIN A6

#endif
