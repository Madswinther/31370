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

//uIP
#include "../CustomLibs/uIP/clock-arch.h"
#include "../CustomLibs/uIP/timer.h"
#include "../CustomLibs/uIP/uip-conf.h"
#include "../CustomLibs/uIP/uipopt.h"
#include "../CustomLibs/uIP/uip_arp.h"
#include "../CustomLibs/uIP/uip.h"
#include "../CustomLibs/uIP/tapdev.h"
#include "../CustomLibs/uIP/httpd/httpd.h"
#include "../CustomLibs/uIP/LPC24xx_enet.h"
   
// User defines
#include "../CustomLibs/animation.h"
#include "../CustomLibs/parsing.h"
#include "../CustomLibs/uart.h"
#include "../CustomLibs/rtc.h"
#include "../CustomLibs/gui.h"
#include "../CustomLibs/draw.h"
#include "../CustomLibs/xml.h"
#include "../CustomLibs/layout.h"
#include "../CustomLibs/Layouts/mainlayout.h"
#include "../CustomLibs/Layouts/learninglayout.h"
#include "../CustomLibs/Layouts/graphlayout.h"
#include "../CustomLibs/Layouts/deviceslayout.h"
#include "../CustomLibs/Layouts/navigationbarlayout.h"
#include "../CustomLibs/graphics/graph.h"
#include "../CustomLibs/graphics/next.h"
#include "../CustomLibs/graphics/previous.h"
#include "../CustomLibs/graphics/ProgressBar.h"
#include "../CustomLibs/graphics/ProgressSpinner.h"

#endif  // __INCLUDES_H
