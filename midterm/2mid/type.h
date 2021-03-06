
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;



#define UART0_BASE_ADDR 0x101f1000
#define UART0_DR (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define UART0_FR (*((volatile u32 *)(UART0_BASE_ADDR + 0x018)))
#define UART0_IMSC (*((volatile u32 *)(UART0_BASE_ADDR + 0x038)))

#define UART1_BASE_ADDR 0x101f2000
#define UART1_DR (*((volatile u32 *)(UART1_BASE_ADDR + 0x000)))
#define UART1_FR (*((volatile u32 *)(UART1_BASE_ADDR + 0x018)))
#define UART1_IMSC (*((volatile u32 *)(UART1_BASE_ADDR + 0x038)))

#define KBD_BASE_ADDR 0x10006000
#define KBD_CR (*((volatile u32 *)(KBD_BASE_ADDR + 0x000)))
#define KBD_DR (*((volatile u32 *)(KBD_BASE_ADDR + 0x008)))


#define TIMER0_BASE_ADDR 0x101E2000
#define TIMER0_LR (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define TIMER0_BR (*((volatile u32 *)(UART0_BASE_ADDR + 0x032)))







// char *VIC_BASE = (char *) 0x10140000;
// #define VIC_STATUS    0x00
// #define VIC_INTENABLE 0x10
// #define VIC_VADDR     0x30


#define VIC_BASE_ADDR 0x10140000
#define VIC_STATUS (*((volatile u32 *)(VIC_BASE_ADDR + 0x000)))
#define VIC_INTENABLE (*((volatile u32 *)(VIC_BASE_ADDR + 0x010)))
#define VIC_VADDR (*((volatile u32 *)(VIC_BASE_ADDR + 0x030)))

#define SIC_BASE_ADDR 0x10003000
#define SIC_STATUS (*((volatile u32 *)(SIC_BASE_ADDR + 0x000)))
#define SIC_INTENABLE (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_ENSET (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_PICENSET (*((volatile u32 *)(SIC_BASE_ADDR + 0x020)))
// char *SIC_BASE = (char *)0x10003000;
// #define SIC_STATUS    0x00
// #define SIC_INTENABLE 0x08
// // #define SIC_ENSET     0x08
// #define SIC_ENSET (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
// #define SIC_PICENSET  0x20



void timer_handler();

#define BLUE 0
#define GREEN 1
#define RED 2
#define CYAN 3
#define YELLOW 4
#define PURPLE 5
#define WHITE 6

#define NPROC 9    // number of PROCs
#define SSIZE 1024 // stack size = 4KB

// PROC status
#define FREE 0
#define READY 1
#define SLEEP 2
#define ZOMBIE 3
#define BLOCK 4

typedef struct proc
{
    struct proc *next; // next proc pointer
    int *ksp;          // saved sp: at byte offset 4

    int pid;      // process ID
    int ppid;     // parent process pid
    int status;   // PROC status=FREE|READY, etc.
    int priority; // scheduling priority

    int event;    // event value to sleep on
    int exitCode; // exit value

    struct proc *child;   // first child PROC pointer
    struct proc *sibling; // sibling PROC pointer
    struct proc *parent;  // parent PROC pointer

    int kstack[1024]; // process stack
} PROC;

typedef struct tq
{
    struct tq *next;
    int time;
    PROC *proc;
    int (*action)(); // 0 = WAKEUP, 1 = NOTIFY, else = entry eaddr of handler
} TQE;