// #include "../type.h"
#include "user.h"

/***********************************************************************
                      io.c file of MTX
***********************************************************************/
// char space = ' ';
// char *ctable = "0123456789ABCDEF";
// char cr = '\r';



// #define printk printf

// int printf(char *fmt, ...);

// typedef struct ext2_dir_entry_2
// {
//     u32 inode;   /* Inode number */
//     u16 rec_len; /* Directory entry length */
//     u8 name_len; /* Name length */
//     u8 file_type;
//     char name[255]; /* File name */
// } DIR;

// typedef struct stat
// {
//     u16 st_dev;   /* major/minor device number */
//     u16 st_ino;   /* i-node number */
//     u16 st_mode;  /* file mode, protection bits, etc. */
//     u16 st_nlink; /* # links; TEMPORARY HACK: should be nlink_t*/
//     u16 st_uid;   /* uid of the file's owner */
//     u16 st_gid;   /* gid; TEMPORARY HACK: should be gid_t */
//     u16 st_rdev;
//     long st_size;  /* file size */
//     long st_atime; /* time of last access */
//     long st_mtime; // time of last modification
//     long st_ctime; // time of creation
//     long st_dtime;
//     long st_date;
//     long st_time;
// } STAT;

// // UNIX <fcntl.h> constants: <asm/fcntl.h> in Linux
// #define O_RDONLY 00
// #define O_WRONLY 01
// #define O_RDWR 02
// #define O_CREAT 0100  /* not fcntl */
// #define O_TRUNC 01000 /* not fcntl */
// #define O_APPEND 02000

// #define EOF -1

// #define exit mexit
/*
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR   2
*/
int puts(const char *s)
{
    char line[128];
    strcpy(line, s);
    strcat(line, "\n\r");
    write(1, line, strlen(line));
}


int putc_nonewline(char c)
{
    write(1, &c, 1);
    return 0;
}

int puts_nonewline(char *s){
    while (*s) {
        putc_nonewline(*s);
        s++;
    }
}

int kc_putc(char c)
{
    write(1, &c, 1);
    if (c == '\n')
        kc_putc('\r');
    return 0;
}

void prints(char *s)
{
    while (*s)
    {
        kc_putc(*s);
        s++;
    }
}

void mputs(char *s)
{
    prints(s);
}

// extern int strlen(const char *);
void print2f(char *s)
{
    write(2, s, (int)strlen(s));
}

void rpi(int x)
{
    char c;
    if (x == 0)
        return;
    c = ctable[x % 10];
    rpi((int)x / 10);
    kc_putc(c);
}

void printi(int x)
{
    if (x == 0)
    {
        prints("0 ");
        return;
    }
    if (x < 0)
    {
        kc_putc('-');
        x = -x;
    }
    rpi((int)x);
    kc_putc(space);
}

void rpu(u32 x)
{
    char c;
    if (x == 0)
        return;
    c = ctable[x % 10];
    rpi((u32)x / 10);
    kc_putc(c);
}

void printu(u32 x)
{
    if (x == 0)
    {
        prints("0 ");
        return;
    }
    rpu((u32)x);
    kc_putc(space);
}

void rpx(u32 x)
{
    char c;
    if (x == 0)
        return;
    c = ctable[x % 16];
    rpx((u32)x / 16);
    kc_putc(c);
}

void printx(u32 x)
{
    prints("0x");
    if (x == 0)
    {
        prints("0 ");
        return;
    }
    rpx((u32)x);
    kc_putc(space);
}

void printc(char c)
{
    kc_putc(c);
    c = c & 0x7F;
    if (c == '\n')
        kc_putc(cr);
}

int printf(char *fmt, ...)
{
    char *cp, *cq;
    int *ip;

    cq = cp = (char *)fmt;
    ip = (int *)&fmt + 1;

    while (*cp)
    {
        if (*cp != '%')
        {
            printc(*cp);
            cp++;
            continue;
        }
        cp++;
        switch (*cp)
        {
        case 'd':
            printi(*ip);
            break;
        case 'u':
            printu(*ip);
            break;
        case 'x':
            printx(*ip);
            break;
        case 's':
            prints((char *)*ip);
            break;
        case 'c':
            printc((char)*ip);
            break;
        }
        cp++;
        ip++;
    }
}
