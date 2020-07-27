#include "s3c2440_reg.h"

/*
 * jz2440 uart related functions
 */

/*
 * jz2440_uart0_init : init the UART_0
 *          param    : 115200, 8, 1, 0
 * NOTE: UART_0 connectes to the on-board USB_UART IF
 */
void jz2440_uart0_init()
{

    /* set the GPIO port to TX/RX and enable the pull up
     * TXD0 : GPH2
     * RXD0 : GPH3
     */
    GPHCON &= ~((3<<6) | (3<<4));
    GPHCON |= ((2<<6) | (2<<4));
    GPHUP &= ~((1<<2) | (1<<3));


    /* ULCON0 : b[7]    : 0     rsv
     *          b[6]    : 0     normal mode(not infrared mode)
     *          b[5:3]  : 000   no parity
     *          b[2]    : 0     1 stop bit
     *          b[1:0]  : 11    8 data bits
     */
    ULCON0 = 0x3;

    /* UCON0 : b[15:12] : 0000  FCLK divider, not used
     *         b[11:10] : 00    PCLK is the source
     *         b[9]     : 0     TX Interrupt in pulse
     *         b[8]     : 0     RX Interrupt in pulse
     *         b[7]     : 0     RX timeout int disabled
     *         b[6]     : 0     Rx error sts int disabled
     *         b[5]     : 0     normal mode (not loopback mode)
     *         b[4]     : 0     normal mode (not sending break signal)
     *         b[3:2]   : 01    tx mode int or poll
     *         b[1:0]   : 01    rx mode int or poll
     */
    UCON0 = 0x5;

    /* UFCON0 : b[7:6]  : 00    TX FIFO trig level : empty
     *          b[5:4]  : 11    RX FIFO trig level : 32 bytes
     *          b3      : 0     rsv
     *          b2      : 0     TX FIFO RST
     *          b1      : 0     RX FIFO RST
     *          b0      : 0     FIFO disabled
     */
    UFCON0 = 0x00;

    /* UMCON0 : auto flow control is diabled    */
    UMCON0 = 0x0;

    /* UBRDIV0 : b[15:0]    : baud rate division
     *          div = uart_clock/(buad_rate*16)-1
     *          div = int(50000000/(115200*16)-1) = 26
     */
    UBRDIV0 = 0x1A;

    return;
}


/* jz2440_uart0_putchar
 * send one byte via uart0
 */
void jz2440_uart0_putchar(unsigned char c)
{
    while (!(UTRSTAT0 & 0x2));
    UTXH0 = c;
}

/* jz2440_uart0_getchar
 * get one byte via uart0
 */
int jz2440_uart0_getchar(void)
{
    while (!(UTRSTAT0 & 0x1));
    return URXH0;
}

/* jz2440_uart0_puts
 * send strings via uart0
 */
void jz2440_uart0_puts(const char *s)
{
    char tmp;
    while ((tmp = *s++))
        jz2440_uart0_putchar(tmp);
}

/*
 * jz2440_uart0_gets
 */
char *jz2440_uart0_gets(char *s)
{
    int i = 0;
    char c;

    while(1) {
        c = jz2440_uart0_getchar();     /* get one char */
        jz2440_uart0_putchar(c);        /* echo */

        /* TODO : why need this ? */
        /*if (c == '\n')          jz2440_uart0_putchar('\r');*/
        /*else if (c == '\r')     jz2440_uart0_putchar('\n');*/

        if((c == '\n') || (c == '\r')) {
            s[i] = '\0';
            break;
        } else {
            s[i++] = c;
        }
    }

    return s;
}




