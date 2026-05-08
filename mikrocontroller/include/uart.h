#ifndef UART_H
#define UART_H

#define MYUBRRD F_CPU/8/BAUD-1  // double speed
#define MYUBRRH F_CPU/16/baud-1 //half speed

void putcUART(char c);
char getcUART();
void putsUART(char *s, int l);
// max skal være én mindre end længden af string hvis \0 ikke skal overskrives
void getsUART(char *dest, int max);

#endif
