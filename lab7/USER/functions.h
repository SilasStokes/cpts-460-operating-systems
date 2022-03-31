#ifndef FUNCS
#define FUNCS
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

int main(int argc, char *argv[]);

// #include "string.h"
// #include "uio.c"
/* ucode.c */
int getpid();
int getppid();
int umenu();
int ups();
int uchname();
int ukfork();
int uswitch();
int wait(int *status);
int uwait();
int myexit(int value);
int uexit();
int ugetusp();
int fork();
int exec(char *line);
int ufork();
int uexec();
int ugetc();
int uputc(char c);
int token(char *line);
int main0(char *s);
int getPA();

/* string.h (?) */
int kprintf(char *, ...); //??
int strlen(char *s);
int strcmp(char *s1, char *s2);
int strcpy(char *dest, char *src);
int kstrcpy(char *dest, char *src);
int atoi(char *s);
int geti();

/* uio.c */
int uputc(char);
int ugetline(char *line);
int uprints(char *s);
int urpx(u32 x);
int uprintx(u32 x);
int urpu(u32 x);
int uprintu(u32 x);
int uprinti(int x);
int uprintf(char *fmt,...);

/* us.s */
extern int entryPoint();
extern int syscall();
extern int getmysp();
extern int getcsr();
extern int getmyaddress();
#endif