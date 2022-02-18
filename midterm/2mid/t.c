#include "type.h"

int color;

#include "string.c"

//##########################################
// PROCESS Stuff
PROC proc[NPROC] = {0}; // NPROC PROCs

PROC *freeList;         // freeList of PROCs
PROC *readyQueue;       // priority queue of READY procs
PROC *running;          // current running proc pointer


// PROC *timeQueue;
TQE timearray[NPROC] = {0};
TQE * timequeue =0;


PROC *sleepList; // list of SLEEP procs
int procsize = sizeof(PROC);
char *status[] = {"FREE", "READY", "SLEEP", "ZOMBIE"};
#define printf kprintf
#define gets kgets

#include "kbd.c"
#include "vid.c"
#include "exceptions.c"

#include "queue.c"
#include "wait.c" // include wait.c file

#include "timer.c"

TIMER *tp[4];

int pstswitch(), do_sleep(), do_wakeup(), do_exit(), do_switch(), do_wait(), do_kfork();
int scheduler();
int ksleep(int event);

int kwakeup(int event);
int kexit(int exitValue);
int kwait(int *status);
int kfork();

// assembly functions:
extern int tswitch();
extern int int_off();
extern int int_on();
extern int reset_handler();
extern int irq_handler();
extern int lock();
extern int unlock();
// extern int vectors_start();

// Event Handler related functions
void copy_vectors(void);
void IRQ_handler();
// initialize the MT system; create P0 as initial running process
int init();

void menu();

int main()
{
    color = YELLOW;
    row = col = 0;
    fbuf_init();
    kbd_init();

    /* enable VIC to route SIC interrupts */
    // *(VIC_BASE + VIC_INTENABLE) |= (1 << 31); // SIC to VIC's IRQ31
    VIC_INTENABLE |= (1 << 31); 

    // enable VIC to route timer0,1 interrupts at line 4
    // *(VIC_BASE + VIC_INTENABLE) |= (1 << 4); // timer0,1 at bit4
    VIC_INTENABLE |= (1 << 4); // timer0,1 at bit4


    /* enable SIC to route KBD IRQ */
    SIC_ENSET |= (1 << 3); // KBD int=3 on SIC

    init();

    printQ(readyQueue);
    kfork(); // kfork P1 into readyQueue

    unlock();
  



    kputs("test timer driver by interrupts\n");
    timer_init();   // initialize timer driver
    timer_start(0); // start timer 0

    kputs("Enter while(1) loop\n");
    while (1)
    {
        if (readyQueue)
            tswitch();
    }
}

int kwait(int *status)
{
    PROC *p = (PROC *)status;
    if (p->child == 0)
    {
        return -1;
    }

    while (1)
    {
        PROC *child = p->child;

        while (child)
        {
            if (child->status == ZOMBIE)
            {
                int pid = child->pid;
                p->status = child->exitCode;
                child->status = FREE;
                // remove from tree?
                removeprocess(child);
                enqueue(&freeList, child);
                return pid;
            }

            child = child->sibling;
        }
        ksleep(running);
    }
}
int kwakeup(int event)
{
    // PROC *p = &p[0];
    int currentprogramstatusregister = int_off();

    int i = 0;
    for (i = 0; i < NPROC; i++)
    {
        if (proc[i].status == SLEEP && proc[i].event == event)
        {
            proc[i].status = READY;
            dequeue(&sleepList);
            enqueue(&readyQueue, &proc[i]);
            // enqueue(&proc[i]);
        }
    }

    int_on(currentprogramstatusregister);
    // printf("kwakeup: under construction\n");
}
/**
 * 1.   erase process user -mode context e.g close file descriptors,
 *      release resources, deallocatre user-mode image memory etc..
 *          - there's no user mode yet so start @ 2.
 *
 * 2.   dispose of child processes, if any
 *
 * 3.   record exitValue in PROC.exitCode for parent to get
 *
 * 4.   Become a ZOMBIE (but do not free the PROC)
 *
 * 5.   wakeup parent, and, if needed also the INIT process P!.
 *
 * 6.   switch process to give up CPU
 */
