#include "memorymanager.h"

MemoryManager::MemoryManager(){
	EEPROM.begin(EEPROM_SIZE);
}

int MemoryManager::getFreeBlocks(){
	return BLOCK_AMOUNT;
}

void MemoryManager::writeBlock(char *data){
	int block = this.getEmptyBlock();
	if(block == -1){
		return;
	}

	for(int i = 0; i < BLOCK_SIZE; i++){
		EEPROM.write(((block * BLOCK_SIZE) + i),data[i])
	}
}

void MemoryManager::deleteBlock(int index){
	EEPROM.write(index * BLOCK_SIZE, EMPTY_BLOCK_PREFIX);
}

void MemoryManager::readBlock(int index, char *outChars){
	for(int i = 0; i < BLOCK_SIZE; i++){
		outChars[i] = EEPROM.read((index * BLOCK_SIZE) + i);
	}
}

int MemoryManager::findBlock(char *data){
	for(int i = 0; i < BLOCK_AMOUNT; i++){
		char currentBlock[BLOCK_SIZE];
		this.readBlock(i, data);
		if(this.dataEquals(currentBlock, data)){
			return i;
		}
	}
	return -1;
}

bool MemoryManager::dataEquals(char *data1, char *data2){
	for(int i = 0; i < BLOCK_SIZE; i++){
		if(data1[i] != data2[i]){
			return false;
		}
	}
	return true;
}

int MemoryManager::getEmptyBlock(){
	for(int i = 0; i < BLOCK_AMOUNT; i++){
		if(EEPROM.read(i * BLOCK_SIZE) == EMPTY_BLOCK_PREFIX){
			return i;
		}
	}
	return 0;
}

void MemoryManager::format(){
	for(int i = 0 ; i < BLOCK_AMOUNT; i++){
		EEPROM.write(i * BLOCK_SIZE, EMPTY_BLOCK_PREFIX);
	}
	this.commit();
}

void MemoryManager::commit(){
	EEPROM.commit();
}
