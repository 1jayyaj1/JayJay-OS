#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "pcb.h"

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
    return numPages;
}

int findFrame() {
    for (int i = 0; i < 10; i++) {
        if (isAvailable(i) == 1) {
            return i;
        }
    }
    return -1;
}

int findVictim(PCB *p) {
    int victimFrameNumber = rand() % (9 + 1 - 0) + 0;
    if (doesExists(victimFrameNumber) == -1) {
        while (doesExists(victimFrameNumber) != 1) {
            victimFrameNumber = (victimFrameNumber + 1) % 10;
        }
    }
    return victimFrameNumber;
}

void loadPage(int pageNumber, FILE* f, int frameNumber) {
    int lineNumber = 4 * pageNumber;
    int frameNumber = findFrame();
    if (frameNumber == -1) {
        frameNumber = findVictim(PCB *p); // TO FIGURE OUT
    }
    setPageTable(pageNumber,frameNumber);
    // Iterate on range 4 starting at lineNumber to add 4 LOC to found frame in ram
}

int launcher(char* filename) {
    FILE* f1 = fopen(filename, "r");
    char command[50];
    char path[50];
    int totalPages;
    snprintf(command, sizeof(command), "cp %s ./BackingStore", strdup(filename));
    system(command);
    snprintf(path, sizeof(path), "./BackingStore/%s", strdup(filename));
    FILE* f2 = fopen(path, "rt");
    totalPages = countTotalPages(f1);
    //printf("%d\n", totalPages);
    fclose(f1);
    myinit(f2);
    return 0;
}