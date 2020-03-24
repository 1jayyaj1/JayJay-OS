#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"

PCB *pcb_create(int p, int s, int e) {
    PCB *pcb = malloc(sizeof(PCB));
    pcb->PC = p;
    pcb->start = s;
    pcb->end = e;
    return pcb;
}

PCB* makePCB(int start, int end) {
    PCB* pcb = pcb_create(start, start, end);
    return pcb;
}
