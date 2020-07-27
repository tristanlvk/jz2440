#ifndef __JZ2440_UART_HHHHHHHH
#define __JZ2440_UART_HHHHHHHH

extern void jz2440_uart0_init();
extern void jz2440_uart0_putchar(unsigned char c);
extern int jz2440_uart0_getchar(void);
extern void jz2440_uart0_puts(const char *s);
extern char *jz2440_uart0_gets(char *s);

#define putchar(c)  jz2440_uart0_putchar(c)
#define getchar()   jz2440_uart0_getchar()
#define puts(s)     jz2440_uart0_puts(s)
#define gets(s)     jz2440_uart0_gets(s)

#endif
