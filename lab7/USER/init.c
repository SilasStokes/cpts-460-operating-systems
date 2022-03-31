#include "functions.h"
// #include "ucode.c"
#define printk printf

int console, s0, s1;

void login()
{
    exec("login /dev/tty0");
}
void s0login()
{
    exec("login /dev/ttyS0");
}
void s1login()
{
    exec("login /dev/ttyS1");
}

void another(int pid)
{
    printf("-----------------------------------------------------\n");
    printf("KCINIT: Oh my God! My beloved login child %d has died\n", pid);
    printf("KCINIT: Oh well, I'll just fork another one!\n");
    printf("-----------------------------------------------------\n");
}

void parent()
{
    int pid, status;
    printf("KCINIT : waiting .....\n");
    while (1)
    {
        pid = wait(&status);

        if (pid == console)
        {
            console = fork();
            if (console)
                continue;
            else
                login();
        }
        if (pid == s0)
        {
            s0 = fork();
            if (s0)
                continue;
            else
                s0login();
        }
        if (pid == s1)
        {
            s1 = fork();
            if (s1)
                continue;
            else
                s1login();
        }
        printf("KCINIT: I just buried an orphan child task %d\n", pid);
    }
}

void cdserver()
{
    exec("cdserver");
    exit(1);
}

int main(int argc, char *argv[])
{
    int in, out;
    int pid;
    in = open("/dev/tty0", O_RDONLY);
    out = open("/dev/tty0", O_WRONLY);

    pid = getpid();

    printf("proc %d in Umode ", pid);
    printf("argc=%d %s %s\n", argc, argv[0], argv[1]);

    printf("INIT %d: fork a login proc on console\n", pid);

    console = fork();
    if (console)
    { // parent

        printf("INIT %d fork login procs on UARTs\n", pid);
        s0 = fork();
        if (s0)
        {
            s1 = fork();
            if (s1)
                parent();
            else
                s1login();
        }
        else
            s0login();
    }
    else
        login();
}
