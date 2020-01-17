#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"

// Declaration of main functions
int parseInput(char * cmd);
int interpreter(char ** tokenized_words);

// Delcaration of executions
int help();
int quit();
int there_is_nothing_to_do_with_get(char ** tokenized_words);
int there_is_nothing_to_do_with_printf(char ** tokenized_words);

//--------------------- Start of Code Body ---------------------//

int interpreter(char ** tokenized_words){
    if(strcmp(*tokenized_words, "help")==0){
        return help();
    } else if(strcmp(*tokenized_words, "quit")==0){
        return quit();
    } else if(strcmp(*tokenized_words, "set")==0){
        return there_is_nothing_to_do_with_get(tokenized_words);
    } else if(strcmp(*tokenized_words, "print")==0){
        return there_is_nothing_to_do_with_printf(tokenized_words);
    } else if(strcmp(*tokenized_words, "run")==0){
        return 1;
    } else {
        return 1;
    }
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
    int times = 0;
    while(*(cmd+start) != '\0' && *(cmd+start) != '\n'){

        for(idx = 0; *(cmd+start) != '\0' && *(cmd+start) != '\n' && *(cmd+start) != '\t' && *(cmd+start) != ' ' && start<1000; start++, idx++){
            
            *(tmp+idx) = *(cmd+start);

        }

        *(tmp+idx) = '\0';

        // Filter out in-line spaces
        if(strcmp(tmp, "\0")!=0){
            *(words+offset++) = strdup(tmp);
        }

        start++;
    }

    // Suggest the end of the tokens
    *(words+offset) = strdup("\0");

    return interpreter(words);

}

int help(){
    printf("COMMAND\t\t\tDESCRIPTION\n\n");
    printf("help\t\t\tDisplays all the commands\n");
    printf("quit\t\t\tExits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING\t\tAssign a value to shell memory\n");
    printf("print VAR\t\tDisplays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
    return 0;
}

int quit(){
    printf("Bye!\n");
    clearMem();
    return 2;
}

int there_is_nothing_to_do_with_get(char ** tokenized_word){
    // if(strcmp(*(tokenized_word+3), "\0")!=0||strcmp(*(tokenized_word+2), "\0")==0||strcmp(*(tokenized_word+1), "\0")==0||strcmp(*(tokenized_word), "set")!=0){
    //     printf("Message: Invalid set command format. Please follow: set VAR STRING\n");
    //     return -1;
    // }
    return setMem(*(tokenized_word+1), *(tokenized_word+2));
}

int there_is_nothing_to_do_with_printf(char ** tokenized_word){
    if(strcmp(*(tokenized_word+2), "\0")!=0||strcmp(*(tokenized_word+1), "\0")==0||strcmp(*(tokenized_word), "print")!=0){
        printf("Message: Invalid print command format. Please follow: print VAR\n");
        return -1;
    }
    char * value;
    int status = readMem(*(tokenized_word+1), value);
    if(status==0){
        printf("%s\n", value);
    } else {
        printf("Message: Variable does not exists\n");
    }
    return status;
}