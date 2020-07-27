#include "my_printf.h"
#include "string_utils.h"


#define NOR_FLASH_BASE  0  /* jz2440, nor-->cs0, base addr = 0 */


/* nor_write_word */
static void nor_write_word(unsigned int base, unsigned int offset, unsigned int val)
{
    volatile unsigned short *p = (volatile unsigned short *)(base + (offset << 1));
    *p = val;
}

/* nor_cmd */
static void nor_cmd(unsigned int offset, unsigned int cmd)
{
    nor_write_word(NOR_FLASH_BASE, offset, cmd);
}

/* nor_read_word */
static unsigned int nor_read_word(unsigned int base, unsigned int offset)
{
    volatile unsigned short *p = (volatile unsigned short *)(base + (offset << 1));
    return *p;
}

/* nor_dat */
static unsigned int nor_dat(unsigned int offset)
{
    return nor_read_word(NOR_FLASH_BASE, offset);
}

/* check Q7 as RY/BY to get busy status */
void wait_ready(unsigned int addr)
{
    unsigned int val;

    val = nor_dat(addr>>1);
    while (~(val | ~(1<<7)));
}


/*
 * jz2440_scan_nor_flash
 */
void jz2440_scan_nor_flash(void)
{
    char str[4];
    unsigned int size;
    int regions, i;
    int region_info_base;
    int block_addr, blocks, block_size, j;
    int cnt;

    int vendor, device;

    /* read ID */
    nor_cmd(0x555, 0xaa);
    nor_cmd(0x2aa, 0x55);
    nor_cmd(0x555, 0x90);
    vendor = nor_dat(0x00);    /* vendor ID = 0xC2 */
    device = nor_dat(0x01);    /* device ID = ? */

    /* reset */
    nor_cmd(0, 0xf0);


    /* CFI mode */
    nor_cmd(0x55, 0x98);

    /* QRY string */
    str[0] = nor_dat(0x10);
    str[1] = nor_dat(0x11);
    str[2] = nor_dat(0x12);
    str[3] = '\0';
    printf("str = %s\n\r", str);

    /* device size */
    size = 1<<(nor_dat(0x27)); /* 2^n */
    printf("vendor id = 0x%x, device id = 0x%x, nor size = 0x%x, %dM\n\r", vendor, device, size, size/(1024*1024));

    /* each region information */
    regions = nor_dat(0x2c);
    region_info_base = 0x2d;
    block_addr = 0;
    printf("Block/Sector start Address:\n\r");
    cnt = 0;
    for (i = 0; i < regions; i++)
    {
        blocks = 1 + nor_dat(region_info_base) + (nor_dat(region_info_base+1)<<8);
        block_size = 256 * (nor_dat(region_info_base+2) + (nor_dat(region_info_base+3)<<8));
        region_info_base += 4;

        for (j = 0; j < blocks; j++)
        {
            printHex(block_addr);
            putchar(' ');
            cnt++;
            block_addr += block_size;
            if (cnt % 5 == 0)
                printf("\n\r");
        }
    }
    printf("\n\r");
    /* reset */
    nor_cmd(0, 0xf0);
}


/*
 * jz2440_erase_nor_flash
 */
void jz2440_erase_nor_flash(void)
{
    unsigned int addr;

    printf("Enter the address of sector to erase: ");
    addr = get_uint();

    printf("erasing ...\n\r");

    /* erase sector */
    nor_cmd(0x555, 0xaa);
    nor_cmd(0x2aa, 0x55);
    nor_cmd(0x555, 0x80);
    nor_cmd(0x555, 0xaa);
    nor_cmd(0x2aa, 0x55);
    nor_cmd(addr>>1, 0x30);
    wait_ready(addr);
}


/*
 * jz2440_write_nor_flash
 */
void jz2440_write_nor_flash(void)
{
    unsigned int addr;
    unsigned char str[100];
    int i, j;
    unsigned int val;

    printf("Enter the address of sector to write: ");
    addr = get_uint();

    printf("Enter the string to write: ");
    gets(str);

    printf("writing ...\n\r");

    i = 0;
    j = 1;
    while (str[i] && str[j])
    {
        val = str[i] + (str[j]<<8);

        nor_cmd(0x555, 0xaa);
        nor_cmd(0x2aa, 0x55);
        nor_cmd(0x555, 0xa0);
        nor_cmd(addr>>1, val);

        wait_ready(addr);

        i += 2;
        j += 2;
        addr += 2;
    }

    val = str[i];
    nor_cmd(0x555, 0xaa);
    nor_cmd(0x2aa, 0x55);
    nor_cmd(0x555, 0xa0);
    nor_cmd(addr>>1, val);
    wait_ready(addr);
}

void jz2440_read_nor_flash(void)
{
    unsigned int addr;
    volatile unsigned char *p;
    int i, j;
    unsigned char c;
    unsigned char str[16];

    printf("Enter the address to read: ");
    addr = get_uint();

    p = (volatile unsigned char *)addr;

    printf("Data : \n\r");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 16; j++)
        {
            c = *p++;
            str[j] = c;
            printf("%02x ", c);
        }

        printf("   ; ");

        for (j = 0; j < 16; j++)
        {
            if (str[j] < 0x20 || str[j] > 0x7e)
                putchar('.');
            else
                putchar(str[j]);
        }
        printf("\n\r");
    }
}

void nor_flash_test(void)
{
    char c;

    while (1)
    {
        printf("[s] Scan nor flash\n\r");
        printf("[e] Erase nor flash\n\r");
        printf("[w] Write nor flash\n\r");
        printf("[r] Read nor flash\n\r");
        printf("[q] quit\n\r");
        printf("Enter selection: ");

        c = getchar();
        printf("%c\n\r", c);

        switch (c)
        {
            case 'q':
            case 'Q':
                return;
                break;

            case 's':
            case 'S':
                jz2440_scan_nor_flash();
                break;

            case 'e':
            case 'E':
                jz2440_erase_nor_flash();
                break;

            case 'w':
            case 'W':
                jz2440_write_nor_flash();
                break;

            case 'r':
            case 'R':
                jz2440_read_nor_flash();
                break;
            default:
                break;
        }
    }
}

