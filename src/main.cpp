#include "main.h"

#include <ESP8266WebServer.h>
#include "webserver/webserver.h"
#include "thread/thread.h"
#include "memory/memory.h"
#include "rfid/rfid.h"

const char *AP_SSID = "Locker_";
const char *AP_PASSWORD = "pass";

//Global variables
Thread closeLockThread(closeLock);
Thread soundThread(speakerDisable);
Thread disableWifiThread(disableWifi);

void speakerDisable(){
	noTone(SPEAKER_PIN);
	soundThread.disable();
}

void noAccessAlert(){
	tone(SPEAKER_PIN, SOUND_NO_ACCESS_FREQUENCY);

	//Disable the sound after some time
	soundThread.setDelay(SOUND_NO_ACCESS_DURATION);
}

void closeLock(){
	digitalWrite(LOCK_PIN, LOW);
	closeLockThread.disable();
	#ifdef DEBUG_MODE
		Serial.println("Lock closed");
	#endif
}

void openLock(){
	digitalWrite(LOCK_PIN, HIGH);
	tone(SPEAKER_PIN, SOUND_OPEN_FREQUENCY);

	//Start a few threads.
	soundThread.setDelay(SOUND_OPEN_DURATION);
	closeLockThread.setDelay(LOCK_CLOSE_DURATION);

	#ifdef DEBUG_MODE
		Serial.println("Lock open");
	#endif
}

void beepFeedback(){
	tone(SPEAKER_PIN, SOUND_BEEP_FREQUENCY);
	soundThread.setDelay(SOUND_BEEP_DURATION);
}

void enableWifi(){
	WiFi.enableAP(true);
	disableWifiThread.setDelay(WIFI_DISABLE_DURATION);
	digitalWrite(LED_PIN, HIGH);
	#ifdef DEBUG_MODE
		Serial.println("Wifi enabled");
	#endif
}

void disableWifi(){
	WiFi.enableAP(false);
	disableWifiThread.disable();
	digitalWrite(LED_PIN, LOW);
	#ifdef DEBUG_MODE
		Serial.println("Wifi disabled");
	#endif
}

void setup(){
	//setup serial
	#ifdef DEBUG_MODE
		delay(1000);
		Serial.begin(115200);
		Serial.println("Serial enabled");
	#endif

	//setup IO
	pinMode(LOCK_PIN, OUTPUT);
	pinMode(SPEAKER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	digitalWrite(LOCK_PIN, LOW);
	digitalWrite(LED_PIN, HIGH);

	#ifdef DEBUG_MODE
		Serial.println("Digital pins enabled");
	#endif

	//setup WIFI
	WiFi.softAP(AP_SSID, AP_PASSWORD);
	enableWifi();
	IPAddress defaultGateway = WiFi.softAPIP();
	#ifdef DEBUG_MODE
		Serial.print("AP IP address: ");
		Serial.println(defaultGateway);
	#endif

	//setup other stuff
	setupMemory();
	setupRFID();
	setupWebserver();
}

void loop(){
	//Handle other services
	handleRFID();
	handleWebserver();

	//Check the threads
	soundThread.check();
	closeLockThread.check();
	disableWifiThread.check();
}
