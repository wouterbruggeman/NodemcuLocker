#include "rfid.h"

MFRC522 reader(MFRC522_SS_PIN, MFRC522_RST_PIN);
Thread rfidModeTimeout(timeoutRFIDMode);

char rfidMode = RFID_MODE_NORMAL;
char lastTag[4];
bool lastTagIsKnown = false;

void checkForAccess(){
	if(!reader.PICC_IsNewCardPresent()){
		return;
	}
	if(!reader.PICC_ReadCardSerial()){
		return;
	}

	lastTagIsKnown = false;
	
	#ifdef DEBUG_MODE
		Serial.print("RFID tag found: ");
	#endif
	char data[5];
	data[0] = MEM_UID;
	for(int i = 0; i < 4; i++){
		data[i + 1] = reader.uid.uidByte[i];

		//save the last tag
		lastTag[i] = data[i + 1];

		#ifdef DEBUG_MODE
			Serial.print(data[i + 1], HEX);
			Serial.print(" ");
		#endif
	}
	#ifdef DEBUG_MODE
		Serial.println();
	#endif
	reader.PICC_HaltA();

	if(rfidMode == RFID_MODE_NORMAL){
		//search for data in memory
		int block = searchForBlock(data);
		if(block == -1){
			noAccessAlert();
			return;
		}

		//user is allowed. Open lock.
		lastTagIsKnown = true;
		openLock();
	}else if(rfidMode == RFID_MODE_TAG_ADD){
		//Insert into EEPROM
		insertBlock(data);
		
		//make sound
		beepFeedback();
		rfidModeTimeout.disable();
	}else if(rfidMode == RFID_MODE_TAG_REMOVE){
		//Remove from EEPROM
		removeBlock(data);

		//make sound
		beepFeedback();
		rfidModeTimeout.disable();
	}

	rfidMode = RFID_MODE_NORMAL;
}

bool readerIsConnected(){
	char v = reader.PCD_ReadRegister(reader.VersionReg);
	Serial.print(v, DEC);
	Serial.print(" ");
	if((v == 0x00) || (v == 0xFF)){
		#ifdef DEBUG_MODE
			Serial.print("Reader version code: ");
			Serial.println(v, DEC);
		#endif
		return false;
	}
	return true;
}

void addRFID(){
	rfidModeTimeout.setDelay(RFID_MODE_TIMEOUT);
	rfidMode = RFID_MODE_TAG_ADD;
	#ifdef DEBUG_MODE
		Serial.println("RFID mode ADD enabled");
	#endif
}

void removeRFID(){
	rfidModeTimeout.setDelay(RFID_MODE_TIMEOUT);
	rfidMode = RFID_MODE_TAG_REMOVE;
	#ifdef DEBUG_MODE
		Serial.println("RFID mode REMOVE enabled");
	#endif
}

void timeoutRFIDMode(){
	rfidMode = RFID_MODE_NORMAL;
	rfidModeTimeout.disable();
	#ifdef DEBUG_MODE
		Serial.println("RFID mode timeout");
	#endif
}

bool getLastTag(char *tag){
	memcpy(tag, lastTag, 4);
	return lastTagIsKnown;
}

void setupRFID(){
	SPI.begin();
	reader.PCD_Init();
	memset(lastTag, 0, 4);

	#ifdef DEBUG_MODE
		Serial.println("RFID reader enabled");
	#endif
}

void handleRFID(){
	/*if(!readerIsConnected()){
		closeLock();
	}else{*/
		checkForAccess();
	//}
	rfidModeTimeout.check();
}
