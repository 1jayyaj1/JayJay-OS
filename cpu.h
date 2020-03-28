#include "shellmemory.h"
#ifndef CPU_H
#define CPU_H
typedef struct CPU {
    int IP;
    int offset;
    char IR[40];
    int quanta;
} CPU;

extern void run(CPU* cpu, List *l);
#endif
