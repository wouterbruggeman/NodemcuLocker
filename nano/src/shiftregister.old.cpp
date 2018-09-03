/*#include "shiftregister.h"
#include <Arduino.h>

//Create a new shiftregister on the defined pins. The chain parameter accepts the
//number of shift regsiters chained.
ShiftRegister::ShiftRegister(int ds_pin, int shcp_pin, int stcp_pin, int chain){


	_ds_pin = ds_pin;
	_shcp_pin = shcp_pin;
	_stcp_pin = stcp_pin;

	pinMode(ds_pin, OUTPUT);
	pinMode(shcp_pin, OUTPUT);
	pinMode(stcp_pin, OUTPUT);

	_chainCount = chain;

	_data = new unsigned char[chain];
}

void ShiftRegister::updateRegister(){
	//Shift out the data
	digitalWrite(_stcp_pin, LOW);

	for(int i = 0; i < _chainCount; i++){
		shiftOut(_ds_pin, _shcp_pin, LSBFIRST, _data[i]);
	}

	digitalWrite(_stcp_pin, HIGH);
}

//Set a particular bit in the shift register
void ShiftRegister::setBit(int bit, bool state){
	if(bit > _chainCount * 8){
		return;
	}

	//AND the bit to be sure the bit equals 0:
	_data[bit % 8] &= (1 << bit);
	//OR the bit to set the new value:
	_data[bit & 8] |= (state << bit);
}

//Set an entire byte in the shift register
void ShiftRegister::setByte(int byte, char data){
	if(byte  > _chainCount){
		return;
	}

	//Update the data
	_data[byte] = data;
}

void ShiftRegister::setNibble(int byte, bool nibble, char data){
	if(byte > _chainCount){
		return;
	}

	//Set the nibble to zeros:
	_data[byte] &= (240 >> (nibble * 4));

	//OR the bits:
	_data[byte] |= (data << (nibble * 4));
}
*/
