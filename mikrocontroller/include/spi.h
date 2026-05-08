#ifndef SPI_H
#define SPI_H

unsigned char putcMaster(unsigned char c);
unsigned char getcSlave(unsigned char c);
void readTemp(unsigned char* MSB, unsigned char* LSB);

#endif
