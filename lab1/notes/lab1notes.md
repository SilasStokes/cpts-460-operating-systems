

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

