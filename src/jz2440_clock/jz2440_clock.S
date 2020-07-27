/*
 * jz2440 clock init
 * NOTE: max freq: FCLK-400MHz; HCLK-133MHz; PCLK-67MHz
 * NOTE: XTLL is 12MHz
 * jz2440_clock_init : init clock freq to:
 *      FCLK : 400MHz; HCLK-100MHz; PCLK-50MHz
 */


.text
.global jz2440_clock_init
.type jz2440_clock_init, STT_FUNC

jz2440_clock_init:

    /* LOCKTIME : set to max */
    ldr r0, =0x4C000000
    ldr r1, =0xFFFFFFFF
    str r1, [r0]

    /* CLKCON : enable all function block */
    ldr r0, =0x4C00000C
    ldr r1, =0x00FFFFF0
    str r1, [r0]

    /* CLKSLOW : set in normal mode */
    ldr r0, =0x4C000010
    ldr r1, =0x00000004
    str r1, [r0]

    /* CLKDVIN : set div of FCLK:HCLK:PCLK = 1:4:8 */
    ldr r0, =0x4C000014
    ldr r1, =0x00000005
    str r1, [r0]

    /* CAMDIVN : don't touch, let be the default value */

    /* set CPU bus into async bus mode */
    /* set the CP15 register 1, [b31:b30] = 11, see ARM920T_TRM.P2.3.5*/
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #0xC0000000
    mcr p15, 0, r0, c1, c0, 0

    /* UPLLCON : set to 48MHz */
    ldr r0, =0x4C000008
    ldr r1, =0x00038022
    str r1, [r0]

    /* 8 NOPs between UPLL and MPLL setting */
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    /* MPLLCON : set to 400MHz */
    ldr r0, =0x4C000004
    ldr r1, =0x0005C011
    str r1, [r0]


    /* return */
    MOV pc, lr





