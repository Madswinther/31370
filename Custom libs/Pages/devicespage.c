#include "devicespage.h"
#include "mainpage.h"
#include "includes.h"
#include <math.h>

static Page * thisPage;
static Device * devices[6];

// Iterators to allow for adding devices
static char size = 0;
static short mX = 20;
static short mY = 20;

// Holder for comparison of measurements
static Measurement * lastReading;
static Measurement * lastStationary;
static char isStationary = 1;

Page * initDevicesPage(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(*thisPage));
  lastReading = (Measurement*)malloc(sizeof(Measurement));
  lastStationary = (Measurement*)malloc(sizeof(Measurement));
  
  // Create layout
  thisPage->layout = initLayout();
  thisPage->drawn = 0;
  
  RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * devicesbutton = initRectangleWindow(240, 190, 319, 239, BUTTON_SELECTED, BUTTON_BORDER);
  
  setText(homebutton, "Home");
  setText(learnbutton, "Learn");
  setText(graphbutton, "Graph");
  setText(devicesbutton, "Devices");
  
  // Add windows
  addWindow(thisPage->layout, homebutton);
  addWindow(thisPage->layout, learnbutton);
  addWindow(thisPage->layout, graphbutton);
  addWindow(thisPage->layout, devicesbutton);
  
  // Set onClick listeners
  setOnClick(homebutton, swapToMain);
  setOnClick(learnbutton, swapToLearning);
  setOnClick(graphbutton, swapToGraph);
  setOnClick(devicesbutton, lightLed);
  
  return thisPage;
}

Device * deviceInit(double activePower, double reactivePower, double harmonicPower, RectangleWindow * knap) {
  Device * device = (Device * ) malloc(sizeof(Device));
  
  device->activePower = activePower;
  device->reactivePower = reactivePower;
  device->harmonicPower = harmonicPower;
  device->devicebutton = knap;
  
  return device;
}

void addDevice(double activePower, double reactivePower, double harmonicPower){
  if (thisPage->layout->size >= 10) return;
  
  RectangleWindow * devicebutton = initRectangleWindow(mX, mY, mX+100, mY+50, DEVICE_OFF, BUTTON_BORDER);
  
  devices[size] = deviceInit(activePower, reactivePower, harmonicPower, devicebutton);
  
  // Update iterators
  size++;
  mY += 50;
  if (mY > 150){
	mY = 20;
	mX += 100;
  }
  
  addWindow(thisPage->layout, devicebutton);
}


void edgeDetection(double * lastVal, double * lastStatVal, double newVal, double tol) {

  
  
  
  
  

}


void checkDevices(Measurement * measurement, Page * currentPage){
  double tol = 5;
  
  double deltaP = fabs(measurement->P_power - lastReading->P_power);
  lastReading->P_power = measurement->P_power;
  
  if (deltaP >= tol){
	// Signal is no longer in steady state
	isStationary = 0;
  }
  else if (!isStationary){
	// Signal is now in steady state
	isStationary = 1;
	double dPst = measurement->P_power - lastStationary->P_power;
	char posChange = (dPst >= 0);
	
	dPst = fabs(dPst);
	
	char pTol = 3;
	char redraw = 0;
	
	// CHECK DEVICES
	for (int i = 0; i < size; i++){
	  if (devices[i]->activePower - pTol <= dPst  && dPst <= devices[i]->activePower + pTol){
		// This is the right device
		if (posChange){
		  if (devices[i]->devicebutton->backgroundColor != DEVICE_ON){
			devices[i]->devicebutton->backgroundColor = DEVICE_ON;
			redraw = 1;
		  }  
		}
		else{
		  if (devices[i]->devicebutton->backgroundColor != DEVICE_OFF){
			devices[i]->devicebutton->backgroundColor = DEVICE_OFF;
			redraw = 1;
		  }
		}
		if (redraw && currentPage == thisPage)	drawWindow(devices[i]->devicebutton);
	  }
	}
  }
  else{
	// Update steady state
	lastStationary->P_power = measurement->P_power;
  }
}


