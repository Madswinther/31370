#include "mainpage.h"
#include "includes.h"


Page * initMainPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	
	int backgroundColor = 0x000000;
	
	RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, backgroundColor, 0x0000FF);
	RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, backgroundColor, 0x0000FF);
	RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, backgroundColor, 0x0000FF);
	RectangleWindow * button3 = initRectangleWindow(240, 190, 319, 239, backgroundColor, 0x0000FF);
	
	setText(homebutton, "Home");
	setText(learnbutton, "Learn");
	setText(graphbutton, "Graph");
	setText(button3, "About");
  
	// Add windows
	addWindow(temp->layout, homebutton);
	addWindow(temp->layout, learnbutton);
	addWindow(temp->layout, graphbutton);
	addWindow(temp->layout, button3);
	
	// Set onClick listeners
	setOnClick(homebutton, lightLed);
	setOnClick(learnbutton, swapToLearning);
	setOnClick(graphbutton, swapToGraph);
	
	return temp;
}

void swapToLearning(){
  	// 1 means LearningPage
	swapToPage(1);
}

void swapToMain(){
	swapToPage(0);
}

void swapToGraph(){
	swapToPage(2);
}

void lightLed(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;    
}