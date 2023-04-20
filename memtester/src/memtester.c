/*
 * memtester version 4
 *
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2020 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 */

#define __version__ "4.6.0"

#include <string.h>
#include "memtester.h"

#define EXIT_FAIL_NONSTARTER    0x01
#define EXIT_FAIL_ADDRESSLINES  0x02
#define EXIT_FAIL_OTHERTEST     0x04

struct test tests[18] = {
    { "Random Value", test_random_value },
    { "Compare XOR", test_xor_comparison },
    { "Compare SUB", test_sub_comparison },
    { "Compare MUL", test_mul_comparison },
    { "Compare DIV",test_div_comparison },
    { "Compare OR", test_or_comparison },
    { "Compare AND", test_and_comparison },
    { "Sequential Increment", test_seqinc_comparison },
    { "Solid Bits", test_solidbits_comparison },
    { "Block Sequential", test_blockseq_comparison },
    { "Checkerboard", test_checkerboard_comparison },
    { "Bit Spread", test_bitspread_comparison },
    { "Bit Flip", test_bitflip_comparison },
    { "Walking Ones", test_walkbits1_comparison },
    { "Walking Zeroes", test_walkbits0_comparison },
#ifdef TEST_NARROW_WRITES    
    { "8-bit Writes", test_8bit_wide_random },
    { "16-bit Writes", test_16bit_wide_random },
#endif
    { NULL, NULL }
};

int memtester_main(ulv* bufa, int testmask, int bufsize, int loops) {
    int loop;
    int exit_code = 0;
    int halflen = bufsize / 2;
    int count = halflen / sizeof(ul);
    int i;
    bufa = (ulv *) bufa;
    ulv* bufb = (ulv *) ((size_t) bufa + halflen);

    for(loop=1; ((!loops) || loop <= loops); loop++) {
        memtester_printf("Loop %d", loop);
        if (loops) {
            memtester_printf("/%d", loops);
        }
        memtester_printf(":\n");
        memtester_printf("  %-20s: ", "Stuck Address");
        if (!test_stuck_address(bufa, bufsize / sizeof(ul))) {
             memtester_printf("ok\n");
        } else {
            exit_code |= EXIT_FAIL_ADDRESSLINES;
        }
        for (i=0;;i++) {
            if (!tests[i].name) break;
            /* If using a custom testmask, only run this test if the
               bit corresponding to this test was set by the user.
             */
            if (testmask && (!((1 << i) & testmask))) {
                continue;
            }
            memtester_printf("  %-20s: ", tests[i].name);
            if (!tests[i].fp(bufa, bufb, count)) {
                memtester_printf("ok\n");
            } else {
                exit_code |= EXIT_FAIL_OTHERTEST;
            }
            /* clear buffer */
            memset((void *) bufa, 255, bufsize);
        }
        memtester_printf("\n");
    }
    memtester_printf("Done.\n");
    return 0;
}
