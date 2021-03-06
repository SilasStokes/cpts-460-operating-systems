/*********  t.c file *********************/
int gets(char *s);
int prints(char *s);

int prints(char *s)
{
    while (*s)
    {
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
char ans[64];

main()
{
    while (1)
    {
        prints("What's your name? ");
        gets(ans);
        prints("\n\r");
        if (ans[0] == 0)
        {
            prints("return to assembly and hang\n\r");
            return;
        }
        prints("Welcome ");
        prints(ans);
        prints("\n\r");
    }
}
