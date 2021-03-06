#include "../layout.h"

#ifndef __NAVIGATIONBARLAYOUT_H
#define __NAVIGATIONBARLAYOUT_H

#define BUTTON_BACKGROUND 0x0
#define BUTTON_SELECTED 0x303030
#define BUTTON_BORDER 0xFFFFFF

extern void swapToPage(int page);

Layout * initNavigationBar();
void swapToMain();
void swapToLearning();
void swapToGraph();
void swapToDevices();
void lightLed();
static void setSelected(int button);

#endif
