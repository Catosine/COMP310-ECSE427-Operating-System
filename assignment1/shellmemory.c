#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MEM{
    char * var;
    char * value;
};

int mem_len;
struct MEM * memory = NULL;
int max_mem = 0;

//Number of element kept in the memory
int size = 0;

//BKDR Hash
unsigned int hash(char *str){

    unsigned int seed = 427;
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF)%mem_len;
}

int getMemLength(){
    return mem_len;
}

int getMemSize(){
    return size;
}

int initMem(int size){
    memory = (struct MEM *)malloc(size*sizeof(struct MEM));
    for(int i=0; i<size; i++){
        (memory+i)->var = NULL;
        (memory+i)->value = NULL;
    }
    mem_len = size;
    return 0;
}

// Finished Implementation
int existMem(char * var){
    int hash_value = hash(var);
    for(int i = 0; i<mem_len; i++){
        char * varToCheck = (memory+(hash_value+i)%mem_len)->var;
        if(varToCheck){if(strcmp(varToCheck, var)==0){return (hash_value+i)%mem_len;}}
    }
    return -1;
}

// Finished Implementation
int updateMem(char * var, char * value){
    int idx = existMem(var);
    if (idx>=0){
        char * result = strcpy((memory+idx)->value, value);
        return strcmp(result, value);
    }
    return -1;
}

// Finished Implementation
int createMem(char * var, char * value){
    if(existMem(var)<0&&size<mem_len){
        int hash_value = hash(var);
        for(int i = 0; i<mem_len; i++){
            if(!(memory+(hash_value+i)%mem_len)->var){
                (memory+(hash_value+i)%mem_len)->var = (char *)malloc((strlen(var)+1)*sizeof(char));
                (memory+(hash_value+i)%mem_len)->value = (char *)malloc((strlen(value)+1)*sizeof(char));
                memcpy((memory+(hash_value+i)%mem_len)->var, var, (strlen(var)+1)*sizeof(char));
                memcpy((memory+(hash_value+i)%mem_len)->value, value, (strlen(value)+1)*sizeof(char));
                size++;
                int currlen = strlen(value);
                max_mem = (currlen>max_mem)? currlen:max_mem;
                return 0;
            }
        }
    }
    return -1;
}

// Finished Implementation
int readMem(char * var, char * value){
    int hash_value = hash(var);
    if((memory+hash_value)->var){
        for(int i = 0; i<mem_len; i++){
            char * varToRead = (memory+(hash_value+i)%mem_len)->var;
            char * valueToRead = (memory+(hash_value+i)%mem_len)->value;
            if(varToRead){
                if(strcmp(varToRead, var)==0){
                    char * result = strcpy(value, valueToRead);
                    return strcmp(result, value);
                }
            }
            return 0;
        }
    }
    return -1;
}

int deleteMem(char * var, char * value){
    int idx = existMem(var);
    if(idx>=0){
        (memory+idx)->var = NULL;
        (memory+idx)->value = NULL;
        size--;
    }
    return 0;
}

// Finished Implementation
int setMem(char * var, char * value){
    if(updateMem(var, value)==0){
        int currlen = strlen(value);
        max_mem = (currlen>max_mem)? currlen:max_mem;
        return 0;
    } else {
        return createMem(var, value);
    }
}

int get_max_mem(){return max_mem;}

int clearMem(){
    free(memory);
    memory = NULL;
    return 0;
}