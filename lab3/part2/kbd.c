#include "keymap2"

#include <stdlib.h>

#define KCNTL           0x00
#define KSTAT           0x04
#define KDATA           0x08
#define KCLK            0x0C
#define KISTA           0x10

#define PRESSED         1
#define NOT_PRESSED     0
#define KEY_RELEASED    0xF0

#define SHIFT_KEY       (keyboard_input == 0x59 || keyboard_input == 0x12)
#define CONTROL_KEY     (keyboard_input == 0x14 || keyboard_input == 0x14)
#define DEBUG           0

// typedef volatile struct base
// {
//     u32 control, status, clkdiv, int_status;
// } BASE;

typedef volatile struct kbd
{
    char *base;
    // BASE * base;
    char buf[128];
    int head, tail, data, room;
} KBD;

volatile KBD kbd;

extern int lock();
extern int unlock();
// extern int vectors_end();
extern int color;

int release; // key release flag
int control_key_status =    NOT_PRESSED;
int shift_key_status   =    NOT_PRESSED;
// int prev_scode = 0;

int kbd_init()
{
    KBD *kp = &kbd;
    // kp->base = (BASE *)0x10006000;
    kp->base = (char *)0x10006000;
    *(kp->base + KCNTL) = 0x10; // bit4=Enable bit0=INT on
    *(kp->base + KCLK) = 8;     // ARM manual says clock=8
    kp->head = kp->tail = 0;    // circular buffer char buf[128]
    kp->data = 0;
    kp->room = 128;

    release = 0;
}


void kbd_handler()
{
    color = RED;
    if (DEBUG) kputs("Start of kbd_handler: \n");
    color = YELLOW;
    u8 keyboard_input, typed_character;
    KBD *kp = &kbd;
    keyboard_input = *(kp->base + KDATA); // get scan code of this interrpt

    if (DEBUG) kputs("\t\tkbd interrupt scancode = ");
    if (DEBUG) kprintx(keyboard_input);

    if (keyboard_input == KEY_RELEASED)
    {                
        release = 1; // set release flag
        color = GREEN;
        if (DEBUG) kputs("  RETURN BC KEY_RELEASE \n");
        return;
    }

    if (release == 1)
    {               
        if (SHIFT_KEY == PRESSED)
            shift_key_status = NOT_PRESSED;
        if (CONTROL_KEY == PRESSED)
            control_key_status = NOT_PRESSED;
        
        release = 0;
        color = GREEN;
        if (DEBUG) kputs("  RETURN BC release == 1 \n");
        return;
    }

    // right shift 0x36/B6      0x59/F0 59        0x59/F0 59
    if ( SHIFT_KEY == PRESSED) {
        shift_key_status = PRESSED;
        return;
    } 

    if ( CONTROL_KEY == PRESSED) {
        control_key_status = PRESSED;
        return;
    } 


    if (DEBUG) kputs("\t\tShift Pressed?: ");
    if (DEBUG) kprintx(shift_key_status);

    if (DEBUG) kputs("\t\tControl Pressed?: ");
    if (DEBUG) kprintx(control_key_status);




    if (shift_key_status == PRESSED) 
        typed_character = utab[keyboard_input];
    else
        typed_character = ltab[keyboard_input];

    // map keyboard_input to ASCII in lowercase
    if (control_key_status == PRESSED && typed_character == 'd'){
        color = CYAN;
        kputs("Control-D Key\n");
        typed_character = (char)0x4; // typed_character=EOF
    }else if (control_key_status == PRESSED && typed_character == 'c')
    {   
        color = CYAN;
        kputs("Control-C Key\n");
    } else{
        if (DEBUG) kputs("\t\tkbd interrupt :                    ");
        color = BLUE;
        kputc(typed_character);
        // kputs("\n");
    }

    kp->buf[kp->head++] = typed_character;
    kp->head %= 128;
    kp->data++;
    kp->room--;

    color = RED;
    if (DEBUG) kputs("  end of kbd_handler\n");
}

int kgetc()
{
    char typed_character;
    KBD *kp = &kbd;

    unlock(); // unmask IRQ in case it was masked out
    while (kp->data == 0)
        ; // BUSY wait while kp->data is 0

    lock(); // mask out IRQ
    typed_character = kp->buf[kp->tail++];
    kp->tail %= 128; /*** Critical Region ***/
    kp->data--;
    kp->room++;
    unlock(); // unmask IRQ
    return typed_character;
}

int kgets(char s[])
{
    char typed_character;
    while ((typed_character = kgetc()) != '\r')
    {
        *s = typed_character;
        s++;
    }
    *s = 0;
}
