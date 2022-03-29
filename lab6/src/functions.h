#ifndef FUNCS
#define FUNCS
#include "type.h"


/* ts.s */
extern int reset_handler();
extern int irq_handler();         // IRQ entry point
extern int data_handler();
extern int tswitch();
extern int svc_entry();
extern int goUmode();
extern int unlock();
extern int lock();
extern int int_on();
extern int int_off();
extern int getcsr();

// extern int vectors_start();

extern int switchPgdir();

/* exec.c */
int exec(char *cmdline);

/* fork.c */

int goUmode();
// char *istring = "init start";
PROC *kfork(char *filename);
int fork();


/* kbd.c */
// also need the types from kbd.h
// int kputc(char); // this is NOT in kbd.c
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

/* kernel.c */
int init();
int scheduler();
int kgetpid();
int kgetppid();
int kps();
int kchname(char *s);
int kgetPA();

/* load.c*/
int search(INODE *ip, char *name);
int load(char *filename, PROC *p);


/* queue.c */
PROC *getproc();
int putproc(PROC *p);
int enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);
int printQ(PROC *p);
int printSleepList(PROC *p);
int printList(PROC *p);

/* sdc.c */
// bunch of definitions and types in sdc.h
// shared variables between SDC driver and interrupt handler
char *rxbuf, *txbuf;
int  rxcount, txcount, rxdone, txdone;
int do_command(int cmd, int arg, int resp);
int sdc_handler();
int sdc_init();
int getblock(int blk, char *buf);
int putblock(int blk, char *buf);


/* string.c */
// int kprintf(char *, ...);// something is going on w this
// functions in sting.c
int strlen(char *s);
int strcmp(char *s1, char *s2);
int strcpy(char *dest, char *src);
int kstrcpy(char *dest, char *src);
int kstrcat(char *dest, char *src);
int atoi(char *s);
int geti();
int memcpy(char *dest, char *src, int size);

/* sdc.c  */
int svc_handler(volatile int a, int b, int c, int d);

/* timer.c */
// int kprintf(char *fmt, ...);
int kpchar(char, int, int);
int unkpchar(char, int, int);
void timer_init();
void timer_handler(int n);
void timer_start(int n);
int timer_clearInterrupt(int n);
void timer_stop(int n);

/* uart.c */
#define UDR  0x00
#define UDS  0x04
#define UFR  0x18
#define CNTL 0x2C
#define IMSC 0x38
#define UMIS 0x40 
#define SBUFSIZE 128

typedef volatile struct uart{
  char *base;     // base address; as char *
  u32 n;          // uart number 0-3

  char inbuf[SBUFSIZE];
  int indata, inroom, inhead, intail;
  char outbuf[SBUFSIZE];
  int outdata, outroom, outhead, outtail;
  int txon; // 1=TX interrupt is on
}UART;

UART uart[4];    

int uart_init();

void uart_handler(UART *up) ;

int do_rx(UART *up);

int do_tx(UART *up);
       
int ugetc(UART *up);


// TO DO: UART outputs should be intertupt-driven also 
int uputc(UART *up, char c);
int ugets(UART *up, char *s);
int uprints(UART *up, char *s);
int urpx(UART *up, int x);
int uprintx(UART *up, int x);
int urpu(UART *up, int x);
int uprintu(UART *up, int x);
int uprinti(UART *up, int x);
int ufprintf(UART *up, char *fmt,...);
int uprintf(char *fmt, ...);

/* vid.c */ 
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

/* wait.c */ 
int ksleep(int event);

int kwakeup(int event);

int kexit(int value);

int kwait(int *status);


#endif