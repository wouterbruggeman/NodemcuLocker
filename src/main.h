#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "webserver/webserver.h"
#include "thread/thread.h"
#include "memory/memory.h"
#include "rfid/rfid.h"

//PIN DEFINES
#define SPEAKER_PIN D2
#define LOCK_PIN D0
#define LED_PIN D1

//SOUND DEFINES
#define SOUND_OPEN_DURATION 250
#define SOUND_OPEN_FREQUENCY 1000
#define SOUND_NO_ACCESS_DURATION 1500
#define SOUND_NO_ACCESS_FREQUENCY 200
#define SOUND_BEEP_FREQUENCY 500
#define SOUND_BEEP_DURATION 250

//OTHER DEFINES
#define LOCK_CLOSE_DURATION 3000
//#define DEBUG_MODE

void speakerDisable();
void noAccessAlert();
void closeLock();
void openLock();
void beepFeedback();

void setup();
void loop();

#endif
