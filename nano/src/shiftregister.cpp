#include "shiftregister.h"
#include <Arduino.h>

//Create a new shiftregister on the defined offsets. The chain parameter accepts the
//number of shift regsiters chained.
ShiftRegister::ShiftRegister(unsigned char direction_register, unsigned char data_register,
		int ds_offset, int shcp_offset, int stcp_offset, int chain)
{
	//No need to save the direction_register variable, it is only used in the constructor
	_data_register = data_register;
	_ds_offset = ds_offset;
	_shcp_offset = shcp_offset;
	_stcp_offset = stcp_offset;

	//Set the pins to output pins:
	/*direction_register &= (0 << _ds_offset) | (0 << _shcp_offset) | (0 << _stcp_offset);
	direction_register |= (1 << _ds_offset) | (1 << _shcp_offset) | (1 << _stcp_offset);*/

	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);

	//Set other variables:
	_chainCount = chain;
	_data = new unsigned char[chain];
	Serial.begin(9600);
}

void ShiftRegister::updateRegister(){
	//Shift out the data

	//Set the stcp pin low:
	//_data_register &= (0 << _stcp_offset);
	digitalWrite(A3, LOW);
	for(int i = 0; i < _chainCount; i++){
		//ShiftRegister::shift(i);
		shiftOut(A1, A2, LSBFIRST, _data[i]);
	}
	digitalWrite(A3, HIGH);

	//Flip the stcp pin (assuming nothing changed the register) to high:
	//_data_register |= (1 << _stcp_offset);
}

void ShiftRegister::shift(int data_index){
	for(int i = 0; i < 8; i++){
		//Save current value as a boolean
		bool value = !!(_data[data_index] & (1 << i));


		/*Set datapin to given value
		//Set the pin low to ensure the right value
		_data_register &= (0 << _ds_offset);
		//Set the pin to the set value
		_data_register |= (value << _ds_offset);*/
		digitalWrite(A1, value);






		/*Pulse the clock pin
		//Set the pin low to ensure the right value
		_data_register &= (0 << _shcp_offset);
		//Set the pin high
		_data_register |= (1 << _shcp_offset);*/

		digitalWrite(A2, LOW);
		digitalWrite(A2, HIGH);
	}
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
