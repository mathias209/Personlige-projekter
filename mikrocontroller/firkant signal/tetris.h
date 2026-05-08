#ifndef TETRIS_H
#define TETRIS_H

#include "notes.h"

#define QUA 429
#define EIG 214
#define SIX 107

typedef struct {
    int delayms, freq;
    char disp[4];
} Note;

Note tetris[] = {
    {QUA,E4, " E4"},
    {QUA,E4, " E4"},
    {EIG,B4, " B4"},
    {EIG,C5, " C5"},
    {EIG,D5, " D5"},
    {SIX,E5, " E5"},
    {SIX,D5, " D5"},
    {EIG,C5, " C5"},
    {EIG,B4, " B4"},
    {QUA,A4, " A4"},
    {EIG,A4, " A4"},
    {EIG,C5, " C5"},
    {QUA,E5, " E5"},
    {EIG,D5, " D5"},
    {EIG,C5, " C5"}
};


#endif
