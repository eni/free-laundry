/*******************************************
 * laundrycard functions
 * lol, pay for washing
 ******************************************/


unsigned int get_balance(){
	eeprom_read(0x07);
	return dataword;
}

void set_balance(int amount){
	eeprom_write(7,amount);
	eeprom_write(9,amount);
	eeprom_write(11,amount);
	eeprom_write(18,amount);
	eeprom_write(20,amount);
	eeprom_write(21,amount);
}

unsigned int is_valid_card(){
	eeprom_read(0x00);
	eeprom_read(0x00);
	if (dataword==0xe8){
		return 1;
	} else {
		return 0;
	}
}
