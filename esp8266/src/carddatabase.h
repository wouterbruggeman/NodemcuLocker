#ifndef ACCEPTEDCARDS_H
#define ACCEPTEDCARDS_H

#include "Arduino.h"

#define UID_SIZE 4
#define PASSCODE_SIZE 4
#define BLOCK_SIZE (UID_SIZE + PASSCODE_SIZE)

class CardDatabase{
	public:
		CardDatabase(char *filename);
		void add(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]);
		void remove(uint8_t card[UID_SIZE]);
		bool contains(uint8_t card[UID_SIZE], uint8_t code[PASSCODE_SIZE]);

		//Lower level functions
		int find(uint8_t card[UID_SIZE]);
	private:
		void remove(int index);
		void clear();
		void debugPrintFile();

		//Variables
		char *_filename;
};

#endif
