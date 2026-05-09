#ifndef TETRIS_H
#define TETRIS_H

#include "notes.h"

#define QUA 429
#define EIG 214
#define SIX 107

typedef struct {
    int delayms, freq;
} Note;

Note tetris[] = {
    {QUA,E4},
    {QUA,E4},
    {EIG,B4},
    {EIG,C5},
    {EIG,D5},
    {SIX,E5},
    {SIX,D5},
    {EIG,C5},
    {EIG,B4},
    {QUA,A4},
    {EIG,A4},
    {EIG,C5},
    {QUA,E5},
    {EIG,D5},
    {EIG,C5},
    {QUA,B4},
    {EIG,B4},
    {EIG,C5},
    {QUA,D5},
    {QUA,E5},
    {QUA,C5},
    {QUA,A4},
    {QUA,A4},
    {QUA,REST},
    {EIG,REST},
    {QUA,D5},
    {EIG,F5},
    {QUA,A5},
    {EIG,G5},
    {EIG,F5},
    {QUA*1.5,E5},
    {EIG,C5},
    {QUA,E5},
    {EIG,D5},
    {EIG,C5},
    {QUA,B4},
    {EIG,B4},
    {EIG,C5},
    {QUA,D5},
    {QUA,E5},
    {QUA,C5},
    {QUA,A4},
    {QUA,A4},
    {QUA,REST}
};


#endif
