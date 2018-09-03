#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

class ShiftRegister{
	public:
		ShiftRegister(unsigned char direction_register, unsigned char data_register,
				int ds_offset, int shcp_offset, int stcp_offset, int chain);
		void updateRegister();
		void setBit(int bit, bool state);
		void setByte(int byte, char data);
		void setNibble(int byte, bool nibble, char data);
	private:
		//Functions:
		void shift(int data_index);

		//Variables:
		unsigned char _data_register;
		int _ds_offset;
		int _shcp_offset;
		int _stcp_offset;

		//ow many shift registers are in chain.
		int _chainCount;

		unsigned char *_data;

};

#endif
