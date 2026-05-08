#include <avr/io.h>

// for timer 1, 3, 4 og 5
void initPFPWM(int timer, int PS, int TPWN, int TON)
{
    switch(timer) {
	case 1:
	    TCCR1A|=(0<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
	    TCCR1B|=(1<<WGM13)|(0<<WGM12)|PS;
	    ICR1=TPWN;
	    OCR1A=TON;
	    DDRB|=(1<<PB5);
	    break;
	case 3:
	    TCCR3A|=(0<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
	    TCCR3B|=(1<<WGM13)|(0<<WGM12)|PS;
	    ICR3=TPWN;
	    OCR3A=TON;
	    DDRE|=(1<<PE3);
	    break;
	case 4:
	    TCCR4A|=(0<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
	    TCCR4B|=(1<<WGM13)|(0<<WGM12)|PS;
	    ICR4=TPWN;
	    OCR4A=TON;
	    DDRH|=(1<<PH3);
	    break;
	case 5:
	    TCCR5A|=(0<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
	    TCCR5B|=(1<<WGM13)|(0<<WGM12)|PS;
	    ICR5=TPWN;
	    OCR5A=TON;
	    DDRL|=(1<<PL3);
	    break;
    }
}
