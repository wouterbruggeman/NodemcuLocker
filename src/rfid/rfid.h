#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <MFRC522.h>
#include "../memory/memory.h"
#include "../thread/thread.h"
#include "../main.h"

//PIN DEFINES
#define MFRC522_SS_PIN 15
#define MFRC522_RST_PIN 5

#define RFID_MODE_NORMAL 0
#define RFID_MODE_TAG_ADD 1
#define RFID_MODE_TAG_REMOVE 2
#define RFID_MODE_TIMEOUT 15000

void checkForAccess();
bool readerIsConnected();
void addRFID();
void removeRFID();
void timeoutRFIDMode();
bool getLastTag(char *tag);
void setupRFID();
void handleRFID();

#endif
