#include "s3c2440_reg.h"
#include "jz2440_nand.h"

/*
 * init code running memroy enviroment
 * copy code to sdram
 * clean BSS
 */


/*
 * jz2440_copy2sdram_nor
 * copy section text, rodata, data to sdram
 */
void jz2440_copy2sdram_nor(void)
{
    extern int __code_start, __bss_start;   /* symbol defined in ld scripts */

    volatile unsigned int *src = (volatile unsigned int *)0;                /* from address 0 */
    volatile unsigned int *dst = (volatile unsigned int *)&__code_start;    /* to SDRAM address */
    volatile unsigned int *end = (volatile unsigned int *)&__bss_start;

    while (dst < end) *dst++ = *src++;
}


/*
 * jz2440_copy2sdram_nand
 * copy section text, rodata, data to sdram
 */
void jz2440_copy2sdram_nand(void)
{
    extern int __code_start, __bss_start;   /* symbol defined in ld scripts */

    volatile unsigned char *dst = (volatile unsigned char *)&__code_start;   /* to SDRAM address */
    volatile unsigned char *end = (volatile unsigned char *)&__bss_start;

    int len;

    if (end < dst)
        return;
    else {
        len = end - dst + 1;
        jz2440_nand_read(0, dst, len);
    }
}



/*
 * jz2440_clean_bss
 * init BSS data to 0
*/
void jz2440_clean_bss(void)
{
    extern int __bss_start, _end;   /* symbol defined in ld scripts */

    volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
    volatile unsigned int *end = (volatile unsigned int *)&_end;

    while (start <= end) *start++ = 0;

}


