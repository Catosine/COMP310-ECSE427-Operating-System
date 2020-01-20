#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include "shellmemory.h"

// Declaration of main functions
int parseInput(char *cmd);
int interpreter(char **tokenized_words);

// Delcaration of executions
int help();
int quit();
int there_is_nothing_to_do_with_get(char **tokenized_words);
int there_is_nothing_to_do_with_printf(char **tokenized_words);
int run(char **tokenized_words);
char *strcmb(char *str1, char *str2);
int find_last_token(char **tokenized_word);

//--------------------- Start of Code Body ---------------------//

int interpreter(char **tokenized_words)
{
    if (strcmp(*tokenized_words, "help") == 0)
    {
        return help();
    }
    else if (strcmp(*tokenized_words, "quit") == 0)
    {
        return quit();
    }
    else if (strcmp(*tokenized_words, "set") == 0)
    {
        return there_is_nothing_to_do_with_get(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "print") == 0)
    {
        return there_is_nothing_to_do_with_printf(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "run") == 0)
    {
        return run(tokenized_words);
    }
    else if (strcmp(*tokenized_words, "\0") == 0)
    {
        //Empty command
        return 0;
    }
    else
    {
        return 1;
    }
}

int parseInput(char *cmd)
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

        for (idx = 0; *(cmd + start) != '\0' && *(cmd + start) != '\n' && *(cmd + start) != '\t' && *(cmd + start) != ' ' && start < 1000; start++, idx++)
        {

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

    return interpreter(words);
}

int help()
{
    printf("COMMAND\t\t\tDESCRIPTION\n\n");
    printf("help\t\t\tDisplays all the commands\n");
    printf("quit\t\t\tExits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING\t\tAssign a value to shell memory\n");
    printf("print VAR\t\tDisplays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
    return 0;
}

int quit()
{
    printf("Bye!\n");
    clearMem();
    return 2;
}

int there_is_nothing_to_do_with_get(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx < 1)
    {
        printf("Message: Invalid set command format. Please follow: set VAR STRING\n");
        return -1;
    }
    else if (zero_idx > 3)
    {
        zero_idx--;
        for (; zero_idx > 2; zero_idx--)
        {
            char *temp = strcmb(*(tokenized_word + zero_idx - 1), *(tokenized_word + zero_idx));
            memset(*(tokenized_word + zero_idx - 1), 0, sizeof(*(tokenized_word + zero_idx - 1)));
            strcpy(*(tokenized_word + zero_idx - 1), temp);
            free(temp);
            temp = NULL;
        }
    }
    return setMem(*(tokenized_word + 1), *(tokenized_word + 2));
}

int there_is_nothing_to_do_with_printf(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        printf("Message: Invalid print command format. Please follow: print VAR\n");
        return -1;
    }
    char *value = (char *)malloc((getMaxMem() + 1) * sizeof(char));
    int status = readMem(*(tokenized_word + 1), value);
    if (status == 0)
    {
        printf("%s\n", value);
    }
    else
    {
        printf("Message: Variable does not exists\n");
    }
    return status;
}

int run(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        printf("Message: Invalid run command format. Please follow: run SCRIPT.TXT\n");
        return -1;
    }
    regex_t *reg;
    const char *pattern = "^.*\\.(txt)?$";
    regcomp(reg, pattern, REG_EXTENDED);
    const size_t nmatch = 1;
    regmatch_t pmatch[1];
    int status = regexec(reg, *(tokenized_word + 1), nmatch, pmatch, 0);
    if (status == REG_NOMATCH)
    {
        printf("Message: A .txt file is required as script\n");
        return -1;
    }
    else if (status == 0)
    {
        int existCheck = access(*(tokenized_word + 1), F_OK);
        int readCheck = access(*(tokenized_word + 1), R_OK);
        if (existCheck == -1)
        {
            printf("Message: File: %s does not exist\n", *(tokenized_word + 1));
            return -1;
        }
        if (readCheck == -1)
        {
            printf("Message: No access to file: %s\n", *(tokenized_word + 1));
            return 4;
        }
        printf("Message: matched\n");
        return 0;
    }
    regfree(reg);
    return -1;
}

char *strcmb(char *str1, char *str2)
{
    char *temp = (char *)malloc((strlen(str1) + strlen(str2) + 2) * sizeof(char));
    strcat(temp, str1);
    strcat(temp, " ");
    strcat(temp, str2);
    return temp;
}

int find_last_token(char **tokenized_word)
{
    int zero_idx = 0;
    for (; strcmp(*(tokenized_word + zero_idx), "\0") != 0; zero_idx++)
        ;
    return zero_idx;
}