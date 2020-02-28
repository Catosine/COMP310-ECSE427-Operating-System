#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "ram.h"
#include "pcb.h"

#define DISPLAY_SIZE 100
#define CMD_BUFFER_SIZE 1000
#define MEM_SIZE 1000
#define RAM_SIZE 1000

char *display;      // TODO: Support customized display
char *cmd;          // Command line
PCB* head = NULL;   // pointer to the first PCB
PCB* tail = NULL;   // pointer to the last PCB

int clearShell()
{
    free(display);
    free(cmd);
    display = NULL;
    cmd = NULL;
    return 0;
}

char** parse(char *cmd)
{

    //List of used parameters
    char *tmp = (char *)malloc(100 * sizeof(char));
    char **words = (char **)malloc(500 * sizeof(char *));
    int start, idx;
    int offset = 0;

    // Skip all white spaces in the front of cmd
    for (start = 0; *(cmd + start) == ' ' && start < 1000; start++);

    // Tokenized the cmd
    int times = 0;
    while (*(cmd + start) != '\0' && *(cmd + start) != '\n')
    {

        for (idx = 0; *(cmd + start) != '\0' && *(cmd + start) != '\n' && *(cmd + start) != '\t' && start < 1000; start++, idx++)
        {

            if (*(cmd + start) == '\\' && *(cmd + start + 1) == ' ')
            {
                start++;
            }
            if (*(cmd + start) == ' ' && *(cmd + start - 1) != '\\')
            {
                break;
            }

            *(tmp + idx) = *(cmd + start);
        }

        *(tmp + idx) = '\0';

        // Filter out in-line spaces
        if (strcmp(tmp, "\0") != 0)
        {
            *(words + offset++) = strdup(tmp);
        }

        start++;
    }

    // Suggest the end of the tokens
    *(words + offset) = strdup("\0");

    free(tmp);
    tmp = NULL;

    return words;
    
}

int shellUI()
{
    // assign memory space for display and command
    display = (char *)malloc(DISPLAY_SIZE * sizeof(char));
    cmd = (char *)malloc(CMD_BUFFER_SIZE * sizeof(char));

    // Initialize memory space
    initMem(MEM_SIZE);
    initRam(RAM_SIZE);

    int errorCode = 0;

    // Login Interface
    printf("Kernel 1.0 loaded!\nWelcome to the Pengnan Fan shell!\nShell Version 2.0 Updated February 2020\n");
    strcpy(display, "& ");

    while (1)
    {
        // Clear command
        strcpy(cmd, "");

        printf("%s", display);

        fgets(cmd, CMD_BUFFER_SIZE-1, stdin);
        
        int status = interpreter(parse(cmd));
        if(decoder(status, cmd)){
            free(cmd);
            cmd = NULL;
            break;
        }

    }

    clearShell();
    clearMem();
    clearRamAll();

    return 0;

}

void addToReady(PCB* newPCB)
{
    if(!head&&!tail)
    {
        head = newPCB;
        tail = newPCB;
    } 
    else 
    {
        tail->next = newPCB;
        tail = newPCB;
    }
}

int myinit(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        int start, end;
        addToRAM(fp, &start, &end);
        fclose(fp);

        if(start<0||end<0)
        {
            printf("Message: CANNOT load the file: %s to RAM\n", filename);
            goto fail;
        }
        
        PCB* pcb = makePCB(start, end);

        addToReady(pcb);

    } else {
        printf("Message: CANNOT open the file: %s\n", filename);
        fail:
            clearRamAll();
            fclose(fp);
            return -1;
    }
}

int scheduler()
{

}