#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char* ram[40] = { NULL };
int nextAvailableIndex = 0;

int isFrameFree(int frameNumber) {
    if (ram[frameNumber * 4] == NULL) {
        return 1;
    } else {
        return -1;
    }
}

void setRamCell(int ramCell, char* fileLine) {
    ram[ramCell] = fileLine;
}

int getNextAvailableIndex() {
    return nextAvailableIndex;
}

void addToRAM(FILE* p, int* start, int* end) {
    int errCode = 0;
    char line[40];
    if (p==NULL){
        printf("Script not found\n");
    }
    fgets(line,39,p);
    while(!feof(p)) {
        ram[nextAvailableIndex] = strdup(line);
        if (errCode != 0) {
            fclose(p);
        }
        fgets(line,39,p);
        nextAvailableIndex++;
    }
    fclose(p);
    *end = nextAvailableIndex-1;
}

char* getInstruction(int index){
    return ram[index];
}

void cleanRam() {
    for (int i = 0; i < 40; i++) {
        ram[i] = NULL;
    }
    nextAvailableIndex = 0;
}
