#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MEM{
    char * var;
    char * value;
};

int mem_len;
struct MEM * memory;

//Number of element kept in the memory
int size = 0;

int getMemLength(){
    return mem_len;
}

int getMemSize(){
    return size;
}

int initMem(int size){
    memory = (struct MEM *)malloc(size*sizeof(struct MEM));
    mem_len = size;
    return 0;
}

int existMem(char * var){
    for(int i = 0; i<size; i++){
        if(strcmp((memory+i)->var, var)==0){
            return i;
        }
    }
    //Not found
    return -1;
}

int updateMem(char * var, char * value){
    int idx = existMem(var);
    if (idx!=-1){
        strcpy((memory+idx)->value, value);
        return 0;
    }
    return -1;
}

int createMem(char * var, char * value){
    if(existMem(var)<0&&size<mem_len){
        struct MEM newItem;
        newItem.var = (char *)malloc(sizeof(var));
        newItem.value = (char *)malloc(sizeof(value));
        memcpy(newItem.var, var, sizeof(var));
        memcpy(newItem.value, value, sizeof(value));
        memcpy(memory+size, &newItem, sizeof(struct MEM));
        size++;
        return 0;
    }
    return -1;
}

int readMem(char * var, char * value){
    int idx = existMem(var);
    if (idx!=-1){
        strcpy(value, (memory+idx)->value);
        return 0;
    }
    return -1;
}

int deleteMem(char * var, char * value){
    int idx = existMem(var);
    if(idx>=0){
        for(; idx<size-1; idx++){
            struct MEM next = *(memory+idx+1);
            memcpy(memory+idx, &next, sizeof(struct MEM));
        }
        size--;
    }
    return 0;
}

int setMem(char * var, char * value){
    if(updateMem(var, value)==0){
        return 0;
    } else {
        return createMem(var, value);
    }
}

int clearMem(){
    free(memory);
    memory = NULL;
    return 0;
}