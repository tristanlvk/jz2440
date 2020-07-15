/*
 * main for testing sdram function
 */

#include "jz2440_led.h"
#include "jz2440_mem.h"

int main(int argc, char *argv[])
{
    /* turn on all leds */
    jz2440_led(1, 1);
    jz2440_led(2, 1);
    jz2440_led(4, 1);

    /* init sdram */
    jz2440_sdram_init();

    if (jz2440_sdram_test()) {
        /* turn off all leds */
        jz2440_led(1, 0);
        jz2440_led(2, 0);
        jz2440_led(4, 0);
    }

    return 0;
}


