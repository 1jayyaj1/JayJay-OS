#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"

int doesExists(int frameNumber, PCB *p) {
    for (int i = 0; i < 10; i++) {
        if (p->pageTable[i] == frameNumber) {
            return -1; //Don't use this frameNumber
        }
    }
    return 1; //Use this frameNumber
}

PCB* makePCB(int pageNumber, int pageOffset, int totalPages) {
    PCB *pcb = malloc(sizeof(PCB));
    pcb->PC = pageNumber + pageOffset;
    pcb->PC_page = pageNumber;
    pcb->PC_offset = pageOffset;
    pcb->pages_max = totalPages;
    return pcb;
}
