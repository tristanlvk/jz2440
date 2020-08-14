/*
 * main for testing nand
 */

#include "jz2440_nand.h"
#include "my_printf.h"

int main(int argc, char *argv[])
{

    /*printf("======> do nand test ... \n\r");*/

    int i;
    unsigned char c_a[20];

    jz2440_nand_read(0, c_a, 20);

    for (i = 0; i < 20; i ++)
        printf("%02x\n\r", c_a[i]);

    return 0;

}


