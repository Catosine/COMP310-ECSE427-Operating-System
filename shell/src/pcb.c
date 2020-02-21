#include <stdlib.h>
#include "pcb.h"

int PC = 0;

PCB* makePCB(int start, int end){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->start = start;
    pcb->end = end;
    pcb->PC = PC;
    PC++;
    return pcb;
}