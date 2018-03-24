#ifndef RFID_H
#define RFID_H

//PIN DEFINES
#define MFRC522_SS_PIN D8
#define MFRC522_RST_PIN D4

#define RFID_MODE_NORMAL 0
#define RFID_MODE_TAG_ADD 1
#define RFID_MODE_TAG_REMOVE 2
#define RFID_MODE_TIMEOUT 15000

#define DEBUG_MODE

void checkForAccess();
bool readerIsConnected();
void addRFID();
void removeRFID();
void timeoutRFIDMode();
bool getLastTag(char *tag);
void setupRFID();
void handleRFID();

#endif
