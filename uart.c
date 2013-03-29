/*******************************************
 * super simple uart driver
 ******************************************/

#define BAUD 9600UL    
#define TERM_MAX_INPUT_LENGTH 2

#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)
 
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error baudrate error too high (bigger than 1%)
#endif


volatile char unsigned uart_buffer[TERM_MAX_INPUT_LENGTH];
unsigned char uart_user_input[TERM_MAX_INPUT_LENGTH];
char uart_buffer_pos = 0;


void put_c (unsigned char buffer) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = buffer;
}

void put_s (const char *s) { 
	while ( !(UCSRA & (1<<UDRE)));
	while (*s) {
		put_c(*s);
		s++;
	}
}

void clear_uart_buffer(){
	memset(&uart_buffer[0], 0, sizeof(uart_buffer));
}

void uart_init(void){
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRB |= (1<<RXCIE);
	UCSRC |= (1<<UCSZ0)|(1<<UCSZ1);
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0x0FF;
	sei();
	_delay_us(50);
}
