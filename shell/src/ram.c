#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kernel.h"

char **ram;
int firstAvailable;
int ram_size;

int clearRamAll();

int findAvailable(){
    for(int i = 0; i<ram_size; i++){
        if(!ram[i]){
            return i;
        }
    }
    return -1;
}

int initRam(int size)
{
    ram = (char **)malloc(size*sizeof(char *));

    for(int i = 0; i<size; i++)
    {
        ram[i] = NULL;
    }

    firstAvailable = 0;
    ram_size = size;

    return 0;
}

// it returns the next line of availiability
void addToRAM(FILE* p, int *start, int *end){

    char *cmd = (char *)malloc(1000 * sizeof(char));
    *start = firstAvailable;

    while (fgets(cmd, 999, p))
    {

        if (firstAvailable>=ram_size)
        {
            // no available space left
            printf("Core Dumped: Out of RAM\n");

            clearRamAll();
            free(cmd);
            cmd = NULL;

            return;

        }

        size_t cmd_size = (strlen(cmd)+1)*sizeof(char);
        ram[firstAvailable] = (char* )malloc(cmd_size);

        memcpy(ram[firstAvailable], cmd, cmd_size);

        firstAvailable++;

    }

    *end = firstAvailable-1;

    return;

}

// clear range: [start, end)
int clearRam(int start, int end)
{
    for(start; start<end; start++)
    {
        if(ram[start]){
            free(ram[start]);
            ram[start] = NULL;
        }
    }

    free(ram);
    ram = NULL;

    return 0;
}

int clearRamAll(){return clearRam(0, ram_size);}