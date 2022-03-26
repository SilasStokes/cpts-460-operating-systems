#ifndef WAIT_H
#define WAIT_H

#include "type.h"


int ksleep(int event);

int kwakeup(int event);

int kexit(int value);

int kwait(int *status);

 #endif
