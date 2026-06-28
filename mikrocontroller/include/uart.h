#ifndef UART_H

void initUART(char profile, char n, int baud);
void putcUART(char c);
void putsUART(char *s, int l);
void tis();
void interruptinit(char *inflag, char *instrptr, char *instr, int *inmax);

#endif
