#include "includes.h"


Layout * initMainLayout(){
	// Alloc space
	Layout * temp;
	temp = (Layout*)malloc(sizeof(*temp));
	
	// Create layout
	temp = initLayout();
	
	RectangleWindow * welcome = initRectangleWindow(250, 0, 317, 50, BUTTON_SELECTED, BUTTON_BORDER);
	
	setText(welcome, "Welcome!");
  
	// Add windows
	addWindow(temp, welcome);
	
	return temp;
}