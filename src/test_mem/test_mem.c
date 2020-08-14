/*
 * main for testing sdram function
 */

#include "jz2440_mem.h"
#include "my_printf.h"
#include "jz2440_nand.h"
#include "jz2440_uart.h"

int main(int argc, char *argv[])
{

    jz2440_uart0_init();

    printf("======> do sdram test ... \n\r");

    /*
    if (0 == jz2440_sdram_test()) {
        printf("sdram test pass \n\r");
    } else {
        printf("sdram test fail \n\r");
    }
    */

    const num = 10;
    int c[num];
    int i;

    /* write to sdram */
    printf("write to sdram... \n\r");
    for (i = 0; i < num; i++) c[i] = i;

    /* read from sdram and check */
    printf("read from sdram... \n\r");
    for (i = 0; i < num; i++) {
        if (c[i] != i)
            printf("sdram test fail \n\r");
    }

    printf("sdram test pass \n\r");

    jz2440_nand_scan_bad();

    my_printf_test();

}


