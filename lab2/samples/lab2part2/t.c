
//#include "defines.h"
#include "uart.c"
#include "vid.c"

int color;
char *tab = "0123456789ABCDEF";

extern char _binary_wsu_bmp_start;
UART *up;

int BASE = 10;
// int urpu(UART *up, unsigned int x);
// int uprintu(UART *up, unsigned int x);
// int uprintd(UART *up, int x);
// int uprinto(UART * up, int x); 
// int uprintx(UART * up, int x);
// void ufprintf(UART * up, char *fmt, ...);



int main()
{
   char c, *p;
   int mode;

   uart_init();
   up = &uart[0];

   fbuf_init();

   p = &_binary_wsu_bmp_start;
   show_bmp(p, 0, 0); 

   while(1);   // loop here  
}

/*
int urpu(UART *up, unsigned int x)
{
    char c;
    if (x)
    {
        c = tab[x % BASE];
        urpu(up, x / BASE);
        uputc(up, c);
    }
}

int uprintu(UART *up, unsigned int x)
{
    BASE = 10;
    if (x == 0)
        uputc(up, '0');
    else
        urpu(up, x);
    uputc(up, ' ');
}

int uprintd(UART *up, int x)
{
    BASE = 10;
    if (x < 0){
        uputc(up, '-');
        uprintu(up, (~x) + 1 );
    } else
        uprintu(up, x );

}

int uprinto(UART * up, int x){
    BASE = 8;
    uputc(up, '0');
    urpu(up, x);
    BASE = 10;
}
int uprintx(UART * up, int x)
{
    BASE = 16;
    uputc(up, '0');
    uputc(up, 'x');
    urpu(up, x);
    BASE = 10;
}
// char, string, unsigned int, int in DEC or HEX  to a UART port
void ufprintf(UART * up, char *fmt, ...) {
    int *ip = (int *) (&fmt + 1);
    char *cp = fmt;
    while (*cp) {
        if(*cp == '%'){
            cp++;
            switch (*cp){
                case 'c' : uputc(up, *ip); break;
                case 's' : uprints(up, (char *) (*ip) ); break;
                case 'u' : uprintu(up, *ip); break;
                case 'd' : uprintd(up, *ip); break;
                case 'o' : uprinto(up, *ip); break;
                case 'x' : uprintx(up, *ip); break;
                default: break;
            }
            ip++;
        } else {
            uputc(up, *cp);
            if (*cp == '\n')
                uputc(up, '\r');
        }
        cp++;
    }
}

*/