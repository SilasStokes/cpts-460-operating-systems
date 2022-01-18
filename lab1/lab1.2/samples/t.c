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

char buf1[BLK], buf2[BLK];
int color = 0x0A;
u8 ino;

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

int getblk(u16 blk, char *buf)
{
    // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
    readfd(blk / 18, ((blk) % 18) / 9, (((blk) % 18) % 9) << 1, buf);
}

prints_len(char *s, u8 len) {
    int i = 0;
    for ( ; i < len; i++) {
        putc(*s);
        s++;
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

    ip = (INODE *) buf1 + ( 2 - 1 ) % 8;

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
