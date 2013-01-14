#include "learningpage.h"
#include "mainpage.h"

ProgressBar * pb;

Page * initLearningPage(){
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
	RectangleWindow * beginlearning = initRectangleWindow(90, 50, 230, 100, backgroundColor, 0x0000FF);
	pb = ProgressBarInit(10, 105, 300, 55, 0xFF0000, 0xFF00FF);
	
	setText(homebutton, "Home");
	setText(learnbutton, "Learn");
	setText(graphbutton, "Graph");
	setText(button3, "About");
	setText(beginlearning, "Start Learning");
  
	// Add windows
	addWindow(temp->layout, homebutton);
	addWindow(temp->layout, learnbutton);
	addWindow(temp->layout, graphbutton);
	addWindow(temp->layout, button3);
	addWindow(temp->layout, beginlearning);
	addWindow(temp->layout, pb);
	
	// Set onClick listeners
	setOnClick(homebutton, swapToMain);
	setOnClick(learnbutton, lightLed);
	setOnClick(graphbutton, swapToGraph);
	setOnClick(beginlearning, doLearn);
	
	return temp;
}

void doLearn(){
  postAnimation(pb, 0, ProgressBarUpdate);
}

void lightLedd(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;   
}