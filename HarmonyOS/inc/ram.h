#include <stdio.h>

int initRam(int size);
int clearRam(int start, int end);
int unmountRam();
int clearRamAll();
void addToRAM(FILE *p, int *start, int *end);
char *readSlot(int index);