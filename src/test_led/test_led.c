/*
 * main for testing led function
 */

#include "jz2440_led.h"
#include "jz2440_clock.h"

#define sleep_1s() my_sleep(1000)

int main(int argc, char *argv[])
{

    jz2440_led(1, 0);
    jz2440_led(2, 0);
    jz2440_led(4, 0);

    while (1) {
        jz2440_led(1, 1);
        sleep_1s();
        jz2440_led(2, 1);
        sleep_1s();
        jz2440_led(4, 1);
        sleep_1s();
        jz2440_led(1, 0);
        sleep_1s();
        jz2440_led(2, 0);
        sleep_1s();
        jz2440_led(4, 0);
        sleep_1s();
    }
    return 0;
}



