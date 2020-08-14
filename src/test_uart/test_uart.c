/*
 * main for testing uart function
 */

#include "jz2440_uart.h"
#include "my_printf.h"


int main(int argc, char *argv[])
{
    unsigned char c;

    jz2440_uart0_init();
    printf("Hello world! \n\r");

    my_printf_test();

    /* uart echo mode */
    while (1)
    {
        c = getchar();

        if (c == '\r') putchar('\n');
        if (c == '\n') putchar('\r');

        putchar(c);
    }

    return 0;
}


