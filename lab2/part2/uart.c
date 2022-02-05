/**************** uart.c file ****************/
#define DATA_RGSTR      0x00
#define FLAG_RGSTR      0x18

// this is for the flag register
#define RX_BUF_EMPTY     0x10    //  0001 0000
#define TX_BUF_FULL      0x20    //  0010 0000
char *CHARACTER_TABLE = "0123456789ABCDEF";
int BASE = 10;




typedef struct uart
{
    char *base;
    int n;
} UART;

UART uart[4];

int uart_init()
{
    int i;
    UART *up;

    for (i = 0; i < 4; i++)
    {
        up = &uart[i];
        up->base = (char *)(0x101F1000 + i * 0x1000);
        up->n = i;
    }
    uart[3].base = (char *)(0x10009000); // uart3 at 0x10009000
}

int ugetc(UART *up)
{
    while (*(up->base + FLAG_RGSTR) & RX_BUF_EMPTY);
    return *(up->base + DATA_RGSTR);
}

int uputc(UART *up, char c)
{
    while (*(up->base + FLAG_RGSTR) & TX_BUF_FULL)  ;
    *(up->base + DATA_RGSTR) = c;
}

int ugets(UART *up, char *s)
{
    while ((*s = (char)ugetc(up)) != '\r')
    {
        uputc(up, *s);
        s++;
    }
    *s = 0;
}

int uprints(UART *up, char *s)
{
    while (*s)
        uputc(up, *s++);
}

/** WRITE YOUR uprintf(UART *up, char *fmt, . . .) for formatted print **/

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


