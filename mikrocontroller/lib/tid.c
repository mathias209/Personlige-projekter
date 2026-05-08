#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tid.h"

unsigned long getTime(char *s)
{
    unsigned int mm,ss;
    unsigned long hh;
    sscanf(s, "%lu:%d:%d", &hh, &mm, &ss);

    return (hh*60*60)+(mm*60)+ss;
}
