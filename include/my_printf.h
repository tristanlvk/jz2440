#ifndef __MY_PRINTF_HHHHHHHH
#define __MY_PRINTF_HHHHHHHH

#include "jz2440_uart.h"

#define  __out_putchar  jz2440_uart0_putchar

#define  MAX_NUMBER_BYTES  64

extern int my_printf_test(void);
extern int printf(const char *fmt, ...);

#endif /* __MY_PRINTF_HHHHHHHH */

