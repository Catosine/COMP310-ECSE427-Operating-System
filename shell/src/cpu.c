#include <stdlib.h>
#include "cpu.h"
#include "ram.h"
#include "interpreter.h"
#include "kernel.h"

#define IR_SIZE 1000

CPU *hisilicon()
{
    CPU *hisilicon_yes = (CPU *)malloc(sizeof(CPU));

    hisilicon_yes->IR = NULL;
    hisilicon_yes->quanta = 0;

    return hisilicon_yes;
}

int deleteCPU(CPU *kirin)
{
    if (kirin->IR)
    {
        free(kirin->IR);
        kirin->IR = NULL;
    }

    free(kirin);
    kirin = NULL;

    return 0;
}

int runCPU(CPU *kirin)
{
    while (kirin->quanta > 0)
    {
        kirin->IR = readSlot(kirin->IP);

        if (!kirin->IR)
        {
            return -1;
        }

        if (interpreter(parse(kirin->IR)))
        {
            return 2;
        }

        kirin->IP++;

        // one quanta used
        kirin->quanta--;
    }

    return 0;
}