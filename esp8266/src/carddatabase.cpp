#include "carddatabase.h"
#include "FS.h"

CardDatabase::CardDatabase(char *filename){
	_filename = filename;

}

bool CardDatabase::mountFs(bool state){
	if(state){
		return SPIFFS.begin();
	}else{
		SPIFFS.end();
		return true;
	}
}

void CardDatabase::add(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]){
	if(this->contains(card, code)){
		return;
	}

	File f = SPIFFS.open(_filename, "a+");
	f.write(card, UID_SIZE);
	f.write(code, PASSCODE_SIZE);
	Serial.println("Card added.");

	f.close();

	this->debugPrintFile();
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
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Loop through all blocks in the file
	for(int i = 0; i < (f.size() / BLOCK_SIZE); i++){
		//Check for the index
		if(i != index){
			//Place item back in file.
			for(int j = 0; j < BLOCK_SIZE; j++){
				f.write(buffer[j + (i * BLOCK_SIZE)]);
			}
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
			if(card[j] == buffer[i + j]){
				matchCounter++;
			}
		}
		if(matchCounter == UID_SIZE){
			f.close();
			SPIFFS.end();
			return i;
		}
	}
	f.close();
	return -1;
}

bool CardDatabase::contains(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]){
	//Read the file
	File f = SPIFFS.open(_filename, "r");
	if(!f){
		Serial.println("File not open..");
	}
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	//Create block to search for
	uint8_t block[BLOCK_SIZE];
	for(int i = 0; i < UID_SIZE; i++){
		block[i] = card[i];
	}
	for(int i = UID_SIZE; i < BLOCK_SIZE; i++){
		block[i] = code[i - UID_SIZE];
	}
	Serial.println("Block created");
	for(int i = 0; i < BLOCK_SIZE; i++){
		Serial.print(block[i]);
	}
	Serial.println("");
	Serial.println("");

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
			return true;
		}
	}

	f.close();
	return false;
}

void CardDatabase::clear(){
	//Read the file
	File f = SPIFFS.open(_filename, "w");
	f.flush();
	f.close();
}

void CardDatabase::debugPrintFile(){
	if(!SPIFFS.begin()){
		return;
	}
	//Read the file
	File f = SPIFFS.open(_filename, "r");
	char buffer[f.size()];
	f.readBytes(buffer, f.size());

	Serial.println("FILE:");
	for(int i = 0; i < (f.size() / BLOCK_SIZE); i++){
		for(int j = 0; j < BLOCK_SIZE; j++){
			Serial.print(buffer[j + (i * BLOCK_SIZE)], DEC);
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
