#ifndef UART_H
#define UART_H

#include "type.h"
#include "functions.h"

// int kprintf(char *fmt, ...);

/******** bytes offsets: for char *base ********/
// #define UDR  0x00
// #define UDS  0x04
// #define UFR  0x18
// #define CNTL 0x2C
// #define IMSC 0x38
// #define UMIS 0x40 
// #define SBUFSIZE 128

// typedef volatile struct uart{
//   char *base;     // base address; as char *
//   u32 n;          // uart number 0-3

//   char inbuf[SBUFSIZE];
//   int indata, inroom, inhead, intail;
//   char outbuf[SBUFSIZE];
//   int outdata, outroom, outhead, outtail;
//   int txon; // 1=TX interrupt is on
// }UART;

// UART uart[4];     
// 4 UArt structures

// int uart_init();

// void uart_handler(UART *up) ;

// int do_rx(UART *up);

// int do_tx(UART *up);
       
// int ugetc(UART *up);


// // TO DO: UART outputs should be intertupt-driven also 
// int uputc(UART *up, char c);

// int ugets(UART *up, char *s);

// int uprints(UART *up, char *s);

// int urpx(UART *up, int x);

// int uprintx(UART *up, int x);

// int urpu(UART *up, int x);

// int uprintu(UART *up, int x);

// int uprinti(UART *up, int x);

// int ufprintf(UART *up, char *fmt,...);

// int uprintf(char *fmt, ...);



#endif