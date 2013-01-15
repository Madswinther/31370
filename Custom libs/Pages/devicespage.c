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
static char step = 0;

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

void checkDevices(Measurement * measurement, Page * currentPage){
  double tol = 15;
  
  if (step == 0){
	if(measurement->P_power - lastStationary->P_power > 10){
	  step = 1;
	}
	else{
	  return;
	}
  }
  
  double signature = measurement->P_power+measurement->Q_power+measurement->H_power;
  double lastReadingSignature = lastReading->P_power+lastReading->Q_power+lastReading->H_power;
  if (!(lastReadingSignature - tol <= signature && signature <= lastReadingSignature + tol)){
	// NOT STATIONARY YET
	printf("n\n");
	lastReading->P_power = measurement->P_power;
	return;
  }
  printf("s\n");
  
  // Stationary - proceed accordingly  
  double deltaP = measurement->P_power - lastStationary->P_power;
  
  step = 0;
  
  // Save last measurements
  lastStationary = measurement;
  lastReading = measurement;
  
  printf("%.2f\n", deltaP);
  
  
  // Start off with a small margin of error
  double pTol = 1;
  char redraw = 0;
  
  for (int i = 0; i < size; i++){
	if (devices[i]->activePower - pTol <= deltaP  && deltaP <= devices[i]->activePower + pTol){
	  // This is the right device
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


