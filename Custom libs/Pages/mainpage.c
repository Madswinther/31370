#include "mainpage.h"
#include "includes.h"


Page * initMainPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	
	
	RectangleWindow * welcome = initRectangleWindow(250, 0, 317, 50, BUTTON_SELECTED, BUTTON_BORDER);
	
	setText(welcome, "Welcome!");
  
	// Add windows
	addWindow(temp->layout, welcome);
	
	return temp;
}