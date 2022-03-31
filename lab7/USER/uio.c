/************ uio.c file: must implement printf() in U space **********/
#include "functions.h"
#define printf uprintf
char *tab = "0123456789ABCDEF";

int uputc(char);
// TO DO: UART outputs should be intertupt-driven also
// int uputc(char c)
// {
//   //kprintf("uputc to UART%d %c ", up->n, c);
//   if (up->txon){ // if TX is on => still transmitting, enter c into outbuf[]
//     up->outbuf[up->outhead++] = c;
//     up->outhead %= 128;
//     int_off();
//      up->outdata++; up->outroom--;
//     int_on();
//     return 0;
//   }

//   // txon==0 means TX is off => output c & enable TX interrupt
//   // PL011 TX is riggered only if write char, else no TX interrupt
//   int i = *(up->base+UFR);         // read FR
//   while( *(up->base+UFR) & 0x20 ); // loop while FR=TXF
//   *(up->base+UDR) = (int)c;        // write c to DR
//   // UART0_IMSC |= 0x30; // 0000 0000: bit5=TX mask bit4=RX mask
//   *(up->base+IMSC) |= 0x30;
//   up->txon = 1;
// }

int ugetline(char *line)
{
    char c, *cp = line;
    while ((c = ugetc()) != '\r')
    {
        //uputc('u'); uputc(c);
        *cp = c;
        cp++;
    }
    *cp = 0;
}

int uprints(char *s)
{
    while (*s)
    {
        uputc(*s);
        s++;
    }
}

int urpx(u32 x)
{
    char c;
    if (x == 0)
        return 0;
    c = tab[x % 16];
    urpx(x / 16);
    uputc(c);
    return 0;
}

int uprintx(u32 x)
{
    uputc('0');
    uputc('x');
    if (x == 0)
        uputc('0');
    else
        urpx(x);
    uputc(' ');
    return 0;
}

int urpu(u32 x)
{
    char c;
    if (x == 0)
        return 0;
    c = tab[x % 10];
    urpu(x / 10);
    uputc(c);
    return 0;
}

int uprintu(u32 x)
{
    if (x == 0)
    {
        uputc('0');
    }
    else
        urpu(x);
    uputc(' ');
    return 0;
}

int uprinti(int x)
{
    if (x < 0)
    {
        uputc(' ');
        uputc('-');
        x = -x;
    }
    uprintu((u32)x);
}

int uprintf(char *fmt, ...)
{
    int *ip;
    char *cp;
    cp = fmt;
    ip = (int *)&fmt + 1;

    while (*cp)
    {
        if (*cp != '%')
        {
            uputc(*cp);
            if (*cp == '\n')
                uputc('\r');
            cp++;
            continue;
        }
        cp++;
        switch (*cp)
        {
        case 'c':
            uputc((char)*ip);
            break;
        case 's':
            uprints((char *)*ip);
            break;
        case 'd':
            uprinti(*ip);
            break;
        case 'u':
            uprintu((u32)*ip);
            break;
        case 'x':
            uprintx((u32)*ip);
            break;
        }
        cp++;
        ip++;
    }
    return 0;
}
