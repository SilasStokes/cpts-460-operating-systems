

# things I found on th discord:
- cast (u16) every time you call getblk
- when calling getblk with i_block[i], I had to save i_block first and then call it with the saved variable.
- bcc is weird compiler, all values have to be delcared at the top of the functions.
- a.out must be less than 1024 bytes, rpu from lab1 360 add 260 bytes, too much. that's prob why kc took out the heads info from a.out
- Apparently getblk(ip->block[i], buf) wont work, you have to save it first, iblk = ip -> block[i] 
- the putc function can't handle integers so kc does putc(1 +'0'); to make it work, however this makes printing numbers weird. If you need to do a reference, here it is:

    for (j = 0; j < 100; j ++) {

        putc(j + '0');
        prints("\n\r");
        getc();
    }
- but root node is 21, which the prompt prints as E. so if i_block[0] = E, you're good. 
- recall that the root node is number 2, and that the inode table begins with inode 1. 
- bcc stands for "Bruce's C Compiler", linked here: https://gitlab.com/FreeDOS/devel/bcc
- For getting the mtx blocks - the 12th (indirect block buffer) must be gotten into buf2 BEFORE setes(0x1000) is called. 
- setes(0x1000) must be done before inces();
- The indirect blocks are 32 bits apart despite being a 16 bit address. 
- Use the mailmans algorithm to get block and offset which are needed to get the boot and mtx inodes. The mailman algorithm can be found in iget() of your cs360 project. 


# Things KC covers in lecture:
- the `mk` script links some basic c functions you can use with the line: /usr/lib/bcc/libc.a
    - libc.a has the following functions (can't find this list online):
        stcmp, strcpy, strlen


    // to print i_block[0] as a number, not a character.
    //      The thought process behind this is the KC's putc can print 0-9 just fine.
    //      so he's just breaking the number up into it's discrete integers. 
    // int lo = ip -> i_block[0] % 10; // num is 21, so this give us 1. 
    // int hi = ip -> i_block[0] / 10; // num is 21, so this give us 2.
    // prints("block # = "); putc(hi + '0');putc(lo + '0'); prints("\n\r");

- once you get the program to boot:
- QEMU:
    login: root
    pw:     12345

    In terminal:
    login:  kcw
    pw:     abcde
