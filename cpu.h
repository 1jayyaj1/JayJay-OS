#include "shellmemory.h"
typedef struct CPU {
    int IP;
    char IR[1000];
    int quanta;
} CPU;

extern void run(CPU* cpu, List *l);
