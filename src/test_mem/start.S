/*
 * start file to load main function
 */

 /* external function */
.extern jz2440_clock_init
.extern jz2440_sdram_init
.extern jz2440_copy2sdram
.extern jz2440_clean_bss
.extern main


.text
.global _start

_start:

    /* disable watch dog */
    ldr r0, =0x53000000
    ldr r1, =0
    str r1, [r0]

    bl jz2440_clock_init        /* init clock */

    /* set the SP pointer */
    /* to see if it's boot from NOR or NAND
     * write #0 to the address 0 to see if it could be written
     * since the #0 is not the valid opCode, for NOR, address 0 data is not #0
     */
    mov r1, #0
    ldr r0, [r1]    /* store the original value to R0 */
    str r1, [r1]    /* 0 -> [0] */
    ldr r2, [r1]    /* r2 = [0] */
    cmp r1, r2
    ldr sp, =0x40000000+4096    /* for NOR */
    moveq sp, #4096             /* for nand */
    streq r0, [r1]  /* restore the value */

    bl jz2440_sdram_init        /* init sdram */
    bl jz2440_nand_init         /* init nand */

    bl jz2440_copy2sdram_nand   /* copy text/data/rodata to sdram */
    bl jz2440_clean_bss         /* clean bss data */

    /* reset the SP pointer to SDRAM top */
    ldr sp, =0x34000000         /* SDRAM is 64M */

    ldr lr, =halt
    ldr pc, =main   /* absolute jump */

halt:
    b halt
