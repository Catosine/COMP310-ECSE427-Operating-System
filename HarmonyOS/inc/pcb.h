typedef struct pcb 
{
    int PC;
    int start;
    int end;
    struct pcb* next;
} PCB;

PCB* makePCB(int start, int end);
int deletePCB(PCB* pcb);