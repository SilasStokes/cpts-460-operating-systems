// int tswitch();

// int ksleep(int event)
// {
//     printf("ksleep: under construction\n");
// }

// int kwakeup(int event)
// {
//     printf("kwakeup: under construction\n");
// }

// /**
//  * 1.   erase process user -mode context e.g close file descriptors,
//  *      release resources, deallocatre user-mode image memory etc..
//  *          - there's no user mode yet so start @ 2.
//  *
//  * 2.   dispose of child processes, if any
//  *
//  * 3.   record exitValue in PROC.exitCode for parent to get
//  *
//  * 4.   Become a ZOMBIE (but do not free the PROC)
//  *
//  * 5.   wakeup parent, and, if needed also the INIT process P!.
//  *
//  * 6.   switch process to give up CPU
//  */
// int kexit(int exitValue)
// {
//     printf("proc %d in kexit(), value=%d\n", running->pid, exitValue);
//     // 2. dispose of childre, if any



//     running->exitCode = exitValue;
//     running->status = ZOMBIE;
//     kwakeup(running->parent);
//     tswitch();
// }
