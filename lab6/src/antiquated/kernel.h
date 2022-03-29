#ifndef KERNEL_H
#define KERNEL_H
// for globals and types:
#include "type.h"

// for needed functions
#include "fork.h"
// gonna need printf from vid.c

// ADDED TO GLOBALS in TYPE.H
// PROC proc[NPROC], 
// *freeList, 
// *readyQueue, 
// *sleepList, 
// *running;

// int procsize = sizeof(PROC);
// char *pname[NPROC]={"sun", "mercury", "venus", "earth", "mars", "jupiter",
//                      "saturn","uranus","neptune"};

// char *pstatus[]={"FREE   ","READY  ","SLEEP  ","BLOCK  ","ZOMBIE ", " RUN  "};
// 
// extern PROC *kfork();

// int init();
// extern int scheduler();


// int kgetpid();

// int kgetppid();
// int kps();
// int kchname(char *s);

// int kgetPA();


#endif