int kexit(int exitValue)
{
    printf("proc %d in kexit(), value=%d\n", running->pid, exitValue);
    // 2. dispose of childre, if any

    if (running->child != 0)
    {
        PROC *childptr = running->child;
        PROC *parentptr = running->parent;

        // append running children to the parent's children linked list
        PROC *parentsibptr = parentptr->child;
        while (parentsibptr->sibling != 0)
        {
            parentsibptr = parentsibptr->sibling;
        }
        parentptr->sibling = childptr;

        // change the running -> children's parent pointer to running -> parent
        while (childptr)
        {
            childptr->parent = parentptr;
            childptr->ppid = parentptr->pid;
            childptr = childptr->sibling;
        }
    }

    running->exitCode = exitValue;
    running->status = ZOMBIE;
    kwakeup((int)running->parent);
    tswitch();
}
int ksleep(int event)
{
    int SR = int_off();
    // record event value in running proc.event
    running->event = event;
    running->status = SLEEP;
    enqueue(&sleepList, running);
    tswitch();
    int_on(SR);
    // printf("ksleep: under construction\n");
}

/*********** scheduler *************/
int scheduler()
{

    printf("proc %d in scheduler()\n", running->pid);
    if (running->status == READY)
        enqueue(&readyQueue, running);
    printList("readyQueue", readyQueue);
    running = dequeue(&readyQueue);
    
    printf("next running = %d\n", running->pid);
    color = running->pid;
}



int body() // process body function
{
    int c;
    char cmd[64];
    color = running->pid;
    printf("proc %d starts from body()\n", running->pid);
    while (1)
    {
        printf("***************************************\n");
        printf("proc %d running: parent=%d\n", running->pid, running->ppid);
        printList("readyQueue", readyQueue);
        // printSleepList(sleepList);
        // menu();
        printf("P%d running. Enter a timer value : ", running -> pid);


        gets(cmd);
        int delay = atoi(cmd);
        TQE *q = &timearray[0];
        q -> time = delay;
        q -> proc = running;
        enqueue_timer(&timequeue, q);
        ksleep( (int) q -> proc);

        // 1. add to timer queue


        // if (strcmp(cmd, "ps") == 0)
        //     do_ps();
        // if (strcmp(cmd, "fork") == 0)
        //     do_kfork();
        // if (strcmp(cmd, "switch") == 0)
        //     do_switch();
        // if (strcmp(cmd, "exit") == 0)
        //     do_exit();
        // if (strcmp(cmd, "sleep") == 0)
        //     do_sleep();
        // if (strcmp(cmd, "wakeup") == 0)
        //     do_wakeup();
    }
}
int kfork() // kfork a child process to execute body() function
{
    int i;
    PROC *p = dequeue(&freeList);
    if (p == 0)
    {
        kprintf("kfork failed\n");
        return -1;
    }
    p->ppid = running->pid; // set ppid
    p->parent = running;    // set parent PROC pointer
    p->child = 0;
    p->sibling = 0;
    // p -> next = 0;

    p->status = READY;
    p->priority = 1;

    // inserting in family tree
    if (running->child == 0)
    {
        running->child = p;
    }
    else
    {
        PROC *sibptr = running->child;

        while (sibptr->sibling != 0)
            sibptr = sibptr->sibling;

        sibptr->sibling = p;
    }

    // set kstack to resume to body
    //  HIGH    -1  -2  -3  -4  -5 -6 -7 -8 -9 -10 -11 -12 -13 -14
    //        ------------------------------------------------------
    // kstack=| lr,r12,r11,r10,r9,r8,r7,r6,r5, r4, r3, r2, r1, r0
    //        -------------------------------------------------|----
    //	                                              proc.ksp
    for (i = 1; i < 15; i++)
        p->kstack[SSIZE - i] = 0; // zero out kstack

    p->kstack[SSIZE - 1] = (int)body;  // saved lr -> body()
    p->ksp = &(p->kstack[SSIZE - 14]); // saved ksp -> -14 entry in kstack

    enqueue(&readyQueue, p);
    return p->pid;
}


