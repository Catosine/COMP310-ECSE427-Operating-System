#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

char * display;//TODO: Support customized display
char * cmd;//Command line

int clearShell(){
    free(display);
    free(cmd);
    return 0;
}

int main(){
    display = (char*)malloc(1000 * sizeof(char));

    cmd = (char*)malloc(1000 * sizeof(char));

    int memory_size = 100;

    // Initialize memory space
    initMem(memory_size);

    int errorCode = 0;

    // Login Interface
    printf("Welcome to the Pengnan Fan shell\nVersion 1.0 Created January 2020\n");
    strcpy(display, "& ");

    while(1){
        // Clear command
        strcpy(cmd, "");

        printf("%s", display);

        fgets(cmd, 999, stdin);
        
        int errorCode = parseInput(cmd);
        switch(errorCode){
            case -1:
                //Error
                printf("RuntimeError - Unable to run: %s", cmd);
            case 0:
                //OK
                break;
            case 1:
                //Unsupported command
                printf("RuntimeError - Unsupported command: %s", cmd);
                break;
            case 2:
                //Exit
                goto sayounara;
        }

    }

    sayounara:
        clearShell();
    
    return 0;

}