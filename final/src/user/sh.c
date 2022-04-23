#include "functions.h"

#include "string.c"
#include "uio.c"
#include "ucode.c"

int main(int argc, char *argv[])
{

    int pid, status;
    char *cmd;
    char line[64];
    // printf("inside sh\n");s
    // while(1);
    while (1)
    {
        printf("sh.c >> ");
        umenu();
        ugetline(line);
        if (strcmp(line, "") == 0){
            printf("No command was entered, try again\n");
            continue;
            // while(1);
        }
        uprintf("\n");
        cmd = line;
        printf("got command, line = %s, cmd = %s\n", line, cmd);
        // display exe commmands
        // prompt for user input i.e cmd a1 a2

        if(!strcmp(cmd, "exit")){
            uexit();
        }
        pid = fork();
        if (pid)
            pid = wait(&status);
        else
            exec(cmd);
    }
}

// #include "functions.h"

// #define BLK 1024

// char *name[16], components[64];
// int nk;
// int nowait;

// /*********************************************
//    Use a single sh.c to replace u1.c u2.c
//    keep ucode.c as a syscall interface
//    Re-write u1.c u2.c as one sh.c, which
//       show menu() ==> /bin dir contents
//       then ask for a command line, and then for(), exec()
// **********************************************/
// char buf[1024];
// int color = 0x00C;

// void menu()
// {
//     /*
//    printf("#################################################\n");
//    printf("# ls     cd     pwd    cat   cp      mv    ps   #\n");
//    printf("# mkdir  rmdir  creat  rm    chmod   more  grep #\n");
//    printf("# lpr    (I/O and Pipe) :  >   >>    <     |    #\n");
//    printf("#################################################\n");
//   */
// }

// int main(int argc, char *argv[])
// {
//     int pid, status, i;
//     char buf[256], tbuf[256], *cp, *cq;
//     /********************************
//   printf("argc=%d ",argc);
//   for (i=0; i<argc; i++)
//     printf("%s  ", argv[i]);
//   printf("\n\r");
//   *********************************/
//     signal(2, 1); /* ignore signal#2: Control-C interrupts */

//     color = getpid() + 0x000A;
//     //printf("sh %d running\n", getpid());

//     while (1)
//     {
//         printf("sh %d# ", getpid());

//         gets(buf);
//         /* printf("input=%s\n", buf); */
//         if (buf[0] == 0)
//             continue;

//         /* condition input string */
//         //     printf("input=%s\n", buf);
//         cp = buf;
//         while (*cp == ' ') // skip leading blanks
//             cp++;

//         cq = cp;
//         while (*cq) // zero our trailing blanks
//             cq++;
//         cq--;
//         while (*cq == ' ')
//         {
//             *cq = 0;
//             cq--;
//         }

//         //printf("input=%s\n", buf);

//         if (strcmp(cp, "") == 0) // if nothing or a bunch of spaces
//             continue;            //    repeat the while loop

//         strcpy(tbuf, cp);
//         strcpy(buf, tbuf);
//         //printf("input=%s\n", buf);

//         strcpy(tbuf, buf);

//         nk = eatpath(tbuf, name);

//         nowait = 0;
//         if (nk > 1)
//         {
//             if (strcmp(name[nk - 1], "&") == 0)
//             {
//                 // must delete & from buf[ ]
//                 cp = buf;
//                 while (*cp)
//                     cp++; // cp to end to buf
//                 while (*cp != ' ')
//                     cp--; // cp back to space
//                 *cp = 0;  // delete & from buf[ ] end

//                 nk--;
//                 nowait = 1;
//             }
//         }

//         if (strcmp(name[0], "cd") == 0)
//         {
//             if (name[1] == 0)
//                 chdir("/");
//             else
//                 chdir(name[1]);
//             continue;
//         }

//         if (strcmp(name[0], "pwd") == 0)
//         {
//             pwd();
//             continue;
//         }

//         if (strcmp(name[0], "echo") == 0)
//         {
//             for (i = 1; i < nk; i++)
//             {
//                 printf("%s ", name[i]);
//             }
//             //printf("\n");
//             continue;
//         }

//         if (strcmp(name[0], "?") == 0 || strcmp(name[0], "help") == 0)
//         {
//             menu();
//             continue;
//         }

//         /* chname must be done by sh itself */
//         if (strcmp(name[0], "chname") == 0)
//         {
//             //printf("sh chname to %s\n", cp);
//             chname(name[1]);
//             continue;
//         }

//         if (strcmp(name[0], "logout") == 0)
//         {
//             printf("##########################################\n");
//             printf("Hey You\007!, I am your process! Don't leave me!\n");
//             printf("Hamm .... The guy just walked out on me!\n");
//             printf("Oh well, I'll commit suicide! So long!\n");
//             printf("##########################################\n");
//             chdir("/");
//             exit(0);
//         }

//         if (strcmp(name[0], "exit") == 0)
//         {
//             exit(0);
//             continue;
//         }

//         printf("parent sh %d: fork a child\n", getpid());

//         pid = fork(); /* sh forks child */

//         if (pid)
//         { /* parent sh */

//             if (nowait)
//             {
//                 printf("parent sh %d: no wait for child\n", getpid());
//                 nowait = 0;
//                 tswitch();
//                 continue;
//             }
//             else
//             {
//                 printf("parent sh %d: wait for child %d to die\n", getpid(), pid);
//                 pid = wait(&status);
//                 printf("sh %d: child %d exit status = %x\n", getpid(), pid, status);
//                 continue;
//             }
//         }
//         else
//         {
//             // printf("child sh %d return to Umode pid=%d\n", getpid(), pid);
//             printf("child sh %d running : cmd=%s\n", getpid(), buf);
//             do_pipe(buf, 0);
//         }
//     }
// }

