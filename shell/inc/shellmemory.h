typedef struct Memory
{
    char *var;
    char *value;
}MEM;
int initMem(int size);
int createMem(char *var, char *value);
int readMem(char *var, char *value);
int updateMem(char *var, char *value);
int deleteMem(char *var, char *value);
int existMem(char *var);
int setMem(char *var, char *value);
int clearMem();
int getMaxMem();