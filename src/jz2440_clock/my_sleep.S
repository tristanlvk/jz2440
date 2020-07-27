/*
 * my_sleep(int ms)
 * sleep using for loop
 */


.text
.global my_sleep
.type my_sleep, STT_FUNC

my_sleep:

    /* check parameter */
    mov r1, #0
    cmp r1, r0
    beq end_loop

s_loop:
    /* init ms counter : 400*1000 @400MHz */
    ldr r2, =400000/9
    mov r3, #0

    /* one loop costs 5*clocks in ARM9 */
ms_loop:
    add r3, r3, #1
    cmp r3, r2
    bne ms_loop

    add r1, r1, #1
    cmp r1, r0
    bne s_loop

end_loop:
    /* return */
    mov pc, lr






