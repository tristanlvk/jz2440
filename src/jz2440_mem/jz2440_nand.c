/*
 * jz2440_nand
 */

#include "jz2440_nand.h"

/* delay_cycle used to delay certain time during DATA/ADR/CMD access */
#define DELAY_CYCLE 12
#define TXD0READY   (1<<2)

/*
 * jz2440_nand_init
 */
void jz2440_nand_init(void)
{
/* timing parameters pls refer to NAND Flash datasheet */
/* in this timing setting, is as follows : each costs 3xHCLK
 * CLE/ALE  -> ____/--------\----
 * nWE      -> ----\________/----
 * DATA/ADR -> xxxx- DDDDDDDDDDDD-xxxxx
 * CYCLE    -> xxxx- 0---1---2---
 */
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0

    /* NFCONF */
    NFCONF = (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);

    /* NFCONT
     * init ECC controller
     * disable nCE, that's the default status
    */
    NFCONT = (1<<4)|(1<<1)|(1<<0);
}

/*
 * nand_select
 * enable nCE
 */
static void nand_select(void)
{
    NFCONT &= ~(1<<1);
}

/*
 * nand_deselect
 * disable nCE
 */
static void nand_deselect(void)
{
    NFCONT |= (1<<1);
}


/*
 * nand_cmd
 */
static void nand_cmd(unsigned char cmd)
{
    volatile int i;
    NFCMD = cmd;
    for(i = 0; i < DELAY_CYCLE; i++);
}


/*
 * nand_addr
 */
static void nand_addr(unsigned int addr)
{
    volatile int i;
    unsigned int col  = addr % 2048;
    unsigned int page = addr / 2048;

    NFADDR  = col & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR  = (col >> 8) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);

    NFADDR  = page & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR  = (page >> 8) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR  = (page >> 16) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
}


/*
 * nand_page
 */
static void nand_page(unsigned int page)
{
    volatile int i;

    NFADDR  = page & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR  = (page >> 8) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR  = (page >> 16) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
}


/*
 * nand_col
 */
static void nand_col(unsigned int col)
{
    volatile int i;

    NFADDR = col & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
    NFADDR = (col >> 8) & 0xff;
    for(i = 0; i < DELAY_CYCLE; i++);
}


/*
 * nand_wait_ready
 */
static void nand_wait_ready(void)
{
    while (!(NFSTAT & 1));
}

/*
 * nand_data
 */
static unsigned char nand_data(void)
{
    return NFDATA;
}

/*
 * nand_bad
 * read out the initial invalid blocks
 */
static int nand_bad(unsigned int addr)
{
    unsigned int col  = 2048;
    unsigned int page = addr / 2048;
    unsigned char val;

    nand_select();

    nand_cmd(0x00);

    nand_col(col);
    nand_page(page);

    nand_cmd(0x30);

    nand_wait_ready();

    val = nand_data();

    nand_deselect();

    if (val != 0xff)
        return 1;  /* bad blcok */
    else
        return 0;
}

/*
 * jz2440_nand_read
 */
void jz2440_nand_read(unsigned int addr, unsigned char *buf, unsigned int len)
{
    int col = addr % 2048;
    int i = 0;

    while (i < len) {

        if (nand_bad(addr))
            printf("nand page %d is bad block \n\r", addr / 2048);

        nand_select();

        nand_cmd(0x00);

        nand_addr(addr);

        nand_cmd(0x30);

        nand_wait_ready();

        for (; (col < 2048) && (i < len); col++)
        {
            buf[i] = nand_data();
            i++;
            addr++;
        }

        col = 0;

        nand_deselect();

    }
}


/*
 * jz2440_nand_scan_bad
 */
void jz2440_nand_scan_bad(void)
{
    int adr = 0;
    while (adr < 256*1024*1024) {
        if (nand_bad(adr))
            printf("nand page %d is bad block \n\r", adr / 2048);

        adr += 2048;
    }

    printf("nand scan bad block finished \n\r");
}


