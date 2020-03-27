#ifndef PCB_H
#define PCB_H
typedef struct PCB {
    int PC;
    int PC_page;
    int PC_offset;
    int pages_max;
    int pageTable[10];
} PCB;

PCB* makePCB(int pageNumber, int pageOffset, int totalPages);
#endif
extern int doesExists(int frameNumber, PCB *p);