int do_ps()
{
    int i;
    PROC *p;
    printf("PID  PPID  status\n");
    printf("---  ----  ------\n");
    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        printf(" %d    %d    ", p->pid, p->ppid);
        if (p == running)
            printf("RUNNING\n");
        else
            printf("%s\n", status[p->status]);
    }

    printf("tree version:\n");
    p = &proc[0];
    printtree(p);
}
int do_kfork()
{
    int child = kfork();
    if (child < 0)
        printf("kfork failed\n");
    else
    {
        printf("proc %d kforked a child = %d\n", running->pid, child);
        printList("Changed readyQueue", readyQueue);
    }
    return child;
}
int do_switch()
{
    tswitch();
}

int do_exit()
{
    int exitCode;
    printf("enter an exitCode value : ");
    exitCode = geti();
    kexit(exitCode);
}

int do_wait()
{
    // int exitCode;
    // printf("enter an exitCode value : ");
    // exitCode = geti();
    // kexit(exitCode);
    kwait(0);
}
int do_sleep()
{
    int event;
    printf("enter an event value to sleep on : ");
    event = geti();
    ksleep(event);
}

int do_wakeup()
{
    int event;
    printf("enter an event value to wakeup with : ");
    event = geti();
    kwakeup(event);
}

// initialize the MT system; create P0 as initial running process
int init()
{
    int i;
    PROC *p;
    for (i = 0; i < NPROC; i++)
    { // initialize PROCs
        p = &proc[i];
        p->pid = i; // PID = 0 to NPROC-1
        p->status = FREE;
        p->priority = 0;

        p->child = 0;
        p->sibling = 0;
        p->parent = 0;
        p->next = 0;

        p->next = p + 1;
    }
    proc[NPROC - 1].next = 0;
    freeList = &proc[0]; // all PROCs in freeList
    readyQueue = 0;      // readyQueue = empty

    sleepList = 0; // sleepList = empty

    // create P0 as the initial running process
    p = running = dequeue(&freeList); // use proc[0]
    p->status = READY;
    p->priority = 0;
    p->ppid = 0; // P0 is its own parent


    
    TQE *q;
    for (i = 0; i < NPROC; i++)
    { // initialize PROCs
        q = &timearray[i];
        q -> next = 0;
        q -> proc = 0;
        q -> action = 0;
    }
    printList("freeList", freeList);
    printf("init complete: P0 running\n");
}

void menu()
{
    printf("***************************************\n");
    printf(" ps switch fork sleep wakeup exit wait \n");
    printf("***************************************\n");
}

void copy_vectors(void)
{
    extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;

    while (vectors_src < &vectors_end)
        *vectors_dst++ = *vectors_src++;
}

// void IRQ_handler()
// {
//     int vicstatus, sicstatus;
//     // read VIC SIV status registers to find out which interrupt
//     vicstatus = *(VIC_BASE + VIC_STATUS);
//     sicstatus = *(SIC_BASE + SIC_STATUS);

//     if (vicstatus & 0x0010)
//     { // timer0,1=bit4
//         timer_handler(0);
//     }
// }
void IRQ_handler()
{
    int vicstatus, sicstatus;

    // read VIC SIV status registers to find out which interrupt
    vicstatus = VIC_STATUS;
    sicstatus = SIC_STATUS;

    if (vicstatus & 0x0010)
    { // timer0,1=bit4
        timer_handler(0);
    }
    if (vicstatus & (1 << 31))
    { // SIC interrupts=bit_31=>KBD at bit 3
        if (sicstatus & (1 << 3))
        {
            kbd_handler();
        }
    }
}
