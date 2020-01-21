#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

char *display; //TODO: Support customized display
char *cmd;     //Command line

int clearShell()
{
    free(display);
    free(cmd);
    display = NULL;
    cmd = NULL;
    return 0;
}

int main()
{
    // assign memory space for display and command
    display = (char *)malloc(100 * sizeof(char));
    cmd = (char *)malloc(1000 * sizeof(char));

    int memory_size = 100;

    // Initialize memory space
    initMem(memory_size);

    int errorCode = 0;

    // Login Interface
    printf("Welcome to the Pengnan Fan shell\nVersion 1.0 Created January 2020\n");
    strcpy(display, "& ");

    while (1)
    {
        // Clear command
        strcpy(cmd, "");

        printf("%s", display);

        fgets(cmd, 999, stdin);

        if(decoder(parseInput(cmd), cmd)){
            break;
        }

    }

    clearShell();
    clearMem();

    return 0;

}