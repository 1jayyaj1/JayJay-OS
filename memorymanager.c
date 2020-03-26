#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memorymanager.h"
#include "kernel.h"

int launcher(char* filename) {
    FILE* f1 = fopen(filename, "rt");
    char command[50];
    strcpy(command, "cd ./BackingStore");
    system(command);
    snprintf(command, sizeof(command), "touch %s", strdup(filename));
    system(command);

    FILE* f2 = fopen(filename, "rt");



    char c; 
  
    if (f1 == NULL || f2 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    }

    c = fgetc(f1); 
    while (c != EOF) 
    { 
        fputc(c, f2); 
        c = fgetc(f1); 
    }
    fclose(f1);
    myinit(f2);
    return 0; 
}

int countTotalPages(FILE *f) {
    char c;
    int count = 0;
    c = fgetc(f); 
    while (c != EOF) {
        if (strcmp(c, "\n") == 0) {
            count += 1;
        }
    }
    return count;
}