#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512
#define BLOCK_SIZE 5
#define BLOCK_AMOUNT (EEPROM_SIZE - (EEPROM_SIZE % BLOCK_SIZE) / BLOCK_SIZE)

#define EMPTY_BLOCK_PREFIX 255

class MemoryManager{
	public:
		MemoryManager();
		int getFreeBlocks();
		void writeBlock(char *data);
		void deleteBlock(int index);
		void readBlock(int index, char *outChars);
		int findBlock(char *data);
		void defrag();
		void format();
}

#endif
