#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char* ram[1000] = { NULL };
int nextAvailableIndex = 0;

int getNextAvailableIndex() {
    return nextAvailableIndex;
}

void addToRAM(FILE* p, int* start, int* end) {
    int errCode = 0;
    char line[1000];
    if (p==NULL){
        printf("Script not found\n");
    }
    fgets(line,999,p);
    while(!feof(p)) {
        ram[nextAvailableIndex] = strdup(line);
        if (errCode != 0) {
            fclose(p);
        }
        fgets(line,999,p);
        nextAvailableIndex++;
    }
    fclose(p);
    *end = nextAvailableIndex-1;
}

char* getInstruction(int index){
    return ram[index];
}

void cleanRam() {
    for (int i = 0; i < 1000; i++) {
        ram[i] = NULL;
    }
    nextAvailableIndex = 0;
}
