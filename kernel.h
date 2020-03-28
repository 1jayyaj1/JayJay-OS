#include "pcb.h"
#include "cpu.h"
extern PCB* myinit(int totalPages);
extern void scheduler();
extern int interrupt(CPU* cpu, PCB* pcb);

typedef struct ReadyQueueNode {
    PCB *pcb;
    struct ReadyQueueNode *next;
} ReadyQueueNode;

typedef struct ReadyQueue {
    struct ReadyQueueNode *head;
    struct ReadyQueueNode *tail;
} ReadyQueue;
