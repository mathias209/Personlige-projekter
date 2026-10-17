#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#include <stdio.h>

#define BAUD 19200UL
#define MYUBRRD F_CPU/8/BAUD -1

void putchUSART0(char tx){
  while(!(UCSR0A&(1<<UDRE0)));
  UDR0=tx;
}

void putsUSART0(char* str, int len){
  for(int i=0; i < len; i++){
    putchUSART0(*str);
    str++;
  }
}

char msg[100];
int msglen = 0;

int main()
{
    // uart
    UCSR0A=(1<<U2X0);
    UCSR0B|=(1<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0);
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UBRR0H = (unsigned char)(MYUBRRD>>8);
    UBRR0L = (unsigned char)(MYUBRRD);

    DDRE|=(1<<DDE1);

    while(1)
    {
	putsUSART0("tis\n\r", 5);
	_delay_ms(100);
    }
}
