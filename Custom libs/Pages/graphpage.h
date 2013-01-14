#include "../layout.h"
#include "mainpage.h"

#ifndef __GRAPHPAGE_H
#define __GRAPHPAGE_H

extern void swapToPage (int page);
extern void swapToMain();
extern void swapToLearning();
extern void lightLed();

Page * initGraphPage();
void updateGraphPage(Measurement * measurement, char draw);
void addPoint();
void changeToVoltage();
void changeToCurrent();
void changeToPower();
void refreshGraph();
#endif
