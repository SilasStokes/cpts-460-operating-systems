Name: Silas Stokes
Email: silas.stokes@wsu.edu
SID: 11655726


===========================================================================
                 CS460 LAB1 Check List

1. Does it boot up the MTX OS?
    A: Yes!

============================================================================

                     CS460 LAB#1 QUESTIONS

    Text edit your answers as a .txt file. Submit it to TA before demo time.

1. On Intel x86 based PCs, during booting, what does BIOS do?
        A:  The BIOS stands for 'basic input/output system'. It's a small program
            (1024 bytes or less), that is meant to prepare the system to read 
            the kernal located in /boot/mtx. 

   How many sectors does BIOS load from the boot device?
        A:  Each sector is 512 bytes, two sectors per BLOCK (1024 bytes). 
            The booter loads 12 direct blocks, 32 indirect blocks
            (32 + 12) * 2 = 56 sectors.

   Where in memory does BIOS load the booter?________________________________
        A:  The booter is runs at address 0x7C00.

2. BIOS loads only 512 bytes of a booter into memory, which is only the 
   beginning part of the booter. How does the booter load the remaining part of 
   the booter into memory?
        A:  The first thing the booter does is move to a safe address, above the
            modifiable memory. Memory 0x9000.

3. Assume a COMPLETE booter is loaded at the segment 0x9000. WHY do we have to
   set the CPU's sgement registers CS,DS,SS,ES to 0x9000?
        A:  Because they will be executing the code there. 

4. How do you find the file /boot/mtx?
        A:  

5. How to load the (disk) blocks of /boot/mtx to the segment 0x1000?__________
        A:  
