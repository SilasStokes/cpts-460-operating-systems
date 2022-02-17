


sleep and wake up are in support of the wait operation

fork implements the binary tree. ps is the status of the processes

fork once:
    proc 1 is running with ppid - , child is 2 and is ready. 
switch:
    proc 2 running, ppid = 1, child = NULL

fork again:
    proc 2 with a child of 3

fork again
    proc 2 with a child of 3 ready -> 4 ready -> null

exit:
    asks for an exit value. he entered 2. children should have been given to parent process P1. 

    now text is green bc we're back at parent (P1) process. 

    P1 has the children process 2 zombie -> 3 ready -> 4 ready -> NULL

now he does wait:
    found zomie child 2, shows the exit code of 2. put p2 back in free list. remove from the child list of P1. 

What if P1 waits again?
    P1 will sleep on it's own process. It searches for zombie process, doesn't find one so goes to sleep. 
    So it switches to P3. The sleep event is the address of P1 so 82696. 

What if he calls wait on P3. 
    fails bc there's no children. 

Exit P3, asks for a value, he puts 2:
    Since P3 is mae a zombie, it wakes P1 up, the process switched to P4

he calls switch to get bcak to P1
    as soon as he switches, P1 found the P3 zombie node, it completes the wait function and then 
    returns back to normal operation. P3 ot put itthe freeList. 


this process relationship is exactly (apparently) the process system that Unix uses. 

-----------------------------------------------------------------------------------------

# Mid2

The timer is running top right. 

entered 5. The process switched from P1 to P2 (red)

the timer queue printed the timer printing [process #, seconds #] -> NULL

for two entires:
    timer queue should show the relative time after the subsequent process so 
    timerqueue = [process #, seconds # (this one is decrementing)] -> [process #, seconds (constant)]


-----------------------------------------------------------------------------------------
going over chapter 5, this is the itimer informaiton
unix uses the real time paradigm, 

virtual only runs when 



