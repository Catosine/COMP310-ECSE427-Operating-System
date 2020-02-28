#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include "shellmemory.h"
#include "kernel.h"

// Declaration of main functions
int decoder(int status, char *cmd);
int interpreter(char **tokenized_words);

// Delcaration of executions
int help(char **tokenized_words);
int quit(char **tokenized_words);
int there_is_nothing_to_do_with_get(char **tokenized_words);
int there_is_nothing_to_do_with_printf(char **tokenized_words);
int run(char **tokenized_words);
int exec(char **tokenized_words);
int find_last_token(char **tokenized_word);
int check_if_txt(char *name);
int freeToken(char **tokenized_words);

//--------------------- Start of Code Body ---------------------//

int decoder(int status, char *cmd)
{
    switch (status)
    {
    case -1:
        // Error
        printf("RuntimeError - Unable to run: %s", cmd);
        return 0;
    case 0:
        // Exit to shell
        return 0;
    case 1:
        // Unsupported command
        printf("RuntimeError - Unsupported command: %s", cmd);
        return 0;
    case 2:
        // bye bye this world
        return 1;
    case 3:
        printf("RuntimeError - Access denied\n");
        return 0;
    }
}

int interpreter(char **tokenized_words)
{
    if (strcmp(*tokenized_words, "help") == 0)
    {
        // help
        return help(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "quit") == 0)
    {
        // quit
        return quit(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "set") == 0)
    {
        // set VAR STRING
        return there_is_nothing_to_do_with_get(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "print") == 0)
    {
        // print VAR
        return there_is_nothing_to_do_with_printf(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "run") == 0)
    {
        // run SCRIPT.TXT
        return run(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "\0") == 0)
    {
        // empty command
        return 0;
    }
    else if (strcmp(*tokenized_words, "exec") == 0)
    {
        return exec(tokenized_words);
    }
    else
    {
        // all other undefined command
        return 1;
    }
}

int help(char **tokenized_words)
{
    freeToken(tokenized_words);
    printf("COMMAND\t\t\tDESCRIPTION\n\n");
    printf("help\t\t\tDisplays all the commands\n");
    printf("quit\t\t\tExits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING\t\tAssign a value to shell memory\n");
    printf("print VAR\t\tDisplays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
    printf("exec p1 p2 p3\t\tExecutes concurrent programs\n\t\t\t$ exec prog.txt prog2.txt\n");
    return 0;
}

int quit(char **tokenized_words)
{
    freeToken(tokenized_words);
    printf("Bye!\n");
    return 2;
}

int there_is_nothing_to_do_with_get(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx < 3)
    {
        // invalid input: STRING missing
        printf("Message: Invalid set command format. Please follow: set VAR STRING\n");
        freeToken(tokenized_word);
        return -1;
    }

    int status = setMem(*(tokenized_word + 1), *(tokenized_word + 2));

    if (status)
    {
        printf("Message: %s\n", *(tokenized_word + 2));
    }

    freeToken(tokenized_word);
    return status;
}

int there_is_nothing_to_do_with_printf(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        // invalid input: VAR missing
        printf("Message: Invalid print command format. Please follow: print VAR\n");
        freeToken(tokenized_word);
        return -1;
    }
    char *value = (char *)malloc((getMaxMem() + 1) * sizeof(char));
    int status = readMem(*(tokenized_word + 1), value);
    if (status == 0)
    {
        // find VAR in the memory
        printf("%s\n", value);
    }
    else
    {
        // cannot find VAR in the memory
        printf("Message: Variable does not exists\n");
    }

    free(value);
    freeToken(tokenized_word);
    value = NULL;

    return status;
}

int run(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        // invalid input: SCRIPT.TXT missing
        printf("Message: Invalid run command format. Please follow: run SCRIPT.TXT\n");
        freeToken(tokenized_word);
        return -1;
    }

    // check if it is a txt file
    int status = check_if_txt(*(tokenized_word + 1));
    if (status)
    {
        freeToken(tokenized_word);
        return status;
    }

    // read the script and processing
    FILE *fp = fopen(*(tokenized_word + 1), "r");

    if (fp)
    {
        char *cmd = (char *)malloc(1000 * sizeof(char));

        while (fgets(cmd, 999, fp))
        {
            status = interpreter(parse(cmd));
            if (decoder(status, cmd) || status)
            {
                goto dead;
            }
            strcpy(cmd, "");
        }
    dead:
        fclose(fp);
        free(cmd);
        freeToken(tokenized_word);
        cmd = NULL;

        return 0;
    }
    else
    {
        printf("Message: CANNOT open the file: %s\n", *(tokenized_word + 1));
        fclose(fp);
        freeToken(tokenized_word);

        return -1;
    }
}

int exec(char **tokenized_words)
{
    int zero_idx = find_last_token(tokenized_words);

    if (zero_idx <= 1)
    {
        printf("Invalid exec command format. Please follow: exec prog.txt prog2.txt\n");
        freeToken(tokenized_words);
        return -1;
    }
    else if (zero_idx > 4)
    {
        printf("Invalid exec command format. At most three programs are supported.\n");
        freeToken(tokenized_words);
        return -1;
    }
    else
    {
        // load program into RAM
        for (int id = 1; id < zero_idx; id++)
        {
            int status = check_if_txt(*(tokenized_words + id));
            if (status)
            {
                freeToken(tokenized_words);
                return status;
            }
            else
            {
                if (myinit(*(tokenized_words + id)))
                {
                    freeToken(tokenized_words);
                    return -1;
                }
            }
        }

        freeToken(tokenized_words);

        return scheduler();
        
        }
}

int find_last_token(char **tokenized_word)
{
    int zero_idx = 0;
    for (; strcmp(*(tokenized_word + zero_idx), "\0") != 0; zero_idx++)
        ;
    return zero_idx;
}

int check_if_txt(char *name)
{
    // setup regular expression for .txt file
    regex_t reg;
    const char *pattern = "^.*\\.(txt)?$";
    regcomp(&reg, pattern, REG_EXTENDED);
    const size_t nmatch = 1;
    regmatch_t pmatch[1];
    int status = regexec(&reg, name, nmatch, pmatch, 0);
    regfree(&reg);

    if (status == REG_NOMATCH)
    {
        // Input does not contain *.txt
        printf("Message: A .txt file is required as script\n");
        return -1;
    }
    else if (status == 0)
    {
        // script is confirmed as .txt file
        int existCheck = access(name, F_OK); //existance check
        int readCheck = access(name, R_OK);  //readability check
        if (existCheck == -1)
        {
            // cannot find the file
            printf("Message: File: %s does not exist\n", name);
            return -1;
        }
        if (readCheck == -1)
        {
            // no reading access to the file
            printf("Message: No access to file: %s\n", name);
            return 3;
        }
        return status;
    }
}

int freeToken(char **tokenized_words)
{
    int i = 0;
    for (; strcmp(*(tokenized_words + i), "\0") != 0; i++)
    {
        free(*(tokenized_words + i));
        *(tokenized_words + i) = NULL;
    }
    free(*(tokenized_words + i));
    *(tokenized_words + i) = NULL;
    free(tokenized_words);
    tokenized_words = NULL;
    return 0;
}