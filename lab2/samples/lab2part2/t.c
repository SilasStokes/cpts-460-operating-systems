
//#include "defines.h"
#include "uart.c"
#include "vid.c"

int color;
char *tab = "0123456789ABCDEF";

extern char _binary_wsu_bmp_start;

int color;
UART *up;

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
