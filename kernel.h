#include "pcb.h"
extern PCB* myinit(int totalPages);
extern void scheduler();

typedef struct ReadyQueueNode {
    PCB *pcb;
    struct ReadyQueueNode *next;
} ReadyQueueNode;

typedef struct ReadyQueue {
    struct ReadyQueueNode *head;
    struct ReadyQueueNode *tail;
} ReadyQueue;
