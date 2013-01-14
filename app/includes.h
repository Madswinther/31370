/***************************************************************************
 **
 **
 **    Master inlude file
 **
 **    Used with ARM IAR C/C++ Compiler
 **
 **    (c) Copyright IAR Systems 2007
 **
 **    $Revision: 47021 $
 **
 ***************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>
#include <nxp/iolpc2478.h>

#include "arm_comm.h"
#include "board.h"

#include "drv_touch_scr.h"

#include "sys.h"
#include "sdram_64M_32bit_drv.h"
#include "drv_glcd.h"
#include "iar_logo.h"
   
// User defines
#include "../Custom libs/animation.h"
#include "../Custom libs/parsing.h"
#include "../Custom libs/uart.h"
#include "../Custom libs/gui.h"
#include "../Custom libs/draw.h"
#include "../Custom libs/layout.h"
#include "../Custom libs/Pages/mainpage.h"
#include "../Custom libs/Pages/learningpage.h"
#include "../Custom libs/Pages/graphpage.h"
#include "../Custom libs/graphics/button.h"
#include "../Custom libs/graphics/graph.h"
#include "../Custom libs/graphics/ProgressBar.h"

#endif  // __INCLUDES_H
