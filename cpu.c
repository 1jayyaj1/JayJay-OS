#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "ram.h"
#include "interpreter.h"
#include "kernel.h"

void run(CPU* cpu, List *l) {
    for (int i = 0; i < cpu->quanta; i++) {
        cpu->offset = cpu->offset + i;
        int address = cpu->IP + cpu->offset;
        interpret(getInstruction(address), l);
    }
}
