#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaration of main functions
int parseInput(char * cmd);
int interpreter(char ** tokenized_words);

// Delcaration of executions
int get_help_info();

//--------------------- Start of Code Body ---------------------//

int interpreter(char ** tokenized_words){
    return 0;
}

int parseInput(char * cmd){

    //List of used parameters
    char * tmp = (char *)malloc(100 * sizeof(char));
    char ** words = (char **)malloc(500 * sizeof(char *));
    int start, idx;
    int offset = 0;

    // Skip all white spaces in the front of cmd
    for(start = 0; *(cmd+start)==' ' && start<1000; start++);

    // Tokenized the cmd 
    while(*(cmd+start) != '\0' && *(cmd+start) != '\n'){

        for(idx = 0; *(cmd+start) != '\0' && *(cmd+start) != '\n' && *(cmd+start) != '\t' && *(cmd+start) != ' ' && start<1000; start++, idx++){
            
            *(tmp+idx) = *(cmd+start);

        }

        *(tmp+idx) = '\0';

        // Filter out in-line spaces
        if(*(tmp)!='\0'){*(words+offset++) = strdup(tmp);}

        start++;

    }

    // Suggest the end of the tokens
    *(words+offset) = strdup("\0");

    return interpreter(words);

}

int get_help_info(){
    printf("COMMAND\t\t\tDESCRIPTION\n\n");
    printf("help\t\t\tDisplays all the commands\n");
    printf("quit\t\t\tExits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING\t\tAssign a value to shell memory\n");
    printf("print VAR\t\tDisplays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
    return 0;
}