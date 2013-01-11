#include "learningpage.h"
#include "mainpage.h"
#include "../layout.h"

Page * initLearningPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	RectangleWindow * button = initRectangleWindow(0, 100, 100, 150, 0xFF00FF, 0x0000FF);
	RectangleWindow * button2 = initRectangleWindow(100, 100, 200, 150, 0xFFFF00, 0x0000FF);
	
	// Add windows
	addWindow(temp->layout, button);
	addWindow(temp->layout, button2);
	
	// Set onClick listeners
	setOnClick(button, swapToMain);
	setOnClick(button2, lightLedd);
	
	return temp;
}

void swapToMain(){
	swapToPage(0);
}

void lightLedd(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;   
}