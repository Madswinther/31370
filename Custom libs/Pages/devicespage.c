#include "devicespage.h"
#include "mainpage.h"
#include "includes.h"
#include <math.h>

static Page * thisPage;
static Device * devices[6];

// Iterators to allow for adding devices
static char size = 0;
static short mX = 20;
static short mY = 60;

// Holder for comparison of measurements
static Measurement * lastReading;
static Measurement * lastStationary;
static char edgeDetected = 0;
static char steadyDetected = 0;

// ProgressSpinner
static ProgressSpinner * pSpinner;

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
  
  RectangleWindow * clearbutton = initRectangleWindow(110, 5, 210, 55, BUTTON_BACKGROUND, BUTTON_BORDER);
  pSpinner = ProgressSpinnerInit(258, 0, 60, 0xFFFFFF);
  
  setText(clearbutton, "Clear Devices");
  setOnClick(clearbutton, clearDevices);
  
  addWindow(thisPage->layout, clearbutton);
  //addWindow(thisPage->layout, pSpinner);
  
  return thisPage;
}


Device * deviceInit(double activePower, double reactivePower, double harmonicPower, RectangleWindow * window) {
  // Initialiaze a new device given average values and a pointer to a Window.
  Device * device = (Device * ) malloc(sizeof(Device));
  
  device->activePower = activePower;
  device->reactivePower = reactivePower;
  device->harmonicPower = harmonicPower;
  device->devicebutton = window;
  
  return device;
}

void addDevice(double activePower, double reactivePower, double harmonicPower){
  // Do not exceed the allocated space
  if (thisPage->layout->size >= 10) return;
  
  // Check if button has existed at some point in the past
  if (devices[size] != NULL){
	// It did - update it
	devices[size]->activePower = activePower;
	devices[size]->reactivePower = reactivePower;
	devices[size]->harmonicPower = harmonicPower;
	
	// The button should be in the ON state by default
	devices[size]->devicebutton->backgroundColor = DEVICE_ON;
	
	// show it again without drawing it right away
	devices[size]->devicebutton->hidden = 0;
  }
  else{
  	// Init Window and add it to the array of devices
  	RectangleWindow * devicebutton = initRectangleWindow(mX, mY, mX+50, mY+50, DEVICE_ON, BUTTON_BORDER);
  	devices[size] = deviceInit(activePower, reactivePower, harmonicPower, devicebutton);
	addWindow(thisPage->layout, devicebutton);
  }
  
  // Update iterators
  size++;
  mY += 50;
  if (mY > 150){
	mY = 60;
	mX += 50;
  }
}

void clearDevices(){
  for (int i = 0; i<size; i++){
	// Hide the devices and decrement size
	setHidden(devices[i]->devicebutton, 1);
  }
  size = 0;
  mX = 20;
  mY = 60;
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
	// No step input detected yet. Keep scanning for one
	edgeDetected = edgeDetection(lastStationary->P_power, measurement->P_power, 5);
	edgeDetected |= edgeDetection(lastStationary->Q_power, measurement->Q_power, 5);
	edgeDetected |= edgeDetection(lastStationary->H_power, measurement->H_power, 5);
	lastReading->P_power = measurement->P_power;
	return;
  }
  
  // Notify user that a step input is being processsed
  if (currentPage == thisPage){
  	pSpinner->cancelled = 0;
	
	// The ProgressSpinner uses an internal count. No need to pass starting value
	// and increment to it
  	postAnimation(pSpinner, 0, 0, ProgressSpinnerUpdate);
  }
  
  // A step input has occured, wait for a steady state before checking again
  steadyDetected = !edgeDetection(lastReading->P_power, measurement->P_power, 0.05);
  steadyDetected &= !edgeDetection(lastReading->Q_power, measurement->Q_power, 0.2);
  steadyDetected &= !edgeDetection(lastReading->H_power, measurement->H_power, 0.2);
  if (steadyDetected){
	
	// Stationary state entered, start checking for next edge
	edgeDetected = 0;
	steadyDetected = 0;
	
	// Compute the changes in P, Q and H
	double dPst = measurement->P_power - lastStationary->P_power;
	double dQst = measurement->Q_power - lastStationary->Q_power;
	double dHst = measurement->H_power - lastStationary->H_power;
	
	// Does this signify a device turning on or off?
	char posChange = (dPst >= 0);
	
	// Get the absolute change in P, Q and H
	dPst = fabs(dPst);
	dQst = fabs(dQst);
	dHst = fabs(dHst);
	
	// Init conditional and tolerance variables
	char checking = 1;
	double pTol = 0.5;
	char redraw = 0;
	
	// CHECK DEVICES
	while (checking){ 
	  for (int i = 0; i < size; i++){
		redraw = 0;
		if (devices[i]->activePower - pTol <= dPst  && dPst <= devices[i]->activePower + pTol){
		  // P matches
		  if (devices[i]->reactivePower - pTol <= dQst  && dQst <= devices[i]->reactivePower + pTol){
			// Q matches
			if (devices[i]->harmonicPower - pTol <= dHst  && dHst <= devices[i]->harmonicPower + pTol){			
			  // H matches
			  if (posChange){
				// This device has been turned ON! Switch it on graphically if needed
				if (devices[i]->devicebutton->backgroundColor != DEVICE_ON){
				  devices[i]->devicebutton->backgroundColor = DEVICE_ON;
				  redraw = 1;
				  checking = 0;
				}  
			  }
			  else{
				// This device has been turned OFF! Switch it off graphically if needed
				if (devices[i]->devicebutton->backgroundColor != DEVICE_OFF){
				  devices[i]->devicebutton->backgroundColor = DEVICE_OFF;
				  redraw = 1;
				  checking = 0;
				}
			  }
			  // Window might need a redraw if its backgroundcolor has changed
			  if (redraw && currentPage == thisPage)	drawWindow(devices[i]->devicebutton);
			}
		  }
		}
	  }
	  // No device has been accepted as the cause of the step. Increase tolerance and go again.
	  pTol += 0.5;
	  
	  // Don't increase tolerance beyond a sensible value - 
	  // doing so might cause a wrong device to be accepted
	  if (pTol >= 4.0) checking = 0;
	}
	
	// Update the last stationary values
	(*lastStationary) = (*measurement);
	
	// Special case is all devices turned off - this would register as a power below 1 watt
	if (measurement->P_power < 1.0){
	  for (int i = 0; i < size; i++){
		if (devices[i]->devicebutton->backgroundColor != DEVICE_OFF){
		  devices[i]->devicebutton->backgroundColor = DEVICE_OFF;
		  drawWindow(devices[i]->devicebutton);
		}
	  }
	}
	
	// Stop animation
	pSpinner->cancelled = 1;
  }
  
  // Update the last read values
  (*lastReading) = (*measurement);
}


