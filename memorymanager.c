#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "pcb.h"
#include "ram.h"

int countTotalPages(FILE *fp) {
    int count = 0;
    int numPages = 0;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n'){
            count = count + 1; 
        }
    }
    numPages = count / 4;
    if (count % 4 != 0) {
        numPages += 1;
    }
    fclose(fp);
    return numPages;
}

int findFrame() {
    for (int i = 0; i < 10; i++) {
        if (isFrameFree(i) == 1) {
            return i;
        }
    }
    return -1;
}

int findVictim(PCB *p) {
    int victimFrameNumber = rand() % (9 + 1 - 0) + 0;
    if (doesExists(victimFrameNumber, p) == -1) {
        while (doesExists(victimFrameNumber, p) != 1) {
            victimFrameNumber = (victimFrameNumber + 1) % 9;
        }
    }
    return victimFrameNumber;
}

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame) {
    p->pageTable[pageNumber] = frameNumber;
    if (victimFrame != -1) {
        p->pageTable[pageNumber] = victimFrame;
    }
    return 0; //Not good function AND value return, figure out both tmr
}

void loadPage(int pageNumber, FILE* f, int frameNumber) {
    int lineNumberStart = 4 * pageNumber;
    int lineNumberEnd = lineNumberStart + 4;
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), f)) {
        if(i >= lineNumberStart && i < lineNumberEnd) {
            setRamCell(i, strdup(line)); 
        } else if (i == lineNumberEnd) {
            break;
        }
        i++;
    }
}

int launcher(char* filename) {
    FILE* f1 = fopen(filename, "r");
    char command[50];
    char path[50];
    snprintf(command, sizeof(command), "cp %s ./BackingStore", strdup(filename));
    system(command);
    snprintf(path, sizeof(path), "./BackingStore/%s", strdup(filename));
    FILE* f2 = fopen(path, "rt");
    int totalPages = countTotalPages(f1);
    PCB* pcb = myinit(totalPages);
    int frameNumber = findFrame();
    if (frameNumber == -1) {
        frameNumber = findVictim(pcb);
    }
    loadPage(pcb->PC_page, f2, frameNumber);
    return 0;
}