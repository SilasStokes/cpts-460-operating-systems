	.text
	.global start, sum
	.global main

start:	ldr sp, =stack_top
	bl  main
stop:	b   stop

sum:    // int sum(int *ip, int n): ip in r0, n in r1
	stmfd sp!, {r4-r12, lr} // save regs in stack
	// stack = HIGH |lr r12 r11 r10 r9 r8 r7 r6 r5 f4| LOW
        //                                             sp
        mov r4, r0         // r4->A[]
	mov r0, #0         // r0 = 0
loop:	
	ldr r5, [r4], #4   // r3 = *r2++
	add r0, r0, r5     // r0 += A[i]
	
	sub r1, r1, #1     // r1--
	cmp r1, #0         
	bne loop

	// r0 now contains sum of A[]; to be returned as total=sum(A,10)

	ldmfd sp!, {r4-r12, pc} // pop saved r4-r12, lr into pc => return
	
	
