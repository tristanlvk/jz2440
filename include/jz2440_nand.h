#ifndef __JZ2440_NAND_HHHHHHHH
#define __JZ2440_NAND_HHHHHHHH

#include "s3c2440_reg.h"
#include "my_printf.h"

extern void jz2440_nand_init(void);
extern void jz2440_nand_scan_bad(void);
extern void jz2440_nand_read(unsigned int addr, unsigned char *buf, unsigned int len);

#endif
