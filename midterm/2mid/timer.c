// timer.c file
/***** timer confiuguration values *****/
#define CTL_ENABLE (0x00000080)
#define CTL_MODE (0x00000040)
#define CTL_INTR (0x00000020)
#define CTL_PRESCALE_1 (0x00000008)
#define CTL_PRESCALE_2 (0x00000004)
#define CTL_CTRLEN (0x00000002)
#define CTL_ONESHOT (0x00000001)

// timer register offsets from base address
/**** byte offsets *******
#define TLOAD   0x00
#define TVALUE  0x04
#define TCNTL   0x08
#define TINTCLR 0x0C
#define TRIS    0x10
#define TMIS    0x14
#define TBGLOAD 0x18
*************************/
/** u32 * offsets *****/
#define TLOAD 0x0
#define TVALUE 0x1
#define TCNTL 0x2
#define TINTCLR 0x3
#define TRIS 0x4
#define TMIS 0x5
#define TBGLOAD 0x6



typedef volatile struct timer
{
    unsigned int *base;            // timer's base address; as u32 pointer
    int tick, hh, mm, ss; // per timer data area
    char clock[16];
} TIMER;

volatile TIMER timer[4]; // 4 timers; 2 timers per unit; at 0x00 and 0x20


// external symbols:
extern int color;
extern int kpchar(char, int, int);
extern int unkpchar(char, int, int);
extern int kputc(char);
extern int kputs(char *);
// extern 
// extern int strcpy(char *dest, char *src);
void erase_timer();

int k;

// functions:
void timer_start(int n) ;

int timer_clearInterrupt(int n);

void timer_stop(int n);

void timer_init()
{
    int i;
    TIMER *tp;
    kputs("timer_init()\n");

    for (i = 0; i < 4; i++)
    {
        tp = &timer[i];
        if (i == 0)
            tp->base = (unsigned int *)0x101E2000;
        if (i == 1)
            tp->base = (unsigned int *)0x101E2020;
        if (i == 2)
            tp->base = (unsigned int *)0x101E3000;
        if (i == 3)
            tp->base = (unsigned int *)0x101E3020;

        *(tp->base + TLOAD) = 0x0; // reset
        *(tp->base + TVALUE) = 0x0;
        *(tp->base + TRIS) = 0x0;
        *(tp->base + TMIS) = 0x0;
        *(tp->base + TCNTL) = 0x62; // 011-0000=|En|Pe|IntE|-|scal=00|32-bit|0=wrap|
        *(tp->base + TBGLOAD) = 0xE0000 / 60;

        tp->tick = tp->hh = tp->mm = tp->ss = 0;
        // strcpy((char *)tp->clock, "00:00:00");
        char *clock = "00:00:00";
        char *src = clock;
        char *dest = (char *)tp ->clock;
        while(*src){
                *dest++ = *src++;
            }
        *dest = 0;
    }
}

int printTimerQueue(char *name, TQE *p)
{
  kprintf("%s = ", name);
   while(p){
     kprintf("[%d %d]->", p->proc->pid, p->time);
     p = p->next;
  }
  kprintf("NULL\n"); 
}


void decr_timer_queue(){
    printf("decrementing timer queue\n");
    TQE *q =  timequeue;
    q -> time -= 1;

    if (q -> time == 0) {
        qdequeue(&timequeue);
       
        kwakeup( (int)q -> proc);

        // timequeue = 0;
        // dequeue
    } else {
        
        printTimerQueue("Time queue", q);
    }

    

}
void timer_handler(int n)
{
    int ris, mis, value, load, bload, i;
    TIMER *t = &timer[n];
    // read all status info
    ris = *(t->base + TRIS);
    mis = *(t->base + TMIS);
    value = *(t->base + TVALUE);
    load = *(t->base + TLOAD);
    bload = *(t->base + TBGLOAD);

    t->tick++;
    if (t -> tick == 60){
        t -> ss += 1;
        t -> tick = 0;
        t->ss %= 60;
        if (t->ss == 0)
        {
            t->mm++;
            if ((t->mm % 60) == 0)
            {
                t->mm = 0;
                t->hh++;
            }
        }
        if (timequeue != 0){
            decr_timer_queue();
        }

        // kputs("timer interrupt\n");
    }
    // t->ss = t->tick;
    
    for (i = 0; i < 8; i++)
    {
        unkpchar(t->clock[i], n, 70 + i);
    }
    t->clock[7] = '0' + (t->ss % 10);
    t->clock[6] = '0' + (t->ss / 10);
    t->clock[4] = '0' + (t->mm % 10);
    t->clock[3] = '0' + (t->mm / 10);
    t->clock[1] = '0' + (t->hh % 10);
    t->clock[0] = '0' + (t->hh / 10);

    // color = n + 1;
    for (i = 0; i < 8; i++)
    {
        kpchar(t->clock[i], n, 70 + i);
    }
    // if (t->tick == 60)
    // {   
    //     int sslo = t-> ss % 10; // num is 21, so this give us 1. 
    //     int sshi = t-> ss / 10; // num is 21, so this give us 2.
    //     int hhlo = t-> hh % 10; // num is 21, so this give us 1. 
    //     int hhhi = t-> hh / 10; // num is 21, so this give us 2.
    //     int mmlo = t-> mm % 10; // num is 21, so this give us 1. 
    //     int mmhi = t-> mm / 10; // num is 21, so this give us 2.
    //     erase_timer();
    //     // unkpchar( (u8)127, 0, 40);
    //     // unkpchar(sslo +'0', 0,40);
    //     // unkpchar(sslo + '0', 0, 41);
    //     t->tick = 0;
    //     t -> ss++;
    //     if (t -> ss == 60){
    //         t -> ss = 0;
    //     }
    //     //   kpchar('a', 0, 40);
    //     // undchar( '0', 0, 40);

    //     kpchar(hhhi + '0', 0, 40);
    //     kpchar(hhlo + '0', 0, 41);
    //     kpchar(':', 0,42);
    //     kpchar(mmhi + '0', 0, 43);
    //     kpchar(mmlo + '0', 0, 44);
    //     kpchar(':', 0,45);
    //     kpchar(sshi + '0', 0, 46);
    //     kpchar(sslo + '0', 0, 47);
    //     kputs("timer interrupt\n");
    // }

    timer_clearInterrupt(n);
}

void timer_start(int n) // timer_start(0), 1, etc.
{
    TIMER *tp = &timer[n];

    *(tp->base + TCNTL) |= 0x80; // set enable bit 7
}

int timer_clearInterrupt(int n) // timer_start(0), 1, etc.
{
    TIMER *tp = &timer[n];
    *(tp->base + TINTCLR) = 0xFFFFFFFF;
}

void timer_stop(int n) // timer_start(0), 1, etc.
{
    TIMER *tp = &timer[n];
    *(tp->base + TCNTL) &= 0x7F; // clear enable bit 7
}
