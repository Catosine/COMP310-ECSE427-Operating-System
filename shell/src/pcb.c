#include <stdlib.h>
#include "pcb.h"

PCB* makePCB(int start, int end)
{
    PCB* pcb = (PCB*)malloc(sizeof(PCB));

    pcb->start = start;
    pcb->end = end;
    pcb->PC = 0;
    pcb->next = NULL;
    
    return pcb;
}