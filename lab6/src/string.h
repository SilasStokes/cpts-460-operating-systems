#ifndef STRING_H
#define STRING_H

int kprintf(char *, ...);// something is going on w this


// functions in sting.c
int strlen(char *s);

int strcmp(char *s1, char *s2);

int strcpy(char *dest, char *src);
int kstrcpy(char *dest, char *src);
int kstrcat(char *dest, char *src);

int atoi(char *s);
int geti();

int memcpy(char *dest, char *src, int size);



#endif