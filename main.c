/*******************************************
 * lol, pay for washing
 ******************************************/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#include "93c46.c"
#include "uart.c"
#include "laundrycard.c"

int valid;
int balance;
char msg[128];

int main(void){
	
	//go eeprom!
	eeprom_init();
		
	//go rs232!
	uart_init();
	put_s("laundry card here\n\ncommands:\ns: get status and current balance\nf: fill card with 99.90\ne: set amount to 0.00\n\n");
		
	//the main loop does not do anything (uart event based)
	while(1){ _delay_ms(20); }
}

//event triggered when uart data recived
ISR(USART_RXC_vect) {
	switch (UDR){

		// status
		case 83:
			valid=is_valid_card();
			if (valid){
				balance=get_balance();
				sprintf(msg,"valid card, balance: %i\n", balance);
			} else {
				put_c("no card detected, double check connections");
			}
			break;
		
		//laundry 4 free
		case 70:
			valid=is_valid_card();
			if (valid){
				set_balance(0x24);
				put_c("new card balance: 99.90.-");
			} else {
				put_c("no card detected, double check connections");
			}
			break;
		
		//set balance to 0.00.-
		case 69:
			valid=is_valid_card();
			if (valid){
				set_balance(0x00);
				put_c("new card balance: 00.00.-");
			} else {
				put_c("no card detected, double check connections");
			}
			break;
		
		
		default:
			break;		
	}
	clear_uart_buffer();
}

