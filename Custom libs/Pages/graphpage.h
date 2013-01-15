#include "../layout.h"
#include "mainpage.h"

#ifndef __GRAPHPAGE_H
#define __GRAPHPAGE_H

#define VOLTAGE_BUTTON 4
#define CURRENT_BUTTON 5
#define POWER_BUTTON 6

extern void swapToPage (int page);
extern void swapToMain();
extern void swapToLearning();
extern void swapToDevices();
extern void lightLed();

Page * initGraphPage();
void updateGraphPage(Measurement * measurement, char draw);
void addPoint();
void changeToVoltage();
void changeToCurrent();
void changeToPower();
static void setSelected(int button);
void refreshGraph();
#endif
