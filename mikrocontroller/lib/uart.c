#include <avr/io.h>
#include <avr/interrupt.h>

int UBRR(int baud, char mode)
{
    long num;
    switch (mode) {
	case 0:
	    num = 1000000;
	    break;
	case 1:
	    num = 2000000;
	    break;
    }
    return num/baud-1;
}

// 0: basic, 1: basic with interrupt
void initUART(char profile, char n, int baud)
{
    char UCSRnA, UCSRnB, UCSRnC;
    int UBRRD;
    switch (profile) {
	case 0:
	    UCSRnA=0b00000010;
	    UCSRnB=0b00011000;
	    UCSRnC=0b00000110;
	    UBRRD=UBRR(baud, 1);
	    break;
	case 1:
	    UCSRnA=0b00000010;
	    UCSRnB=0b10011000;
	    UCSRnC=0b00000110;
	    UBRRD=UBRR(baud, 1);
	    break;
    }

    switch (n) {
	case 0:
	    UCSR0A=UCSRnA;
	    UCSR0B=UCSRnB;
	    UCSR0C=UCSRnC;
	    UBRR0=UBRRD;
	    break;
	case 1:
	    UCSR1A=UCSRnA;
	    UCSR1B=UCSRnB;
	    UCSR1C=UCSRnC;
	    UBRR1=UBRRD;
	    break;
	case 2:
	    UCSR2A=UCSRnA;
	    UCSR2B=UCSRnB;
	    UCSR2C=UCSRnC;
	    UBRR2=UBRRD;
	    break;
	case 3:
	    UCSR3A=UCSRnA;
	    UCSR3B=UCSRnB;
	    UCSR3C=UCSRnC;
	    UBRR3=UBRRD;
	    break;
    }
}

void putcUART(char c)
{
    while (!(UCSR0A&(1<<UDRE0)))
	;
    UDR0=c;
}

void putsUART(char *s, int l)
{
    int i = 0;
    while (*(s+i)!='\0' && i < l) {
	putcUART(*(s+(i++)));
    }
}

char *flag,*strptr,*str;
int *max;

void interruptinit(char *inflag, char *instrptr, char *instr, int *inmax)
{
    flag=inflag;
    strptr=instrptr;
    str=instr;
    max=inmax;
}

void tis()
{
    if (!(*flag)) {
	*strptr=UDR0;
	if (*strptr=='\r' || strptr-str+1 >= *max) {
	    *flag = 1;
	    *strptr='\0';
	} else
	    strptr++;
    } else {
	UDR0;
    }
}
