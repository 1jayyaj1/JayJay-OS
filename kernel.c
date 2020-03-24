#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "interpreter.h"
#include "shellmemory.h"
#include "kernel.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"

ReadyQueueNode *createReadyQueueNode() {
    ReadyQueueNode *rqn = malloc(sizeof(ReadyQueueNode));
    rqn->pcb = NULL;
    rqn->next = NULL;
    return rqn;
}

ReadyQueue *createReadyQueue() {
    ReadyQueue *rq = malloc(sizeof(ReadyQueue));
    rq->head = NULL;
    rq->tail = NULL;
    return rq;
}

CPU *createCPU() {
    CPU *cpu = malloc(sizeof(CPU));
    cpu->quanta = 2;
    return cpu;
}

List *l;
ReadyQueue* rq;
CPU* cpu;

void addToReady(PCB* p) {
    ReadyQueueNode* rqn = createReadyQueueNode();
    rqn->pcb = p;
    if (rq->head == NULL && rq->tail == NULL) {
        rq->head = rqn;
        rq->tail = rqn;
    } else {
        rqn->next = rq->tail;
        rq->tail = rqn;
    }
}

int isEmpty() {
    if (rq->head == NULL && rq->tail == NULL) {
        return 1; //List is empty - true
    }
    return -1;  //List is not empty - false
}

 void removePCB() {
    if (rq->head == rq->tail) {
        rq->head = NULL;
        rq->tail = NULL;
    } else {
        ReadyQueueNode* rqn = rq->tail;
        while (rqn->next != rq->head) {
            rqn = rqn->next;
        }
        rqn->next = NULL;
        rq->head = rqn;
    }
}

ReadyQueueNode* getNext() {
    ReadyQueueNode* temp = rq->head;
    removePCB();
    return temp;
}

void myinit(char* filename) {
    FILE *p = fopen(filename,"rt");
    if (p == NULL){
        printf("%s not found\n", filename);
    } else {
        int start = getNextAvailableIndex();
        int end = 0;
        addToRAM(p, &start, &end);
        PCB* pcb = makePCB(start, end);
        addToReady(pcb);
    }
}

void scheduler() {
    cpu = createCPU();
    ReadyQueueNode* temp;
    while (isEmpty() == -1) {
        temp = getNext();
        cpu->IP = temp->pcb->PC;
        if ((temp->pcb->PC)+2 > temp->pcb->end) {
            cpu->quanta = 1;
        }
        run(cpu, l);
        temp->pcb->PC = (cpu->IP) + 1;
        if (cpu->IP != temp->pcb->end) {
            addToReady(temp->pcb);
        } else {
            free(temp->pcb);
        }
    }
    cleanRam();
}

void boot() {
    char command[50];
    strcpy(command, "rm -rf BackingStore");
    system(command);
    strcpy(command, "mkdir BackingStore");
    system(command);
}

int main() {
    boot();
    l = List_create();
    rq = createReadyQueue();
    shellUI(l);
}
