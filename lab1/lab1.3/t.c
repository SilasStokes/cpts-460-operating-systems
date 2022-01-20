/*******************************************************
 *                      t.c file                        *
 *******************************************************/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define TRK 18
#define CYL 36
#define BLK 1024
//#define BLOCK_OFFSET(block) (BLK + (block - 1)*blocksize)

#include "ext2.h"
typedef struct ext2_group_desc GD;
typedef struct ext2_inode INODE;
typedef struct ext2_dir_entry_2 DIR;
GD *gp;
INODE *ip;
DIR *dp;

char buf1[BLK], buf2[BLK], temp[32];
int color = 0x0A;
u8 ino;

 char *ctable = "0123456789ABCDEF";
 int  BASE = 10; 

int prints(char *s)
{
    while (*s)
    {
        putc(*s);
        if (*s == '\n')
        {
            putc('\r');
        }
        s++;
    }
}

// int gets(char *s)
// {
//     char c;
//     while ((c = getc()) != '\r')
//     {
//         *s = c;
//         putc(c);
//         s++;
//     }
//     *s = 0; // null terminate
// }

int getblk(u16 blk, char *buf)
{
    // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
    readfd(blk / 18, ((blk) % 18) / 9, (((blk) % 18) % 9) << 1, buf);
}

// prints_len(char *s, u8 len) {
//     int i = 0;
//     for ( ; i < len; i++) {
//         putc(*s);
//         s++;
//     }
// }

// u8 print_int(u32 num) {
//     u32 div, mod;
//     if (num < 10){
//         putc(num + '0');
//         return 0;
//     } else {
//         mod = num % 10;
//         div = num / 10;
//         print_int((u32)div);
//         putc(mod + '0');
//     }
// }


u16 search(INODE * ip, char *name) {
    // char temp[64];
    getblk((u16) ip -> i_block[0], buf2);
    dp = (DIR * ) buf2;
    while ((char *) dp < buf2 + BLK) {
        strcpy(temp, dp-> name, dp ->name_len);
        temp[dp -> name_len] = 0;
        prints(temp);
        prints(" ");
        if (strcmp(temp, name) == 0) {
            
            prints("found inode: ");
            // putc(dp -> inode + '0');
            prints("\n\r");
            return (u16)dp -> inode;
        }
        dp = (DIR *) ( (char *) dp + dp->rec_len);
        // getc();

    }
    // prints("didn't find inode \n\r");    
    // return (u16)0;
}

main()
{
    u16 i, j,iblk; 
    u16 ino, block, offset;
    u32 *indirect_block;
    // char c;

    // prints("read block# 2 (GD)\n\r");
    getblk((u16)2, buf1);
    gp = (GD *)buf1;
    iblk = gp->bg_inode_table;// this an offset
    // prints("Got iblk value\n\r");

    // 1. WRITE YOUR CODE to get iblk = bg_inode_table block number
    // prints("inode_block=");
    // putc(iblk + '0');
    // prints("\n\r");

    // 2. WRITE YOUR CODE to get root inode
    // prints("read inodes begin block to get root inode\n\r");
    getblk((u16)iblk, buf1);

    // iblk = ( 2 - 1) / 8 + iblk;
    ip = (INODE *) buf1 + 1;
    // 3. WRITE YOUR CODE to step through the data block of root inode
    // prints("read data block of root DIR\n\r");
    
    // prints("block # = "); putc(ip -> i_block[0] + '0'); prints("\n\r");

    ino = search(ip, "boot");
    // i = iblk % 10; // num is 21, so this give us 1. 
    // j = iblk / 10; // num is 21, so this give us 2.
    // prints("block # = "); putc(j + '0');putc(i + '0'); prints("\n\r");

    // use mailmans algorithm to get inode from ino
    block = (ino - 1 ) / 8 + iblk;
    offset = (ino - 1) % 8;
    getblk((u16)block, buf1);
    // now we're at boot inode
    ip = (INODE *) buf1 + offset;
    ino = search(ip, "mtx");

    block = (ino - 1 ) / 8 + iblk;
    offset = (ino - 1) % 8;
    getblk((u16)block, buf1);
    ip = (INODE *) buf1 + offset; // now ip points at mtx inode

    
    getblk((u16) ip -> i_block[12], buf2);
    
    setes(0x1000);
    // now need to adjust setes
    for( i = 0; i < 12; i++) {
        getblk((u16) ip -> i_block[i], 0);
        putc('*');
        inces();
    }
    // prints("done with direct blocks \n\r");



    indirect_block = (u32 *) buf2;
    // j = 0;

    while (*indirect_block != 0) {
        getblk((u16) *indirect_block, 0);
        putc(' ');
        putc('-');
        inces();
        indirect_block ++;
        j++;
    }
    // putc(j + '0');
    // i = j % 10; // num is 21, so this give us 1. 
    // j = j / 10; // num is 21, so this give us 2.
    // prints("num indirect blocks # = "); putc(j + '0');putc(i + '0'); prints("\n\r");

                                                             

    // iblk =  (u16)ip -> i_block[i];
    // getblk((u16) ip -> i_block[0], buf1);
    // dp = (DIR * ) buf1;
    // while ((char *) dp < buf2 + BLK) {
    //     strcpy(temp, dp-> name, dp ->name_len);
    //     temp[dp -> name_len] = 0;
    //     prints(temp);
    //     prints(" ");
    //     if (strcmp(temp, "boot") == 0) {
    //         prints("found boot \n\r");
    //         //puts("found boot, inode num: "); print_int( ((u32)dp -> inode)); prints("\n\r");
    //         // lo = dp ->inode % 10; 
    //         // hi = dp ->inode / 10;
    //         // prints("block # = "); putc(hi + '0');putc(lo + '0'); prints("\n\r");
    //     }
    //     dp = (DIR *) ( (char *) dp + dp->rec_len);
    //     getc();

    // }
    // prints("\n\r");

    getc();
    
    // 4. print file names in the root directory /
    return 1;
}
/*
example:
if num 123
we mod by 10 to get 3
we divide by 10 to get 12
mod by 10 to get 2
div by 10 to get 1
mod by 10 to get 0

*/

