
#include "functions.h"
#include "kbd.h"

int kbd_init()
{
  char scode;
  keyset = 1; // default to scan code set-1
  
  KBD *kp = &kbd;
  kp->base = (char *)0x10006000;
  *(kp->base + KCNTL) = 0x10; // bit4=Enable bit0=INT on
  *(kp->base + KCLK)  = 8;
  kp->head = kp->tail = 0;
  kp->data = 0; kp->room = 128;
  shifted = 0;
  release = 0;
  control = 0;

  printf("Detect KBD scan code: press the ENTER key : ");
  while( (*(kp->base + KSTAT) & 0x10) == 0);
  scode = *(kp->base + KDATA);
  printf("scode=%x ", scode);
  if (scode==0x5A)
    keyset=2;
  printf("keyset=%d\n", keyset);
}

// kbd_handler1() for scan code set 1
void kbd_handler1()
{
  u8 scode, c;
  KBD *kp = &kbd;
  //color = YELLOW;
  scode = *(kp->base + KDATA);

  //printf("scan code = %x ", scode);
  
  if (scode & 0x80)
    return;
  c = unsh[scode];

  if (c != '\r')
    kputc(c);
  
  kp->buf[kp->head++] = c;
  kp->head %= 128;
  kp->data++; kp->room--;

  if (c=='\r')
    kline++;
}

// kbd_handelr2() for scan code set 2
void kbd_handler2()
{
  u8 scode, c;
  KBD *kp = &kbd;
  //color = YELLOW;
  scode = *(kp->base + KDATA);
  //  printf("scanCode = %x  ", scode);

  if (scode == 0xF0){ // key release 
    release = 1;
    return;
  }
  
  if (release && scode != 0x12){ // ordinay key release
    release = 0;
    return;
  }

  if (release && scode == 0x12){ // Left shift key release
    release = 0;
    shifted = 0;
    return;
  }

  if (!release && scode == 0x12){// left key press and HOLD
    release = 0;
    shifted = 1;
    return;
  }

  if (!release && scode == LCTRL){// left Control key press and HOLD
    release = 0;
    control = 1;
    return;
  }

  if (release && scode == LCTRL){ // Left Control key release
    release = 0;
    control = 0;
    return;
  }

  /********* catch Control-C ****************/
  if (control && scode == 0x21){ // Control-C
    // send signal 2 tp processes on KBD
    printf("Control-C: %d\n", control);
    control = 0;
    return;
  }   

  
  if (!shifted)
     c = ltab[scode];
  else
     c = utab[scode];

  if (c != '\r')
    kputc(c);
  
  if (control && scode == 0x23){ // Control-D
    c = 0x04;
    printf("Control-D: c = %x\n", c);
  }   

  kp->buf[kp->head++] = c;
  kp->head %= 128;
  kp->data++; kp->room--;

  if (c=='\r')
    kline++;
}

void kbd_handler()
{
  if (keyset == 1)
    kbd_handler1();
  else
    kbd_handler2();
}


int kgetc()
{
  char c;
  KBD *kp = &kbd;
  //printf("%d in kgetc\n", running->pid); 
  unlock();
  while(kp->data == 0);

  lock();
  c = kp->buf[kp->tail++];
  kp->tail %= 128;
  kp->data--; kp->room++;
  unlock();
  return c;
}

int kgets(char s[ ])
{
  char c;
  while( (c = kgetc()) != '\r'){
    if (c=='\b'){
      s--;
      continue;
    }
    *s++ = c;
  }
  *s = 0;
  return strlen(s);
}

int getc()  // 
{
  char c;
  KBD *kp = &kbd;

  unlock();
  while(kp->data == 0);

  lock();
  c = kp->buf[kp->tail++];
  kp->tail %= 128;
  kp->data--; kp->room++;
  unlock();
  return c;
}
int kgetline(char s[ ])
{
  char c;
  KBD *kp = &kbd;
  
  if (kline==0){
    //kprintf("enter a line from KBD: ");
     while(kline==0); // wait until kline > 0
  }
  // fetch a line from kbuf[ ] 

  while(1){
      c = kp->buf[kp->tail++];
      *s++ = c;
      kp->tail %= 128;
      kp->data--; kp->room++;
      if (c=='\r')
	break;
  }
  *(s-1) = 0;
  kline--;
}

