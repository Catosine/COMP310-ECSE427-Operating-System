#include "cpu.h"
#define IR_SIZE 1000

CPU* hisilicon(int quanta)
{
    CPU* hisilicon_yes = (CPU* )malloc(sizeof(CPU));

    hisilicon_yes->IR = (char* )malloc(IR_SIZE*sizeof(char));
    hisilicon_yes->quanta = quanta;

    return hisilicon_yes;
}