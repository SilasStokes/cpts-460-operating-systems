
//#include "defines.h"
#include "uart.c"

int color;

extern char _binary_wsu_bmp_start;
UART *up;

#include "vid.c"

// int urpu(UART *up, unsigned int x);
// int uprintu(UART *up, unsigned int x);
// int uprintd(UART *up, int x);
// int uprinto(UART * up, int x); 
// int uprintx(UART * up, int x);
// void ufprintf(UART * up, char *fmt, ...);



int main()
{
   char c, *bit_map_ptr;
   int mode;

   uart_init();
   up = &uart[0];

   fbuf_init();

   bit_map_ptr = &_binary_wsu_bmp_start;
   show_bmp(bit_map_ptr, 0, 0); 

   while(1);   // loop here  
}


