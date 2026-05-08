 /*
  * Firkant signal med PWM
  * af Mathias Ø. Selander
  *
  */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "I2C.h"  //include library for i2c driver
#include "ssd1306.h" //include display driver

#include <avr/delay.h>

#define BAUD 19200
#include "uart.h"

#include "utils.h"

#include "tetris.h"

volatile char nextB = 2;
volatile char nextC = 3;
volatile char COMBmask = 0b11001111;
volatile char COMCmask = 0b11110011;

char in[8];
char *inptr = in;
int flag = 0;

volatile int ms = 0;

int main()
{
    // oled init
    _i2c_address = 0X78; // write address for i2c interface
    I2C_Init();  //initialize i2c interface to display
    InitializeDisplay(); //initialize  display
    clear_display(); // clear display :)
   
    // USART init
    UCSR0A=(1<<U2X0);
    UCSR0B|=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UBRR0H = (unsigned char)(MYUBRRD>>8);
    UBRR0L = (unsigned char)(MYUBRRD);

    // timer init
    // mode 12, ICRn=8000, OCnA toggle mode, OCRnA halvdelen af ICRn
    TCCR1A|=(nextB<<COM1B0)|(nextC<<COM1C0);
    TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
    TIMSK1|=(1<<OCIE1C)|(1<<OCIE1B);
    ICR1=8000;
    OCR1A=4000;
    DDRB=(1<<PB6)|(1<<PB7);

    // timer for ms delay
    // mode 4, PS 8, OCR 2000
    TCCR3B|=(1<<WGM32)|(1<<CS31);
    TIMSK3|=(1<<OCIE3A);
    OCR3A=2000;


    sei();

    // char in[20];
    // memset(in, '\0', 20);
    int f = 0;
    long top;

    char msg[20];

    int sec = 0;

    // putsUART("ready\r\n", 7);
    // sprintf(msg, "%d/%d=%d", sizeof(tetris),sizeof(tetris[0]),sizeof(tetris)/sizeof(tetris[0]));
    // sendStrXY(msg, 0, 0);

       for (int i = 0; i<sizeof(tetris)/sizeof(tetris[0]); i++) {
	    top=8000000/tetris[i].freq;
	    sprintf(msg, "%2d: %s", i, tetris[i].disp);
	    sendStrXY(msg, 0, 0);
	    ICR1=top;
	    OCR1A=ICR1/2;
	    while(ms<tetris[i].delayms)
		;
	    ms=0;
       }
    while(1) {
	top=8000000/20000;
	ICR1=top;
	OCR1A=ICR1/2;
	// if (flag) {
	//     sscanf(in, "%d", &f);
	//     sprintf(msg, "frq: %5d", f);
	//     sendStrXY(msg, 0, 0);
	//
	//     if (f<123 || f>20000) {
	// 	continue;
	//     }
	//     top=8000000/f;
	//     sprintf(msg, "top: %5ld", top);
	//     sendStrXY(msg, 1, 0);
	//     ICR1=top;
	//     OCR1A=ICR1/2;
	//
	//     inptr=in;
	//     flag = 0;
	// } else {
	//     _delay_us(1);
	// }
	// sprintf(msg, "%10s", in);
	// sendStrXY(msg, 1, 0);
	// sscanf(in, "%d", &f);
	// sprintf(msg, "%d\r\n", f);
	// putsUART(msg, 10);
	// if (f<123 || f>20000) {
	//     continue;
	// }
	// top=8000000/f;
	// sprintf(msg, "%5ld", top);
	// sendStrXY(msg, 0, 0);
	// ICR1=top;
	// OCR1A=ICR1/2;
    }
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

// uart recieve complete intterupt
ISR(USART0_RX_vect)
{
    *inptr = UDR0;
    if (*inptr=='\r') {
	*inptr='\0';
	flag = 1;
    } else
	inptr++;
}

ISR(TIMER3_COMPA_vect)
{
    ms++;
}
