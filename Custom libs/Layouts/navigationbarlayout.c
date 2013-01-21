#include "includes.h"

static Layout * thisLayout;

Layout * initNavigationBar(){
  // Alloc space
  thisLayout = (Layout*)malloc(sizeof(Layout));
  
  // Create layout
  thisLayout = initLayout();
  
  RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * devicesbutton = initRectangleWindow(240, 190, 319, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  
  setText(homebutton, "Home");
  setText(learnbutton, "Learn");
  setText(graphbutton, "Graph");
  setText(devicesbutton, "Devices");
  
  // Add windows
  addWindow(thisLayout, homebutton);
  addWindow(thisLayout, learnbutton);
  addWindow(thisLayout, graphbutton);
  addWindow(thisLayout, devicesbutton);
  
  // Set onClick listeners
  setOnClick(homebutton, swapToMain);
  setOnClick(learnbutton, swapToLearning);
  setOnClick(graphbutton, swapToGraph);
  setOnClick(devicesbutton, swapToDevices);
  
  return thisLayout;
}

void swapToMain(){
  setSelected(0);
  swapToLayout(0);
}

void swapToLearning(){
  // 1 means LearningLayout
  setSelected(1);
  swapToLayout(1);
}

void swapToGraph(){
  setSelected(2);
  swapToLayout(2);
}

void swapToDevices(){
  setSelected(3);
  swapToLayout(3);
}

static void setSelected(int button){
  // Reset backgroundcolor for all navigation-buttons
  for (int i=0; i<4; i++){
	if (i == button){
	  // Set a specific graph button to display the selected state
	  ((RectangleWindow*)thisLayout->windows[button])->backgroundColor = BUTTON_SELECTED;
	}
	else{
	  ((RectangleWindow*)thisLayout->windows[i])->backgroundColor = BUTTON_BACKGROUND;
	}
  }
}