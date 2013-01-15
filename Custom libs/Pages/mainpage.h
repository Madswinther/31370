#include "../layout.h"

#ifndef __MAINPAGE_H
#define __MAINPAGE_H

#define BUTTON_BACKGROUND 0x0
#define BUTTON_SELECTED 0x303030
#define BUTTON_BORDER 0xFFFFFF


typedef struct{
  Layout * layout;
  char drawn;
} Page;

extern void swapToPage(int page);

Page * initMainPage();
void swapToMain();
void swapToLearning();
void swapToGraph();
void lightLed();

#endif