// // scan breaks up buf = "head | tail" into  "head"  "tail"

// int scan(buf, tail) char *buf;
// char **tail;
// {
//     char *p;

//     p = buf;
//     *tail = 0;

//     while (*p) // scan to buf end line
//         p++;

//     while (p != buf && *p != '|') // scan backward until |
//         p--;

//     if (p == buf) // did not see any |, so head=buf
//         return 0;

//     *p = 0;           // change | to NULL
//     p++;              // move p right by 1
//     while (*p == ' ') // skip over any blanks
//         p++;

//     *tail = p; // change tail pointer to p

//     return 1; // head points at buf; return head
// }

// int do_pipe(char *buf, int *rpd)
// {
//     int hasPipe, pid;
//     char *tail;
//     int lpd[2];

//     /*******************************************************************
//    cmdline = a < infile | b |c | d > outfile
//    1. only FIRST and LAST can have < or > for I/O redirect
//    2. divide cmdline into  head=a|b|c; tail=d;
//    3. pipe(pd);
//       fork();
//       parent: do tail; as pipe reader by close(rpd[1)}; close(0); dup(rpd[0]);
//            then do > redirect;
//            then exec(tail);

//       child : fisan(buf, rpd)
//               if (rpd):  as rpd writer by close(rpd[0]); close(1); dup(rpd[1]);
//   **************************************************************************/
//     if (rpd)
//     {
//         // as writer on RIGHT side pipe
//         close(rpd[0]);
//         close(1);
//         dup(rpd[1]);
//         close(rpd[1]);
//     }

//     //printf("proc %d do_pipe: buf=%s ", getpid(), buf);
//     /*
//   if (rpd) print2f("rpd=[%d %d]  ", rpd[0], rpd[1]);
//   printf("\n");
//   *****************/

//     hasPipe = scan(buf, &tail);
//     //printf("after scan: buf=%s  tail=%s\n", buf, tail);

//     if (hasPipe)
//     { // buf=head; tail->tailString
//         if (pipe(lpd) < 0)
//         { // create LEFT side pipe
//             printf("proc %d pipe call failed\n", getpid());
//             exit(1);
//         }
//         // printf("after pipe(): lpd[0|1]=[%d %d]\n", lpd[0], lpd[1]);
//         pid = fork();

//         if (pid < 0)
//         {
//             printf("proc %d fork failed\n", getpid());
//             exit(1);
//         }

//         if (pid)
//         { // parent as reader on LEFT side pipe
//             close(lpd[1]);
//             close(0);
//             dup(lpd[0]);
//             close(lpd[0]);
//             //printf("proc %d exec %s\n", getpid(), tail);
//             command(tail);
//         }
//         else
//         { // child gets LEFT pipe as its RIGHT pipe
//             do_pipe(buf, lpd);
//         }
//     }
//     else
//     { // no pipe symbol in string must be the leftmost cmd
//         command(buf);
//     }
//     return 1;
// }

// int command(char *s)
// {
//     char *name[16], tbuf[64];
//     int i, j, nk, I;
//     char cmdline[64];

//     strcpy(tbuf, s);
//     nk = eatpath(tbuf, name);

//     I = nk;

//     for (i = 0; i < nk; i++)
//     {
//         if (strcmp(name[i], "<") == 0)
//         {
//             //printf("proc %d redirect input from %s\n", getpid(), name[i+1]);
//             if (I > i)
//                 I = i; // I = index of first < or > or >>
//             if (name[i + 1] == 0)
//             {
//                 printf("invalid < in command line\n\r");
//                 exit(1);
//             }
//             close(0);
//             if (open(name[i + 1], 0) < 0)
//             {
//                 printf("no such input file\n");
//                 exit(2);
//             }
//             break;
//         }
//     }
//     for (i = 0; i < nk; i++)
//     {
//         if (strcmp(name[i], ">") == 0)
//         {
//             //printf("proc %d redirect outout to %s\n", getpid(), name[i+1]);
//             if (I > i)
//                 I = i; // I = index of first > or < or >>
//             if (name[i + 1] == 0)
//             {
//                 printf("invalid > in command line\n\r");
//                 exit(3);
//             }
//             close(1);
//             open(name[i + 1], O_WRONLY | O_CREAT);
//             break;
//         }
//     }
//     for (i = 0; i < nk; i++)
//     {
//         if (strcmp(name[i], ">>") == 0)
//         {
//             //printf("proc %d append output to %s\n",getpid(), name[i+1]);
//             if (I > i)
//                 I = i;
//             if (name[i + 1] == 0)
//             {
//                 printf("invalid >> in command line\n\r");
//                 exit(4);
//             }
//             close(1);
//             open(name[i + 1], O_WRONLY | O_CREAT | O_APPEND);
//             break;
//         }
//     }
//     //printf("after I/O redirection ");

//     strcpy(cmdline, name[0]);
//     //printf("cmdline=%s I=%d ", cmdline, I);

//     for (j = 1; j < I; j++)
//     {
//         strcat(cmdline, " ");
//         strcat(cmdline, name[j]);
//     }
//     /********* must write to 2 for correct output redirect **********/
//     //printf("proc %d exec %s\n", getpid(), name[0]);
//     //printf("%d before exec\n", getpid());
//     if (getpid() < 9)
//     {
//         if (exec(cmdline) < 0)
//             exit(1);
//     }

//     while (1)
//     {
//         printf("%d : enter a key : ", getpid());
//         getc();
//     }
//     return 1;
// }
