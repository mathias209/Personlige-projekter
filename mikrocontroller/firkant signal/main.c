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

#include "square.h"


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

    // timer for ms delay
    // mode 4, PS 8, OCR 2000
    TCCR3B|=(1<<WGM32)|(1<<CS31);
    TIMSK3|=(1<<OCIE3A);
    OCR3A=2000;

    initSquarewave(1000);

    sei();

    for (int i = 0; i<sizeof(tetris)/sizeof(tetris[0]); i++) {
	setFreq(tetris[i].freq);
	while(ms<tetris[i].delayms)
	    ;
	ms=0;
    }
    while(1) {
	// inaudible
	setFreq(21000);
    }
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
