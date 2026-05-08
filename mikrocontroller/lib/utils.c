#include <string.h>
#include <stdio.h>

void inttobin(char *dest, int in, int width)
{
    strcpy(dest, "");
    for (int i = 0; i<width; i++) {
	if(in&(1))
	    strcat(dest, "1");
	else
	    strcat(dest, "0");
	in=in>>1;
    }
    strrev(dest);
}

void integerfrac(int a, int b, int prec, int *q, int *df)
{
    *q=a/b;
    int r = (a*prec)%(b*prec);
    *df=r/b;
}
