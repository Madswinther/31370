#include "../layout.h"

#ifndef __MAINPAGE_H
#define __MAINPAGE_H

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
