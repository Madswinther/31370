#include "learningpage.h"
#include "mainpage.h"

Page * initGraphPage(){
	// Alloc space
	Page * temp;
	temp = (Page*)malloc(sizeof(*temp));
	
	// Create layout
	temp->layout = initLayout();
	temp->drawn = 0;
	
	int backgroundColor = 0x000000;
	
	// Default buttons
	RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, backgroundColor, 0x0000FF);
	RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, backgroundColor, 0x0000FF);
	RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, backgroundColor, 0x0000FF);
	RectangleWindow * button3 = initRectangleWindow(240, 190, 319, 239, backgroundColor, 0x0000FF);
	
	// Buttons for changing graph window
	RectangleWindow * voltagebutton = initRectangleWindow(285, 10, 320, 45, backgroundColor, 0x0000FF);
	RectangleWindow * currentbutton = initRectangleWindow(285, 50, 320, 85, backgroundColor, 0x0000FF);
	RectangleWindow * powerbutton = initRectangleWindow(285, 90, 320, 125, backgroundColor, 0x0000FF);
	RectangleWindow * reactivebutton = initRectangleWindow(285, 130, 320, 165, backgroundColor, 0x0000FF);
	setText(voltagebutton, "V");
	setText(currentbutton, "I");
	setText(powerbutton, "P");
	setText(reactivebutton, "Q");
	
	// Setup Graph
	Graph * graph = Graph_init(0,0,280, 180);
	Graph_xlim(graph, 0, 5);
	Graph_ylim(graph, 220, 240);
	
	setText(homebutton, "Home");
	setText(learnbutton, "Learn");
	setText(graphbutton, "Graph");
	setText(button3, "About");
  
	// Add windows
	addWindow(temp->layout, homebutton);
	addWindow(temp->layout, learnbutton);
	addWindow(temp->layout, graphbutton);
	addWindow(temp->layout, button3);
	addWindow(temp->layout, graph);
	addWindow(temp->layout, voltagebutton);
	addWindow(temp->layout, currentbutton);
	addWindow(temp->layout, powerbutton);
	addWindow(temp->layout, reactivebutton);
	
	// Set onClick listeners
	setOnClick(homebutton, swapToMain);
	setOnClick(learnbutton, swapToLearning);
	setOnClick(graphbutton, lightLed);
	
	return temp;
}
