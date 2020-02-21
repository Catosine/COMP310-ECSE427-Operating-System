#include <stdlib.h>
#include <stdio.h>
#include "kernel.h"
#define  ram_size 1000

char *ram[ram_size];
int firstAvailable;

int initRam(){
    for(int i = 0; i<ram_size; i++){
        ram[i] = NULL;
    }
    firstAvailable = 0;
    return 0;
}

// it returns the next line of availiability
void addToRAM(FILE* p, int *start, int *end){
    char *cmd = (char *)malloc(1000 * sizeof(char));
    while (fgets(cmd, 999, p))
    {   
        int status = parse(cmd);
    }
    return;
}