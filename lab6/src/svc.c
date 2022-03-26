
#include "svc.h"

int svc_handler(volatile int a, int b, int c, int d)
{
  int r; 
  // if (a<90) 
  //   kprintf("svc_handler: a=%d b=%d c=%x d=%x\n",a,b,c,d);
  switch(a){
     case 0: r = kgetpid(); break;
     case 1: r = kgetppid(); break;
     case 2: r = kps(); break;
     case 3: r = kchname((char *)b); break;
     case 4: r = kfork(b); break;
     case 5: r = tswitch(); break;
     case 6: r = kwait((int *)b); break;
     case 7: r = kexit(b); break;

     case 9: r = fork(); break;
     case 10: r = exec((char *)b); break;

     case 90: r = kgetc() & 0x7F;  break;
     case 91: r = kputc(b); break;
     case 92: r = kgetPA(); break;
     default: printf("invalid syscall %d\n", a);
  }

  running->kstack[SSIZE - 14] = r;

  return r; // return to to goUmode: which MAY replace uR0 in Kstack with r
}

 
