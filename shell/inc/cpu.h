typedef struct kirin
{
    int IP;
    char *IR;
    int quanta;
} CPU;

CPU *hisilicon();
int runCPU(CPU *kirin);
int deleteCPU(CPU *kirin);