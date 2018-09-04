#include "carddatabase.h"
#include "FS.h"

CardDatabase::CardDatabase(char *filename){
	_filename = filename;
}

void CardDatabase::add(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]){
	if(!SPIFFS.begin()){
		return;
	}
	File f = SPIFFS.open(_filename, "a");
	if(!f){
		//Create the file if it does not exist.
		f = SPIFFS.open(_filename, "w+");
	}
	f.write(card, UID_SIZE);
	f.write(code, PASSCODE_SIZE);
	f.close();

	SPIFFS.end();
}

void CardDatabase::remove(uint8_t card[UID_SIZE]){
	int index = find(card);
	if(index == -1){
		return;
	}
	remove(index);
}

void CardDatabase::remove(int index){
	if(!SPIFFS.begin()){
		return;
	}

	//Read the file
	File f = SPIFFS.open(_filename, "r+");

	//Create new buffer
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Loop through the content of the file
	for(int i = 0; i < f.size(); i++){
		//Put bytes into new buffer if index does not equal 'index'
		if((i - (i % UID_SIZE + PASSCODE_SIZE)) != index){
			f.write(buffer[i]);
		}
	}

	f.close();
	SPIFFS.end();
}

int CardDatabase::find(uint8_t card[UID_SIZE]){
	if(!SPIFFS.begin()){
		return -1;
	}

	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Walk through all blocks
	for(int i = 0; i < (f.size() / UID_SIZE + PASSCODE_SIZE); i++){
		int matchCounter = 0;
		for(int j = 0; j < UID_SIZE; j++){
			if(card[j] == buffer[i]){
				matchCounter++;
			}
		}
		if(matchCounter == UID_SIZE){
			f.close();
			SPIFFS.end();
			return i / UID_SIZE;
		}
	}
	f.close();
	SPIFFS.end();
	return -1;
}

bool CardDatabase::contains(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]){
	if(!SPIFFS.begin()){
		return false;
	}
	Serial.println("Filesystem init");

	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());
	Serial.println("File can be read");

	//Walk through all blocks
	for(int i = 0; i < (f.size() / UID_SIZE + PASSCODE_SIZE); i++){
		int matchCounter = 0;
		for(int j = 0; j < UID_SIZE + PASSCODE_SIZE; j++){
			if(card[j] == buffer[i]){
				matchCounter++;
			}
		}
		if(matchCounter == UID_SIZE + PASSCODE_SIZE){
			f.close();
			SPIFFS.end();
			return true;
		}
	}

	f.close();
	SPIFFS.end();
	return false;
}

void CardDatabase::clear(){
	if(!SPIFFS.begin()){
		return;
	}

	//Read the file
	File f = SPIFFS.open(_filename, "w");
	f.flush();
	f.close();
	SPIFFS.end();
}
