#ifndef ACCEPTEDCARDS_H
#define ACCEPTEDCARDS_H

#include "Arduino.h"

#define UID_SIZE 4

class CardDatabase{
	public:
		CardDatabase(char *filename);
		void add(uint8_t card[UID_SIZE]);
		void remove(uint8_t card[UID_SIZE]);
		int find(uint8_t card[UID_SIZE]);
		bool contains(uint8_t card[UID_SIZE]);
		void clear();
	private:
		void remove(int index);

		//Variables
		char *_filename;
};

#endif
