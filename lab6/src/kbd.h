#ifndef KBD_H
#define KBD_H
#include "type.h"

#include "keymap"
#include "keymap2"

#define LSHIFT 0x12
#define RSHIFT 0x59
#define ENTER  0x5A
#define LCTRL  0x14
#define RCTRL  0xE014

#define ESC    0x76
#define F1     0x05
#define F2     0x06
#define F3     0x04
#define F4     0x0C

#define KCNTL 0x00
#define KSTAT 0x04
#define KDATA 0x08
#define KCLK  0x0C
#define KISTA 0x10
// extern PROC *running;

typedef volatile struct kbd{
  char *base;
  char buf[128];
  int head, tail, data, room;
}KBD;

int kputc(char);

volatile KBD kbd;
int shifted = 0;
int release = 0;
int control = 0;
volatile int kline;
volatile int keyset;

int kbd_init();

// kbd_handler1() for scan code set 1
void kbd_handler1();

// kbd_handelr2() for scan code set 2
void kbd_handler2();

void kbd_handler();


int kgetc();

int kgets(char s[ ]);

int getc() ;
int kgetline(char s[ ]);



#endif