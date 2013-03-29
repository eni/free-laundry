/*******************************************
 * laundrycard functions
 * lol, pay for washing
 ******************************************/

//balance is stored in followed locations
char balance_locations[6]=7,9,11,18,20,21;
//card size in bits
int card_size=1024;

unsigned char get_balance(){
	int ret=eeprom_read(0x07);
	return ret;
}

void set_balance(int amount){
	for (int i=0;i<6;i++){
		int act_adress=balance_locations[i];
		eeprom_write(act_adress,amount);
	}
}

unsigned int is_valid_card(){
	int chk=eeprom_read(0x00);
	if (chk==0xe8){
		return 1;
	} else {
		return 0;
	}
}

char dump_card(){
	char card_content;
	for (int i=0;i>card_size;i++){
		card_content += eeprom_read(i);
	}
	return card_content;
}
