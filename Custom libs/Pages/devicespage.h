#include "../layout.h"
#include "mainpage.h"

#ifndef __DEVICESPAGE_H
#define __DEVICESPAGE_H

#define DEVICE_OFF 0x0000FF
#define DEVICE_ON 0x00FF00

extern void swapToPage (int page);
extern void swapToMain();
extern void swapToLearning();
extern void swapToGraph();
extern void lightLed();

Page * initDevicesPage();
void addDevice();

#endif
