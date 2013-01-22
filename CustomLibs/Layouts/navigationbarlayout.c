#include "includes.h"

static Layout * thisLayout;

Layout * initNavigationBar(){
  // Alloc space
  thisLayout = (Layout*)malloc(sizeof(Layout));
  
  // Create layout
  thisLayout = Layout_initLayout();
  
  RectangleWindow * homebutton = GUI_initRectangleWindow(0, 190, 80, 239, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * learnbutton = GUI_initRectangleWindow(80, 190, 160, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * graphbutton = GUI_initRectangleWindow(160, 190, 240, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * devicesbutton = GUI_initRectangleWindow(240, 190, 319, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  
  GUI_setText(homebutton, "Home");
  GUI_setText(learnbutton, "Learn");
  GUI_setText(graphbutton, "Graph");
  GUI_setText(devicesbutton, "Devices");
  
  // Add windows
  Layout_addWindow(thisLayout, homebutton);
  Layout_addWindow(thisLayout, learnbutton);
  Layout_addWindow(thisLayout, graphbutton);
  Layout_addWindow(thisLayout, devicesbutton);
  
  // Set onClick listeners
  GUI_setOnClick(homebutton, swapToMain);
  GUI_setOnClick(learnbutton, swapToLearning);
  GUI_setOnClick(graphbutton, swapToGraph);
  GUI_setOnClick(devicesbutton, swapToDevices);
  
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