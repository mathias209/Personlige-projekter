#include <avr/io.h>

// 5 bits
void setAdcCh(char channel)
{
    ADMUX&=0b11100000;
    ADCSRB&=0b11110111;

    ADMUX|=channel;
    ADCSRB|=((channel>>4)<<MUX5);
}

// starts conversion and polls
unsigned int sampleAdc()
{
    ADCSRA|=(1<<ADSC);

    while(!(1<<ADIF&ADCSRA))
	;

    return ADC;
}
