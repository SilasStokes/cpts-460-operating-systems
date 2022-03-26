#ifndef VID_H
#define VID_H
#include "type.h"


// vid.c file: implement fbuf for the ARM PL110 LCD display
/**************** Reference: ARM PL110 and DUI02241 ********************
Color LCD base address: 0x10120000 - 0x1012FFFF
00    timing0
04    timing1
08    timing2
0C    timing3
10    upperPanelframeBaseAddressRegister // use only ONE panel
14    lowerPanelFrameBaseAddressRegister // some display allows 2 panels
18    interruptMaskClrregister
1C    controlRegister
20    interruptStatusReg
etc
************************************************************************/
#include "font0"

u8 cursor;
int volatile *fb;
unsigned char *font;
int row, col;

int fbuf_init();

int clrpix(int x, int y);

int setpix(int x, int y);

int dchar(unsigned char c, int x, int y);

int undchar(unsigned char c, int x, int y);

int dstring(char *s, int x, int y);

int scroll();
  
int kpchar(char c, int ro, int co);

int unkpchar(char c, int ro, int co);

int erasechar();

int clrcursor();

int putcursor(unsigned char c);

int kputc(char c);

int kprints(char *s);

int krpx(u32 x);

int kprintx(u32 x);

int krpu(u32 x);

int kprintu(u32 x);

int kprinti(int x);

int kprintf(char *fmt,...);

int stestring(char *s);

#endif