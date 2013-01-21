#include "includes.h"


Layout * initMainLayout(){
	// Alloc space
	Layout * temp;
	temp = (Layout*)malloc(sizeof(*temp));
	
	// Create layout
	temp = Layout_initLayout();
	
	RectangleWindow * welcome = GUI_initRectangleWindow(250, 0, 317, 50, BUTTON_SELECTED, BUTTON_BORDER);
	
	GUI_setText(welcome, "Welcome!");
  
	// Add windows
	Layout_addWindow(temp, welcome);
	
	return temp;
}