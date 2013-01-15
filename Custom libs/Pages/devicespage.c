#include "devicespage.h"
#include "mainpage.h"
#include "includes.h"

static Page * thisPage;

// Iterators to allow for adding devices
static char size = 0;
static short mX = 20;
static short mY = 20;

Page * initDevicesPage(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(*thisPage));
  
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

void addDevice(){
  RectangleWindow * devicebutton = initRectangleWindow(mX, mY, mX+100, mY+50, DEVICE_OFF, BUTTON_BORDER);
  setText(devicebutton, "1");
  
  // Update iterators
  size++;
  mY += 50;
  if (mY > 150){
	mY = 20;
	mX += 100;
  }
  
  addWindow(thisPage->layout, devicebutton);
  drawWindow(devicebutton);
}


