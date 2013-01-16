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
static char edgeDetected = 0;
static char steadyDetected = 0;

Page * initDevicesPage(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(*thisPage));
  lastReading = (Measurement*)malloc(sizeof(Measurement));
  lastStationary = (Measurement*)malloc(sizeof(Measurement));
  
  // Init to zero
  lastReading->P_power = 0;
  lastReading->Q_power = 0;
  lastReading->H_power = 0;
  lastStationary->P_power = 0;
  lastStationary->Q_power = 0;
  lastStationary->H_power = 0;
  
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
  
  RectangleWindow * devicebutton = initRectangleWindow(mX, mY, mX+100, mY+50, DEVICE_ON, BUTTON_BORDER);
  
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



char edgeDetection(double compareVal, double newVal, double tol) {
  
  // Calculate change
  double delta = fabs(newVal - compareVal);
  
  if (delta >= tol){
	// Signal is no longer in steady state
	return 1;
  }
  else{
	// Signal is now in steady state
	return 0;
  }
  
}


void checkDevices(Measurement * measurement, Page * currentPage){
  
  // Detect errors
  if (measurement->P_power > 1000 || measurement->Q_power > 1000 || measurement->H_power > 1000){
	return;
  }
  
  if (!edgeDetected){
	edgeDetected = edgeDetection(lastStationary->P_power, measurement->P_power, 5);
	edgeDetected |= edgeDetection(lastStationary->Q_power, measurement->Q_power, 5);
	edgeDetected |= edgeDetection(lastStationary->H_power, measurement->H_power, 5);
	lastReading->P_power = measurement->P_power;
	return;
  }
  // A step input has occured, wait for a steady state before checking again
  
  
  steadyDetected = !edgeDetection(lastReading->P_power, measurement->P_power, 0.05);
  steadyDetected &= !edgeDetection(lastReading->Q_power, measurement->Q_power, 0.2);
  steadyDetected &= !edgeDetection(lastReading->H_power, measurement->H_power, 0.2);
  if (steadyDetected){
	// Stationary state entered, allow checking for edges once again
	edgeDetected = 0;
	steadyDetected = 0;
	
	double dPst = measurement->P_power - lastStationary->P_power;
	double dQst = measurement->Q_power - lastStationary->Q_power;
	double dHst = measurement->H_power - lastStationary->H_power;
	char posChange = (dPst >= 0);
	
	dPst = fabs(dPst);
	dQst = fabs(dQst);
	dHst = fabs(dHst);
	
	//printf("%0.2f\n", dHst);
	
	char checking = 1;
	double pTol = 0.5;
	char redraw = 0;
	while (checking){ 
	  // CHECK DEVICES
	  for (int i = 0; i < size; i++){
		redraw = 0;
		if (devices[i]->activePower - pTol <= dPst  && dPst <= devices[i]->activePower + pTol){
		  // P matches
		  if (devices[i]->reactivePower - pTol <= dQst  && dQst <= devices[i]->reactivePower + pTol){
			// Q matches
			//if (devices[i]->harmonicPower - pTol*2 <= dHst  && dHst <= devices[i]->harmonicPower + pTol*2){
			// H matches
			if (posChange){
			  if (devices[i]->devicebutton->backgroundColor != DEVICE_ON){
				devices[i]->devicebutton->backgroundColor = DEVICE_ON;
				redraw = 1;
				checking = 0;
			  }  
			}
			else{
			  if (devices[i]->devicebutton->backgroundColor != DEVICE_OFF){
				devices[i]->devicebutton->backgroundColor = DEVICE_OFF;
				redraw = 1;
				checking = 0;
			  }
			}
			if (redraw && currentPage == thisPage)	drawWindow(devices[i]->devicebutton);
		  //}
		  }
		}
	  }
	  pTol += 0.5;
	  if (pTol >= 2.0) checking = 0;
	}
	lastStationary->P_power = measurement->P_power;
	lastStationary->Q_power = measurement->Q_power;
	lastStationary->H_power = measurement->H_power;
  }
  lastReading->P_power = measurement->P_power;
  lastReading->Q_power = measurement->Q_power;
  lastReading->H_power = measurement->H_power;
}


