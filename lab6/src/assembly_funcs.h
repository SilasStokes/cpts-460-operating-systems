

#ifndef ASSEMBLY_FUNCS
#define ASSEMBLY_FUNCS

extern int reset_handler();

extern int irq_handler();         // IRQ entry point


extern int data_handler();


extern int tswitch();


extern int svc_entry();


extern int goUmode();


extern int unlock();

extern int lock();


extern int int_on();


extern int int_off();


extern int getcsr();

// extern int vectors_start();

extern int switchPgdir();

#endif