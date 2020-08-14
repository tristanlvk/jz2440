#include "s3c2440_reg.h"

/*
 * jz2440 mem controller
 */


/*
 * jz2440_sdram_init
 */
void jz2440_sdram_init(void)
{
    /* only bank 6 needs configured for SDRAM */
    BWSCON  = 0x02000000;

    /* BANK0 ~ BANK5 are not touched
     * NOTE : BANK0 is used for NOR Flash, BANK4 is used for ETH MAC
     */

    /* BANK6
     * [16:15]  - MT    = 11
     * [3:2]    - Trcd  = 0 - 2 clocks
     * [1:0]    - SCAN  = 1 - col address line = 9
     * */
    BANKCON6 = 0x00018001;

    /* BANK7 untouched */

    /* REFRESH : enable auto refresh
     *          Trp=2xclocks/tsrc=5xclocks
     *          refresh_counter=1269 - 64ms for 8192 cycles
     */
    REFRESH = 0x008404F5;

    /* BANKSIZE : enable burst/64M */
    BANKSIZE = 0xB1;

    /* MRSRB6 : CL=2xclocks */
    MRSRB6 = 0x20;

    /* MRSRB7untouched */

}


/*
 * jz2440_sdram_test
 */
int jz2440_sdram_test(void)
{
    volatile unsigned char *p = (volatile unsigned char *)0x30000000;
    int i;

    /* write sdram */
    for (i = 0; i < 1000; i++) {
        p[i] = (unsigned char)(i & 0xFF);
    }

    /* read sdram and check */
    for (i =0; i < 1000; i++) {
        if (p[i] != (i & 0xFF))
            return -1;
    }

    return 0;
}


