#include "includes.h"

#ifndef __GRAPHPAGE_H
#define __GRAPHPAGE_H

#define VOLTAGE_BUTTON 0
#define CURRENT_BUTTON 1
#define POWER_BUTTON 2


Layout * initGraphLayout();
void updateGraphLayout(Measurement * measurement, char draw);
void addPoint();
void changeToVoltage();
void changeToCurrent();
void changeToPower();
static void setSelected(int button);
void refreshGraph();
#endif
