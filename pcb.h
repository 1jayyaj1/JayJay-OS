#ifndef PCB_H
#define PCB_H
typedef struct PCB {
    int PC;
    int start;
    int end;
} PCB;

PCB* makePCB(int start, int end);
#endif

extern void setPageTable(int pageNumber, int frameNumber);
extern int doesExists(int frameNumber);
extern void isAvailable(int pageNumber);
