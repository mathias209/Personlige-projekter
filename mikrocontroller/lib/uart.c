#include <avr/io.h>
#include <uart.h>

char getcUART()
{
    while(!(UCSR0A&(1<<RXC0)))
	;
    return UDR0;
}

void putcUART(char c)
{
    while(!(UCSR0A&(1<<UDRE0)))
	;

    UDR0=c;
}

void putsUART(char *s, int l)
{
    char *ptr = s;
    for(int i = 0; i<l; i++)
	putcUART(*ptr++);
}

void getsUART(char *dest, int max)
{
    char c;
    int n = 0;

    // dette virker siden getc funktion venter på data
    while((c=getcUART())!='\r' && (n++)<max) {
	*(dest+n)=c;
    }
    *(dest+n+1)='\0';
}
