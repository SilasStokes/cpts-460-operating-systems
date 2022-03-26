#ifndef FORK_H
#define FORK_H
#include "type.h"
// #include "globals.h"
// need freelist
// need running

// not sure what these are doing
int goUmode();
char *istring = "init start";


PROC *kfork(char *filename);

int fork();

#endif