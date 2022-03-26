#ifndef QUEUE_H
#define QUEUE_H
#include "type.h"
// gonna need vid.c


// extern PROC *freeList;

PROC *getproc();

int putproc(PROC *p);

int enqueue(PROC **queue, PROC *p);

PROC *dequeue(PROC **queue);

int printQ(PROC *p);

int printSleepList(PROC *p);

int printList(PROC *p);

#endif