#ifndef SETTINGS_H
#define SETTINGS_H

//Authenticator settings
#define UID_SIZE 4
#define AUTH_CODE_SIZE 4
#define PRESSED_KEYS_BUFFER_SIZE 20
#define LOGOUT_TIME (1000 * 60 * 5)

//Login settings
#define AUTH_NORMAL_CODE "1234"
const unsigned char AUTH_UID[UID_SIZE] = {(unsigned char)1, (unsigned char)2, (unsigned char)3,(unsigned char)4};
#define AUTH_MASTER_CODE "68190625669456325174"

//Other settings
#define ENABLE_SERIAL
#define ENABLE_SERIAL_AUTHENTICATOR
#define ENABLE_SERIAL_RFID
#define ENABLE_SERIAL_LOCK
#define ENABLE_SERIAL_KEYPAD

#endif
