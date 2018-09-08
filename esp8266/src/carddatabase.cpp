#include "carddatabase.h"
#include "FS.h"

CardDatabase::CardDatabase(char *filename){
	_filename = filename;

}

void CardDatabase::add(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]){
	if(!SPIFFS.begin()){
		return;
	}

	if(SPIFFS.exists(_filename)){
		Serial.println("File exists");
	}else{
		Serial.println("File doesn't exists");
		File f = SPIFFS.open(_filename, "a+");
		f.write(1);
		f.close();

		f = SPIFFS.open(_filename, "r");
		bool test = SPIFFS.exists(_filename);
		Serial.println(test, DEC);

	}

	/*if(this->contains(card, code)){
		return;
	}

	File f = SPIFFS.open(_filename, "a");
	if(!f){
		//Create the file if it does not exist.
		f = SPIFFS.open(_filename, "w+");
		Serial.println("Created new file");
	}

	f.write(card, UID_SIZE);
	f.write(code, PASSCODE_SIZE);
	Serial.println("Card added.");

	f.close();

	this->debugPrintFile();*/
}

void CardDatabase::remove(uint8_t card[UID_SIZE]){
	int index = find(card);
	if(index == -1){
		return;
	}
	remove(index);
}

void CardDatabase::remove(int index){
	//Read the file
	File f = SPIFFS.open(_filename, "r+");

	//Create new buffer
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Loop through the content of the file
	for(int i = 0; i < f.size(); i++){
		//Put bytes into new buffer if index does not equal 'index'
		if((i - (i % BLOCK_SIZE)) != index){
			f.write(buffer[i]);
		}
	}

	f.close();
}

int CardDatabase::find(uint8_t card[UID_SIZE]){
	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Walk through all blocks
	for(int i = 0; i < (f.size() / BLOCK_SIZE); i++){
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
	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Create block to search for
	uint8_t block[BLOCK_SIZE];
	for(int i = 0; i < UID_SIZE; i++){
		block[i] = card[i];
	}
	for(int i = UID_SIZE; i < PASSCODE_SIZE; i++){
		block[i] = code[i];
	}

	//Walk through all blocks
	for(int i = 0; i < (f.size() / BLOCK_SIZE); i++){
		int matchCounter = 0;
		for(int j = 0; j < BLOCK_SIZE; j++){
			if(buffer[j + (i * BLOCK_SIZE)] == block[j]){
				matchCounter++;
			}
		}
		if(matchCounter == BLOCK_SIZE){
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

void CardDatabase::debugPrintFile(){
	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	Serial.println("FILE:");
	for(int i = 0; i < (f.size() / (UID_SIZE + PASSCODE_SIZE)); i++){
		for(int j = 0; j < UID_SIZE + PASSCODE_SIZE; j++){
			Serial.print(buffer[j + (i * (UID_SIZE + PASSCODE_SIZE))], DEC);
		}
		Serial.println("");
	}

	Serial.println("==============");

	FSInfo fs_info;
	SPIFFS.info(fs_info);
	Serial.print("totalBytes: ");
	Serial.println(fs_info.totalBytes);
	Serial.print("usedBytes: ");
	Serial.println(fs_info.usedBytes);

	Serial.println("==============");

	f.close();
}
