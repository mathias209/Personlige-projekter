#include <avr/io.h>

#include "ssd1306.h" //include display driver

unsigned char putcMaster(unsigned char c)
{
    PORTB&=~(1<<PB0);

    SPDR=c;

    while(!(SPSR&(1<<SPIF)))
	;
    PORTB|=(1<<PB0);

    return SPDR;
}

unsigned char getcSlave(unsigned char c)
{
    SPDR=c;

    while(!(SPSR&(1<<SPIF)))
	;

    return SPDR;
}

void readTemp(unsigned char* MSB, unsigned char* LSB)
{
    PORTB &= ~(1<<PB0);

    SPDR=0x00;

    while(!(SPSR&(1<<SPIF)))
	;
    *MSB = SPDR;
    SPDR=0x00;
    while(!(SPSR&(1<<SPIF)))
	;
    *LSB = SPDR;

    PORTB|= (1<<PB0);
}
