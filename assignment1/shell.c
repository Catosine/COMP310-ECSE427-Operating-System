#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

int main(){
    // Login Interface
    printf("Welcome to the Pengnan Fan shell\nVersion 1.0 Created January 2020\n");
    
    // Support customized display
    char * display = (char*)malloc(1000 * sizeof(char));
    strcpy(display, "& ");

    // Command line
    char * cmd = (char*)malloc(1000 * sizeof(char));

    int errorCode = 0;
    
    while(1){
        // Clear command
        strcpy(cmd, "");

        printf("%s", display);
        
        fgets(cmd, 999, stdin);

        int errorCode = parseInput(cmd);
        switch(errorCode){
            case 0:
                //OK
                break;
            default:
                //All other unseen commands
                printf("Unsupported command: %s", cmd);
        }

    }

    free((void *)display);
    free((void *)cmd);
    
    return 0;

}