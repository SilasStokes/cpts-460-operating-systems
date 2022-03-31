#include "timer.h"

// int kprintf(char *fmt, ...);
// int kpchar(char, int, int);
// int unkpchar(char, int, int);

void timer_init()
{
  int i;
  TIMER *tp;
  kprintf("timer_init()\n");

  for (i=0; i<4; i++){
    tp = &timer[i];
    if (i==0) tp->base = (u32 *)0x101E2000; 
    if (i==1) tp->base = (u32 *)0x101E2020; 
    if (i==2) tp->base = (u32 *)0x101E3000; 
    if (i==3) tp->base = (u32 *)0x101E3020;
    //printf("%d: %x %x %x\n", i, tp->base, tp->base+TLOAD, tp->base+TVALUE);
    *(tp->base+TLOAD) = 0x8000;       // count down value
    *(tp->base+TVALUE)= 0x0;          // current counter value 
    *(tp->base+TRIS)  = 0x0;
    *(tp->base+TMIS)  = 0x0;
    *(tp->base+TCNTL) = 0x62; //011-0000=|NOTEn|Pe|IntE|-|scal=00|32-bit|0=wrap|
    *(tp->base+TBGLOAD) = 0xF0000/120;

    tp->tick = tp->hh = tp->mm = tp->ss = 0;
    strcpy((char *)tp->clock, "00:00:00");
  }
}

void timer_handler(int n) {
    u32 ris, mis, value, load, bload, i;
    TIMER *t = &timer[n];

    t->tick++;
    if (t->tick == 120){
      t->tick = 0; t->ss++;
      if (t->ss == 60){
	t->ss = 0; t->mm++;
	if (t->mm == 0){
	  t->mm = 0; t->hh++;
	}
      }
    }
    if (t->tick == 0){ // every  second
       for (i=0; i<8; i++){
           unkpchar(t->clock[i], n, 70+i);
       }
       t->clock[7]='0'+(t->ss%10); t->clock[6]='0'+(t->ss/10);
       t->clock[4]='0'+(t->mm%10); t->clock[3]='0'+(t->mm/10);
       t->clock[1]='0'+(t->hh%10); t->clock[0]='0'+(t->hh/10);
 
       for (i=0; i<8; i++){
          kpchar(t->clock[i], n, 70+i);
       }
    }

    timer_clearInterrupt(n);
    return;
} 

void timer_start(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];

  kprintf("timer_start %d base=%x\n", n, tp->base);
  *(tp->base+TCNTL) |= 0x80;  // set enable bit 7
}

int timer_clearInterrupt(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];
  *(tp->base+TINTCLR) = 0xFFFFFFFF;
}

void timer_stop(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];
  *(tp->base+TCNTL) &= 0x7F;  // clear enable bit 7
}
