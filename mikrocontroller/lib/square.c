#include <avr/io.h>
#include <avr/interrupt.h>

volatile char nextB = 2;
volatile char nextC = 3;
volatile char COMBmask = 0b11001111;
volatile char COMCmask = 0b11110011;

void initSquarewave(int f)
{
    TCCR1A|=(nextB<<COM1B0)|(nextC<<COM1C0);
    TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
    TIMSK1|=(1<<OCIE1C)|(1<<OCIE1B);
    DDRB=(1<<PB6)|(1<<PB7);

    long top = 8000000/f;
    ICR1=top;
    OCR1A=ICR1/2;
}

void setFreq(int f)
{
    long top = 8000000/f;
    ICR1=top;
    OCR1A=ICR1/2;
}

ISR(TIMER1_COMPB_vect)
{
    TCCR1A&=COMBmask;
    TCCR1A|=(nextB<<COM1B0);
    if (nextB==2)
	nextB=3;
    else
	nextB=2;
}

ISR(TIMER1_COMPC_vect)
{
    TCCR1A&=COMCmask;
    TCCR1A|=(nextC<<COM1C0);
    if (nextC==2)
	nextC=3;
    else
	nextC=2;
}
