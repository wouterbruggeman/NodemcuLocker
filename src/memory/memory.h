#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include <EEPROM.h>

#define MEM_UID 1
#define EEPROM_SIZE 512

void setupMemory();
void memWrite(int block, char data[5]);
void memRead(int block, char* outChars);
void memDelete(int block);
int getNextEmptyMemBlock();
bool blocksEqual(char data1[5], char data2[5]);
int searchForBlock(char data[5]);
void defragMemory();
void formatMemory();
void insertBlock(char data[5]);
void removeBlock(char data[5]);

#endif
