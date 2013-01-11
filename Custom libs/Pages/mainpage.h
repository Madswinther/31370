#include "../layout.h"

#ifndef __MAINPAGE_H
#define __MAINPAGE_H

typedef struct{
  Layout * layout;
  char drawn;
} Page;

Page * initMainPage();
void lightLed();
void swapToLearning();

#endif
