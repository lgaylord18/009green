///009 Green
///Game Library
///Card Class
#include <algorithm>



// Represents Single RFID card
// with associated integer value
class Card {
		int value;
   		uint8_t UID[4];
   	public:
   		//mutators
   		void set_value(int);
   		void set_UID(uint8_t*);

   		//observers
   		uint8_t* get_UID();
   		int get_value();
};

void Card::set_UID(uint8_t* uidValue){
	std::copy(uidValue,uidValue+4,UID);

};

void Card::set_value(int value){
	value = value;
};

uint8_t* Card::get_UID(){
	return UID;
};

int Card::get_value(){
	return value;
};
