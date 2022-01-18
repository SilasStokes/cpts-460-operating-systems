/*******************************************************
 *                      t.c file                        *
 *******************************************************/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc GD;
typedef struct ext2_inode INODE;
typedef struct ext2_dir_entry_2 DIR;
GD *gp;
INODE *ip;
DIR *dp;
char * cp;

char buf1[BLK], buf2[BLK];
int color = 0x0A;
u8 ino;

//** function defintions
int getblk(u16 blk, char *buf);
int gets(char *s);

prints_len(char *s, u8 len) {
    int i = 0;
    for ( ; i < len; i++) {
        putc(*s);
        s++;
    }
}

int gets(char *s)
{
    char c;
    while ((c = getc()) != '\r')
    {
        *s = c;
        putc(c);
        s++;
    }
    *s = 0; // null terminate
}

char *ctable = "0123456789ABCDEF";
int  BASE = 10; 

int rpu(u32 x)
{  
    char c;
    if (x){
       c = ctable[x % BASE];
       rpu(x / BASE);
       putc(c);
    }
}

int printu(u32 x)
{
    if (x == 0 ) 
        putc('0');
    else
        rpu (x);
   //(x==0) ? putc('0') : rpu(x);
}

int printd(int x)
{
    if (x < 0){
        putc('-');
        printu( (~x) + 1 );
    } else 
        printu( x );

}

int printx(u32 x)
{
    BASE = 16;
    putc('0');
    putc('x');
    rpu(x);
    BASE = 10;
}
int printo(u32 x){
    BASE = 8;
    putc('0');
    rpu(x);
    BASE = 10;
}
int prints(char *s){
    while (*s) {
        putc(*s);
        if (*s == '\n'){
            putc('\r');
        }
        s++;
    }
}

/*
    char                      by %c
    string                    by %s
    unsigned integer          by %u
    integer                   by %d
    unsigned integer in OCT   by %o
    unsigned integer in HEX   by %x
*/
void myprintf(char *fmt, ...){
    int *ip = (int *) (&fmt + 1);
    char *cp = fmt;
    while (*cp) {
        if(*cp == '%'){
            cp++;
            switch (*cp){
                case 'c' : putc(*ip); break;
                case 's' : prints((char *) (*ip) ); break;
                case 'u' : printu(*ip); break;
                case 'd' : printd(*ip); break;
                case 'o' : printo(*ip); break;
                case 'x' : printx(*ip); break;
                default: break;
            }
            ip++;
        } else {
            putc(*cp);
            if (*cp == '\n')
                putc('\r');
        }
        cp++;
    }
}

main()
{
    u16 i, iblk;
    char c, temp[64];

    prints("read block# 2 (GD)\n\r");
    getblk(2, buf1);
    gp = (GD *)buf1;
    iblk = gp->bg_inode_table;// this an offset
    prints("Got iblk value\n\r");

    // 1. WRITE YOUR CODE to get iblk = bg_inode_table block number
    prints("inode_block=");
    putc(iblk + '0');
    prints("\n\r");

    // 2. WRITE YOUR CODE to get root inode
    prints("read inodes begin block to get root inode\n\r");
    getblk(iblk, buf1);
    // add code for iget here basically


    // iblk = ( 2 - 1) / 8 + iblk;

    ip = (INODE *) buf1 + ( 2 - 1 ) % 8; // basically just add 1 for root. 

    // 3. WRITE YOUR CODE to step through the data block of root inode
    prints("read data block of root DIR\n\r");
    //prints("first block # = ");
    //putc(ip -> i_block[0] + '0');

    //prints("\n\r");

    
    for (i = 0; ip -> i_block[i]!= 0; i++) {
        prints("block # = ");
        putc(ip -> i_block[i] + '0');
        prints("\n\r");

        // getblk( ip -> i_block[i], buf2);
        //dp = (DIR * ) buf2;
        // while ((char *) dp < buf2 + BLK) {

        //     prints_len(dp ->name, dp ->name_len);
        //     dp = (DIR *) ( (char *) dp + dp->rec_len);
        //     getc();

        // }


        getc();
    }
    
    // 4. print file names in the root directory /
}

int getblk(u16 blk, char *buf)
{
    // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
    readfd(blk / 18, ((blk) % 18) / 9, (((blk) % 18) % 9) << 1, buf);
}
