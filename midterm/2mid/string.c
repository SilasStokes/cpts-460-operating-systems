#define bcopy  kbcopy
#define memcpy kmemcpy
// #define strcpy kstrcpy
#define strlen kstrlen

extern int kgets(char string[ ]);

// int kprintf(char *fmt,...)
// {
//   int *ip;
//   char *cp;
//   cp = fmt;
//   ip = (int *)&fmt + 1;

//   while(*cp){
//     if (*cp != '%'){
//       kputc(*cp);
//       if (*cp=='\n')
// 	kputc('\r');
//       cp++;
//       continue;
//     }
//     cp++;
//     switch(*cp){
//     case 'c': kputc((char)*ip);      break;
//     case 's': kprints((char *)*ip);  break;
//     case 'd': kprinti(*ip);          break;
//     case 'u': kprintu(*ip);          break;
//     case 'x': kprintx(*ip);          break;
//     }
//     cp++; ip++;
//   }
// }

int kbcopy(const void *src, void *dest, unsigned int n)
{
   const char *s = (const char *)src;
   char *d = (char *)dest;
   if (s <= d){
      for (; n>0; --n)
         d[n-1] = s[n-1];
   } 
   else{
     for (; n>0; --n)
	*d++ = *s++;
   }
}

char *kmemcpy(void *dest, const void *src, unsigned int n)
{
      kbcopy(src, dest, n);
      return dest;
}

int kstrlen(char *s)
{
  int i = 0;
  while(*s){
    i++; s++;
  }
  return i;
}
int strcmp(char *s1, char *s2)
{
  while((*s1 && *s2) && (*s1==*s2)){
      s1++; s2++;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}
int kstrcmp(char *s1, char *s2)
{
  while((*s1 && *s2) && (*s1==*s2)){
      s1++; s2++;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}

int kstrcpy(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}


int strcpy(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}

int atoi(char *s)
{
  int v = 0;
  while (*s){
    v = 10*v + (*s - '0');
    s++;
  }
  //kprintf("v=%d\n", v);
  return v;
}
int geti()
{
  char s[16];
  kgets(s);
  return atoi(s);
}
