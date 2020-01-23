#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include "shellmemory.h"

// Declaration of main functions
int decoder(int status, char *cmd);
int parseInput(char *cmd);
int interpreter(char **tokenized_words);

// Delcaration of executions
int help();
int quit();
int there_is_nothing_to_do_with_get(char **tokenized_words);
int there_is_nothing_to_do_with_printf(char **tokenized_words);
int run(char **tokenized_words);
int find_last_token(char **tokenized_word);

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
        return help();
    }
    else if (strcmp(*tokenized_words, "quit") == 0)
    {
        // quit
        return quit();
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
    else
    {
        // all other undefined command
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
    return 2;
}

int there_is_nothing_to_do_with_get(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx < 3)
    {
        // invalid input: STRING missing
        printf("Message: Invalid set command format. Please follow: set VAR STRING\n");
        return -1;
    }

    int status = setMem(*(tokenized_word + 1), *(tokenized_word + 2));

    if (status)
    {
        printf("Message: %s\n", *(tokenized_word + 2));
    }

    free(tokenized_word);
    tokenized_word = NULL;
    return status;
}

int there_is_nothing_to_do_with_printf(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        // invalid input: VAR missing
        printf("Message: Invalid print command format. Please follow: print VAR\n");
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
    free(tokenized_word);
    value = NULL;
    tokenized_word = NULL;

    return status;
}

int run(char **tokenized_word)
{
    int zero_idx = find_last_token(tokenized_word);
    if (zero_idx <= 1)
    {
        // invalid input: SCRIPT.TXT missing
        printf("Message: Invalid run command format. Please follow: run SCRIPT.TXT\n");
        return -1;
    }

    // setup regular expression for .txt file
    regex_t reg;
    const char *pattern = "^.*\\.(txt)?$";
    regcomp(&reg, pattern, REG_EXTENDED);
    const size_t nmatch = 1;
    regmatch_t pmatch[1];
    int status = regexec(&reg, *(tokenized_word + 1), nmatch, pmatch, 0);
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
        int existCheck = access(*(tokenized_word + 1), F_OK); //existance check
        int readCheck = access(*(tokenized_word + 1), R_OK);  //readability check
        if (existCheck == -1)
        {
            // cannot find the file
            printf("Message: File: %s does not exist\n", *(tokenized_word + 1));
            return -1;
        }
        if (readCheck == -1)
        {
            // no reading access to the file
            printf("Message: No access to file: %s\n", *(tokenized_word + 1));
            return 3;
        }

        // read the script and processing
        FILE *fp = fopen(*(tokenized_word + 1), "r");

        if (fp)
        {
            char *cmd = (char *)malloc(1000 * sizeof(char));

            while (fgets(cmd, 999, fp))
            {
                if (decoder(parseInput(cmd), cmd))
                {
                    return 0;
                }
                strcpy(cmd, "");
            }

            fclose(fp);
            free(cmd);
            free(tokenized_word);
            tokenized_word = NULL;
            cmd = NULL;

            return 0;
        }
        else
        {
            printf("Message: CANNOT open the file: %s\n", *(tokenized_word + 1));

            free(tokenized_word);
            tokenized_word = NULL;

            return -1;
        }
    }

    free(tokenized_word);
    tokenized_word = NULL;

    return -1;
}

int find_last_token(char **tokenized_word)
{
    int zero_idx = 0;
    for (; strcmp(*(tokenized_word + zero_idx), "\0") != 0; zero_idx++)
        ;
    return zero_idx;
}