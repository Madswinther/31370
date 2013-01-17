#include "navigationbar.h"
#include "includes.h"

static Page * thisPage;

Page * initNavigationBar(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(Page));
  
  // Create layout
  thisPage->layout = initLayout();
  thisPage->drawn = 0;
  
  RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * devicesbutton = initRectangleWindow(240, 190, 319, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  
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
  setOnClick(devicesbutton, swapToDevices);
  
  return thisPage;
}

void swapToMain(){
  setSelected(0);
  swapToPage(0);
}

void swapToLearning(){
  // 1 means LearningPage
  setSelected(1);
  swapToPage(1);
}

void swapToGraph(){
  setSelected(2);
  swapToPage(2);
}

void swapToDevices(){
  setSelected(3);
  swapToPage(3);
}

static void setSelected(int button){
  // Reset backgroundcolor for all navigation-buttons
  for (int i=0; i<4; i++){
	if (i == button){
	  // Set a specific graph button to display the selected state
	  ((RectangleWindow*)thisPage->layout->windows[button])->backgroundColor = BUTTON_SELECTED;
	}
	else{
	  ((RectangleWindow*)thisPage->layout->windows[i])->backgroundColor = BUTTON_BACKGROUND;
	}
  }
}