#ifndef SETTINGS_H
#define SETTINGS_H

//Authenticator settings
#define UID_SIZE 4
#define AUTH_CODE_SIZE 4
#define PRESSED_KEYS_BUFFER_SIZE 20
#define LOGOUT_TIME (1000 * 60 * 5)

//Login settings
#define AUTH_CODE "1234"
const unsigned char AUTH_UID[UID_SIZE] = {(unsigned char)12,(unsigned char)34,(unsigned char)56,(unsigned char)78};
#define AUTH_MASTER_CODE "12345678901234567890"

//Speaker Settings
#define SPEAKER_BTNBEEP_DURATION 250
#define SPEAKER_BTNBEEP_FREQUENCY 1000

#define SPEAKER_SHORTBEEP_DURATION 250
#define SPEAKER_SHORTBEEP_FREQUENCY 800

#define SPEAKER_LONGBEEP_DURATION 750
#define SPEAKER_LONGBEEP_FREQUENCY 800

//Other settings
#define ENABLE_SERIAL true

#endif
