#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"

int pageTable[10];
int PC_page;
int PC_offset;
int pages_max;

void setPageTable(int pageNumber, int frameNumber) {
    pageTable[pageNumber] = frameNumber;
}

void isAvailable(int pageNumber) {
    if (pageTable[pageNumber] == NULL) {
            return 1; //Don't use this frameNumber
    } else {
        return -1;
    }
}
int doesExists(int frameNumber) {
    for (int i = 0; i < 10; i++) {
        if (pageTable[i] == frameNumber) {
            return -1; //Don't use this frameNumber
        }
    }
    return 1; //Use this frameNumber
}

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
