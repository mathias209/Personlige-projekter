#include <avr/io.h>
#include <avr/interrupt.h>

#include "I2C.h"  //include library for i2c driver
#include "ssd1306.h" //include display driver

#include <avr/delay.h>

#include "uart.h"

#include <string.h>

char uartflag;
char uartin[130];
char *uartsptr = uartin;
int uartmax = 129;

interruptinit(&uartflag,uartin,uartsptr,&uartmax);

int main()
{
    // oled init
    _i2c_address = 0X78; // write address for i2c interface
    I2C_Init();  //initialize i2c interface to display
    InitializeDisplay(); //initialize  display
    print_fonts();
    clear_display(); // clear display :)

    initUART(1, 0, 19200);

    sei();

    while (1) {
	if (flag) {
	    clear_display();
	    memset(str, '\0', 130);
	    strptr=str;
	    flag = 0;
	}
    }

    return 0;
}

ISR(USART0_RX_vect)
{
    tis();
}
