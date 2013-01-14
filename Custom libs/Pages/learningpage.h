#include "../layout.h"
#include "mainpage.h"

#ifndef __LEARNINGPAGE_H
#define __LEARNINGPAGE_H

extern void swapToPage (int page);
extern void swapToMain();
extern void swapToGraph();
extern void lightLed();
extern Measurement * getMeasurement();

Page * initLearningPage();
void doLearn();

#endif
