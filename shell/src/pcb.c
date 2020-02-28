#include <stdlib.h>
#include "pcb.h"

PCB *makePCB(int start, int end)
{
    PCB *pcb = (PCB *)malloc(sizeof(PCB));

    pcb->start = start;
    pcb->end = end;
    pcb->PC = start;
    pcb->next = NULL;

    return pcb;
}

int deletePCB(PCB *pcb)
{
    if(pcb->next)
    {
        pcb->next = NULL;
    }

    free(pcb);
    pcb = NULL;

    return 0;
}