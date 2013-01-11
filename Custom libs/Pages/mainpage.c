#include "mainpage.h"
#include "../layout.h"

Page * initMainPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	RectangleWindow * button = initRectangleWindow(0, 190, 100, 240, 0xFF00FF, 0x0000FF);
	RectangleWindow * button2 = initRectangleWindow(100, 190, 200, 240, 0xFFFF00, 0x0000FF);
	
	// Add windows
	addWindow(temp->layout, button);
	addWindow(temp->layout, button2);
	
	// Set onClick listeners
	setOnClick(button, lightLed);
	setOnClick(button2, swapToLearning);
	
	return temp;
}

void swapToLearning(){
  	// 1 means LearningPage
	swapToPage(1);
}

void lightLed(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;    
}