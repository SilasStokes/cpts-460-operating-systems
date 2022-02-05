/**************** t.c file **************/
int N;
int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sum;

#include "string.c"
#include "uart.c"
// char *tab = "0123456789ABCDEF";
int BASE = 10;
int urpu(UART *up, unsigned int x)
{
    char c;
    if (x)
    {
        c = CHARACTER_TABLE[x % BASE];
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
void uprintf(UART * up, char *fmt, ...) {
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


int main()
{
    int i;
    char string[64];
    UART *up;

    N = 10;

    uart_init();
    up = &uart[0];

    uprints(up, "Enter lines from UART terminal, enter end to exit\n\r");
    uprintf(up, "cha=%c string=%s      dec=%d hex=%x oct=%o neg=%d\n",
	          'A', "this is a test", 100,    100,   100,  -100);
    while (1)
    {
        ugets(up, string);
        uprints(up, "    ");
        uprints(up, string);
        uprints(up, "\n\r");

        if (strcmp(string, "end") == 0)
            break;
    }
    uprints(up, "Compute sum of array\n\r");
    sum = 0;
    for (i = 0; i < N; i++)
        sum += v[i];
    uprints(up, "sum = ");
    uputc(up, (sum / 10) + '0');
    uputc(up, (sum % 10) + '0');
    uprints(up, "\n\r");

    uprints(up, "END OF UART DEMO\n\r");
}
