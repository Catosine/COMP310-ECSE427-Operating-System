#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MEM
{
    char *var;
    char *value;
};

int mem_len; // memory size assigned
struct MEM *memory = NULL;
int max_mem = 0; // max size of value stored in memory

// Number of element kept in the memory
int size = 0;

// BKDR Hash
unsigned int hash(char *str)
{

    unsigned int seed = 233;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF) % mem_len;
}

int getMemLength()
{
    return mem_len;
}

int getMemSize()
{
    return size;
}

int initMem(int size)
{
    // assign memory space
    memory = (struct MEM *)malloc(size * sizeof(struct MEM));

    // initialize each memory struct
    for (int i = 0; i < size; i++)
    {
        (memory + i)->var = NULL;
        (memory + i)->value = NULL;
    }

    mem_len = size;

    return 0;
}

// Finished Implementation
int existMem(char *var)
{
    int hash_value = hash(var);
    for (int i = 0; i < mem_len; i++)
    {
        char *varToCheck = (memory + (hash_value + i) % mem_len)->var;
        if (varToCheck)
        {
            // if var exists
            if (strcmp(varToCheck, var) == 0)
            {
                // if var is the same as expected
                return (hash_value + i) % mem_len;
            }
        }
    }

    return -1;
}

// Finished Implementation
int updateMem(char *var, char *value)
{
    int idx = existMem(var);
    if (idx >= 0)
    {
        // found var and update corresponding value
        char *result = strcpy((memory + idx)->value, value);
        return strcmp(result, value);
    }
    return -1;
}

// Finished Implementation
int createMem(char *var, char *value)
{
    if (existMem(var) < 0 && size < mem_len)
    {
        // if var does not exist in memory and memory is not full
        int hash_value = hash(var);
        for (int i = 0; i < mem_len; i++)
        {
            struct MEM *toCheck = memory + (hash_value + i) % mem_len;
            if (!toCheck->var)
            {
                // if empty slot
                size_t varlen = (strlen(var) + 1) * sizeof(char);
                int currlen = strlen(value);
                size_t valuelen = (currlen + 1) * sizeof(char);

                // assign value to each var and value in the slot
                toCheck->var = (char *)malloc(varlen);
                toCheck->value = (char *)malloc(valuelen);

                // store var and value to the memory
                memcpy(toCheck->var, var, varlen);
                memcpy(toCheck->value, value, valuelen);

                size++;

                // update max_mem
                max_mem = (currlen > max_mem) ? currlen : max_mem;
                return 0;
            }
        }
    }

    return -1;
    
}

// Finished Implementation
int readMem(char *var, char *value)
{
    int hash_value = hash(var);
    for (int i = 0; i < mem_len; i++)
    {
        struct MEM *toCheck = memory + (hash_value + i) % mem_len;
        if (toCheck->var)
        {
            // if slot toCheck has var
            if (strcmp(toCheck->var, var) == 0)
            {
                // read value from toCheck out
                char *result = strcpy(value, toCheck->value);
                return strcmp(result, value);
            }
        }

    }

    return -1;
}

int deleteMem(char *var, char *value)
{
    int idx = existMem(var);
    if (idx >= 0)
    {
        struct MEM *toDelete = (memory + idx);

        // free pointer in toDelete
        free(toDelete->var);
        free(toDelete->value);

        // points to NULL for furthur use
        toDelete->var = NULL;
        toDelete->value = NULL;

        size--;
    }

    return 0;
}

int setMem(char *var, char *value)
{
    if (updateMem(var, value) == 0)
    {
        // var exists in memory, then update directly
        int currlen = strlen(value);
        max_mem = (currlen > max_mem) ? currlen : max_mem;
        return 0;
    }
    else
    {
        // var does not exist in memory, then create new slot
        return createMem(var, value);
    }
}

int getMaxMem() { return max_mem; }

int clearMem()
{
    for (int i = 0; i < size; i++)
    {   
        struct MEM * toClear = memory+i;
        free(toClear->var);
        free(toClear->value);
        (memory + i)->var = NULL;
        (memory + i)->value = NULL;
    }
    free(memory);
    memory = NULL;
    return 0;
}