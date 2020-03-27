#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"

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

void loadPage(int pageNumber, FILE* f, int frameNumber) {

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