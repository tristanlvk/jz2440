/*
 * main for testing uart function
 */

#include "jz2440_uart.h"
#include "my_printf.h"

static void sleep(int ms);

int main(int argc, char *argv[])
{
    unsigned char c;

    jz2440_uart0_init();
    printf("Hello world! \n\r");

    my_printf_test();

    /* uart echo mode */
    while (1)
    {
        c = jz2440_uart0_getchar();

        if (c == '\r') {
            jz2440_uart0_putchar('\n');
        }
        if (c == '\n') {
            jz2440_uart0_putchar('\r');
        }

        jz2440_uart0_putchar(c);
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

