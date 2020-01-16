#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_help_info(){
    printf("COMMAND\t\t\tDESCRIPTION\n\n");
    printf("help\t\t\tDisplays all the commands\n");
    printf("quit\t\t\tExits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING\t\tAssign a value to shell memory\n");
    printf("print VAR\t\tDisplays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
    return 0;
}

int main(){
    // Login Interface
    printf("Welcome to the Pengnan Fan shell\nVersion 1.0 Created January 2020\n");
    
    // Support customized display
    char * display = (char*)malloc(1000 * sizeof(char));
    strcpy(display, "& ");

    // Command line
    char * cmd = (char*)malloc(1000 * sizeof(char));
    
    while(1){
        printf("%s", display);
        // Start of a line

        // End of a line
        strcpy(display, "");
        break;//REMOVE BEFORE USE
    }

    free((void *)display);
    free((void *)cmd);
    
    return 0;
}