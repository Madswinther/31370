#include "../layout.h"
#include "mainpage.h"

#ifndef __GRAPHPAGE_H
#define __GRAPHPAGE_H

extern void swapToPage (int page);
extern void swapToMain();
extern void swapToLearning();
extern void lightLed();

Page * initGraphPage();

#endif
