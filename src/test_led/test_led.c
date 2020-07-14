/*
 * main for testing led function
 */

#include "jz2440_led.h"

static void sleep(int ms);

int main(int argc, char *argv[])
{

    jz2440_led(1, 0);
    jz2440_led(2, 0);
    jz2440_led(4, 0);

    while (1) {
        jz2440_led(1, 1);
        sleep(1000);
        jz2440_led(2, 1);
        sleep(1000);
        jz2440_led(4, 1);
        sleep(1000);
        jz2440_led(1, 0);
        sleep(1000);
        jz2440_led(2, 0);
        sleep(1000);
        jz2440_led(4, 0);
        sleep(1000);
    }
    return 0;
}


/*
 * use loop to sleep
 * one loop roughly needs 8*instructions
 * if FCLK = 400MHz, then roughly 50000 needed to get 1ms
 */
static void sleep(int ms)
{
    volatile int i;
    for (i = 0; i < 50000*ms; i++)
        ;
}

