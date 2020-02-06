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

int parse(char *cmd)
{

    //List of used parameters
    char *tmp = (char *)malloc(100 * sizeof(char));
    char **words = (char **)malloc(500 * sizeof(char *));
    int start, idx;
    int offset = 0;

    // Skip all white spaces in the front of cmd
    for (start = 0; *(cmd + start) == ' ' && start < 1000; start++)
        ;

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

    return interpreter(words);
    
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

        if(decoder(parse(cmd), cmd)){
            break;
        }

    }

    clearShell();
    clearMem();

    return 0;

}
