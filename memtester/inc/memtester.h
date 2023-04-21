/*
 * Very simple (yet, for some reason, very effective) memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2020 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains the declarations for external variables from the main file.
 * See other comments in that file.
 *
 */
 
#ifndef MEMTESTER_H
#define MEMTESTER_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "memtester_types.h"
#include "memtester_sizes.h"
#include "memtester_tests.h"

#define PROGRESSOFTEN 32768  
#define STUCK_LOOPS 2       /* 16 */
#define SOLIDBITS_LOOPS 2   /* 64 */
#define CHECKERBOARD_LOOPS 2      /* 64 */
#define BLOCKSEQ_LOOPS  1   /* 256 */

int memtester_main(ulv* bufa, int testmask, int bufsize, int loops);

#ifdef __cplusplus
}
#endif

#endif