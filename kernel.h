#include "pcb.h"
extern void myinit(FILE* p);
extern void scheduler();

typedef struct ReadyQueueNode {
    PCB *pcb;
    struct ReadyQueueNode *next;
} ReadyQueueNode;

typedef struct ReadyQueue {
    struct ReadyQueueNode *head;
    struct ReadyQueueNode *tail;
} ReadyQueue;
