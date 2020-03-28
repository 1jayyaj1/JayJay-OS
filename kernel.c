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
#include "memorymanager.h"

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

PCB* myinit(int totalPages) {
    PCB* pcb = makePCB(0, 0, totalPages);
    addToReady(pcb);
    return pcb;
}

int interrupt(CPU* cpu, PCB* pcb) {
    int nextPage = (pcb->PC_page)++;
    if (nextPage > pcb->pages_max) {
        return -1;
    } else {
        int frameNumber;
        if (pcb->pageTable[nextPage] != -1) {
            frameNumber = pcb->pageTable[nextPage];
        } else {
            int frameNumber = findFrame();
            if (frameNumber == -1) {
                frameNumber = findVictim(pcb);
                updatePageTable(pcb, nextPage, frameNumber, frameNumber);
            }
            updatePageTable(pcb, nextPage, frameNumber, frameNumber);
            loadPage(nextPage, pcb->filePtr, frameNumber);
        }
        pcb->PC_page = nextPage;
        pcb->PC = frameNumber * 4;
        pcb->PC_offset = 0;
    }
    return 0;
}

void scheduler() {
    cpu = createCPU();
    ReadyQueueNode* temp;
    int processComplete = 0;
    while (isEmpty() == -1) {
        temp = getNext();
        cpu->IP = temp->pcb->PC_page;
        cpu->offset = temp->pcb->PC_offset;
        if ((temp->pcb->PC_offset)+2 > 3) {
            cpu->quanta = 1;
            run(cpu, l);
            processComplete = interrupt(cpu, temp->pcb);
        } else {
            run(cpu, l);
            temp->pcb->PC_offset = cpu->offset;
        }
        if (processComplete == -1) {
            free(temp->pcb);
        } else {
            addToReady(temp->pcb);
        }
    }
    cleanRam();
}

void boot() {
    char command[50];
    strcpy(command, "rm -rf BackingStore && mkdir BackingStore");
    system(command);
}

int main() {
    boot();
    l = List_create();
    rq = createReadyQueue();
    shellUI(l);
}
