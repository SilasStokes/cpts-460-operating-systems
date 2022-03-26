
#ifndef TIMER_H
#define TIMER_H
#include "type.h"

// timer.c file
/***** timer confiuguration values *****/
#define CTL_ENABLE          ( 0x00000080 )
#define CTL_MODE            ( 0x00000040 )
#define CTL_INTR            ( 0x00000020 )
#define CTL_PRESCALE_1      ( 0x00000008 )
#define CTL_PRESCALE_2      ( 0x00000004 )
#define CTL_CTRLEN          ( 0x00000002 )
#define CTL_ONESHOT         ( 0x00000001 )

// timer register offsets from base address
/**** byte offsets *******
#define TLOAD   0x00 : count down to 0 then reload
#define TVALUE  0x04 : currrent value of counter
#define TCNTL   0x08 : control register
#define TINTCLR 0x0C : interrupt clear register
#define TRIS    0x10 : raw interrupt status register
#define TMIS    0x14 : masked interrupt status register
#define TBGLOAD 0x18 : background load register; reload to TLOAD periodically
*************************/
/** u32 * offsets *****/
#define TLOAD   0x0
#define TVALUE  0x1
#define TCNTL   0x2
#define TINTCLR 0x3
#define TRIS    0x4
#define TMIS    0x5
#define TBGLOAD 0x6

typedef volatile struct timer{
  u32 *base;            // timer's base address; as u32 pointer
  int tick, hh, mm, ss; // per timer data area
  char clock[16]; 
}TIMER;
volatile TIMER timer[4];  // 4 timers; 2 timers per unit; at 0x00 and 0x20



int kprintf(char *fmt, ...);
int kpchar(char, int, int);
int unkpchar(char, int, int);

void timer_init();

void timer_handler(int n);

void timer_start(int n);

int timer_clearInterrupt(int n);

void timer_stop(int n);


#endif