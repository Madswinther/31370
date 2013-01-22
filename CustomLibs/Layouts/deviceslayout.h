#include "includes.h"

#ifndef __DEVICESPAGE_H
#define __DEVICESPAGE_H

#define DEVICE_OFF 0x0000FF
#define DEVICE_ON 0x00FF00

typedef struct {
	double activePower, reactivePower, harmonicPower;
	RectangleWindow * devicebutton;
	char name[5];
} Device;

extern void swapToLayout (int layout);
extern void swapToMain();
extern void swapToLearning();
extern void swapToGraph();
extern void lightLed();

Device * deviceInit(char name[], double activePower, double reactivePower, double harmonicPower, RectangleWindow * window);
Layout * initDevicesLayout();
void addDevice(char name[], double activePower, double reactivePower, double harmonicPower);
void clearDevices();
char edgeDetection(double compareVal, double newVal, double tol);
void checkDevices(Measurement * measurement, Layout * currentLayout);

#endif
