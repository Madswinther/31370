#include "learningpage.h"
#include "mainpage.h"

Page * initLearningPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	
	int backgroundColor = rgbToHex(100, 100, 100);
	
	RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 240, backgroundColor, 0x0000FF);
	RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 240, backgroundColor, 0x0000FF);
	RectangleWindow * button2 = initRectangleWindow(160, 190, 240, 240, backgroundColor, 0x0000FF);
	RectangleWindow * button3 = initRectangleWindow(240, 190, 320, 240, backgroundColor, 0x0000FF);
	ProgressBar * pb = ProgressBarInit(0, 50, 240, 50, 0xFF0000, 0xFF00FF);
  
	// Add windows
	addWindow(temp->layout, homebutton);
	addWindow(temp->layout, learnbutton);
	addWindow(temp->layout, button2);
	addWindow(temp->layout, button3);
	addWindow(temp->layout, pb);
	
	// Set onClick listeners
	setOnClick(homebutton, swapToMain);
	setOnClick(learnbutton, lightLedd);
	
	return temp;
}

void swapToMain(){
	swapToPage(0);
}

void lightLedd(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;   
}