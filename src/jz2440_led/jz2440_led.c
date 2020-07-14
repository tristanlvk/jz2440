#include "s3c2440_reg.h"

/*
 * jz2440 led controller
 * NOTE: valid led number is 1/2/4
 */

/*
 * jz2440_led : control led on or off
 * param :      no      - vaild led number(1/2/4)
 *              state   - 0: off, other: on
 */
int jz2440_led(int no, int state)
{

    switch (no) {
        case 1: /* GPF4 */
            GPFCON &= ~(1<<9);  /* set GPF4 to output mode: [9:8]=01 */
            GPFCON |= (1<<8);   /* set GPF4 to output mode: [9:8]=01 */
            if (state)
                GPFDAT &= ~(1<<4);  /* set GPF4 = 0 */
            else
                GPFDAT |= (1<<4);   /* set GPF4 = 1 */
            break;

        case 2: /* GPF5 */
            GPFCON &= ~(1<<11); /* set GPF5 to output mode: [9:8]=01 */
            GPFCON |= (1<<10);  /* set GPF5 to output mode: [9:8]=01 */
            if (state)
                GPFDAT &= ~(1<<5);  /* set GPF5 = 0 */
            else
                GPFDAT |= (1<<5);   /* set GPF5 = 1 */
            break;

        case 4: /* GPF6 */
            GPFCON &= ~(1<<13); /* set GPF6 to output mode: [9:8]=01 */
            GPFCON |= (1<<12);  /* set GPF6 to output mode: [9:8]=01 */
            if (state)
                GPFDAT &= ~(1<<6);  /* set GPF6 = 0 */
            else
                GPFDAT |= (1<<6);   /* set GPF6 = 1 */
            break;

        default:
            return -1;
    }

    return 0;
}

