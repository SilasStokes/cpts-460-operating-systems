



# Feb 1 Chapter 3:

Lab3.1 is posted - should not take any time at all. 


## Lab 3.1:
    - There's a cursor that is stationary - we need to make it flash once a second. 
        - how do we do that? Every half second we turn it on, else turn it off.
    - Write the code to show a world clock in the upper right hand corner. 

KC is going to explain the code
    - mk : standard mk script we've been using. 
    - t.ld: when an interupt occurs we go to irq mode, thats what the second part of SECTIONS is:
    - ts.s :    svc_stack is an export symbol from the linker, that what is setting the stack location. 
                0 to 64k 
