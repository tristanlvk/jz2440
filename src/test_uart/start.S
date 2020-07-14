/*
 * start file to load main function
 */

 /* external function */
.extern jz2440_clock_init
.extern main


.text
.global _start

_start:

    /* disable watch dog */
    ldr r0, =0x53000000
    ldr r1, =0
    str r1, [r0]

    bl jz2440_clock_init

    /* set the SP pointer */
    /* TODO : not prefect */
    /* to see if it's boot from NOR or NAND
     * first readout the value of address 0,
     * then to see if could change it successfully
     */
    mov r1, #0
    ldr r0, [r1]    /* read out the now value */
    str r1, [r1]    /* 0 -> [0] */
    ldr r2, [r1]    /* r2 = [0] */
    cmp r1, r2
    ldr sp, =0x40000000+4096    /* for NOR */
    moveq sp, #4096             /* for nand */
    streq r0, [r1]  /* restore the value */

    bl main

halt:
    b halt
