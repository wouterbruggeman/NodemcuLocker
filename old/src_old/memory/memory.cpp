#include "memory.h"

const int BLOCKS_AMOUNT = (EEPROM_SIZE - (EEPROM_SIZE % 5)) / 5;

void setupMemory(){
	EEPROM.begin(EEPROM_SIZE);
}

void memWrite(int block, char data[5]){
	for(int i = 0; i < 5; i++){
		EEPROM.write(((block * 5) + i), data[i]);
	}
	EEPROM.commit();
}

void memRead(int block, char *outChars){
	for(int i = 0; i < 5; i++){
		outChars[i] = EEPROM.read((block * 5) + i);
	}
}

void memDelete(int block){
	EEPROM.write((block * 5), 255);
}

int getNextEmptyMemBlock(){
	for(int i = 0; i < BLOCKS_AMOUNT; i++){
		if(EEPROM.read(i * 5) == 255){
			return i;
		}
	}
	return -1;
}

bool blocksEqual(char data1[5], char data2[5]){
	for(int i = 0; i < 5; i++){
		if(data1[i] != data2[i]){
			return false;
		}
	}
	return true;
}

int searchForBlock(char data[5]){
	char returnedData[5];
	//Search for the long and return the block.
	for(int i = 0; i < BLOCKS_AMOUNT; i++){
		memRead(i, returnedData);

		if(blocksEqual(returnedData, data)){
			return i;
		}
	}

	//Nothing found. Return -1
	return -1;
}

void defragMemory(){
	for(int i = 0; i < BLOCKS_AMOUNT; i++){
		char readi = EEPROM.read(i * 5);
		if((readi == 0) || (readi == 255)){
			for(int j = i + 1; j < BLOCKS_AMOUNT; j++){
				char readj = EEPROM.read(j * 5);
				if((readj != 0) && (readj != 255)){

					//copy all bytes to i
					for(int k = 0; k < 5; k++){
						EEPROM.write(((i * 5) + k), EEPROM.read((j * 5) + k));
					}
					EEPROM.write(j * 5, 255);
					break;
				}
			}
		}
	}

	EEPROM.commit();
	#ifdef DEBUG_MODE
		Serial.println("EEPROM defragmented");
	#endif
}

void formatMemory(){
	for(int i = 0; i < BLOCKS_AMOUNT; i++){
		EEPROM.write(i * 5, 255);
	}
	/*for(int i = 0; i < EEPROM_SIZE; i++){
		EEPROM.write(i, 255);
	}*/
	EEPROM.commit();
	#ifdef DEBUG_MODE
		Serial.println("EEPROM formatted");
	#endif

}

void insertBlock(char data[5]){
	//search for duplicates
	int block = searchForBlock(data);
	if(block != -1){
		return;
	}

	//Get the next block to write to.
	block = getNextEmptyMemBlock();
	if(block == -1){
		return;
	}
	memWrite(block, data);
	#ifdef DEBUG_MODE
		Serial.print("Block inserted on: ");
		Serial.println(block);
	#endif
}

void removeBlock(char data[5]){
	int block = searchForBlock(data);
	if(block == -1){
		return;
	}
	memDelete(block);
}
