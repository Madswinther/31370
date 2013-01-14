#include "learningpage.h"
#include "mainpage.h"

Graph * voltageGraph;
Graph * currentGraph;
Graph * powerGraph;
Graph * reactiveGraph;
Graph * activeGraph;

Page * thisPage;

Page * initGraphPage(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(*thisPage));
  
  // Create layout
  thisPage->layout = initLayout();
  thisPage->drawn = 0;
  
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
  voltageGraph = Graph_init(0, 0, 280, 180, 230, 240);
  currentGraph = Graph_init(0, 0, 280, 180, 0, 0.3);
  powerGraph = Graph_init(0, 0, 280, 180, 0, 50);
  activeGraph = voltageGraph;
  
  setText(homebutton, "Home");
  setText(learnbutton, "Learn");
  setText(graphbutton, "Graph");
  setText(button3, "About");
  
  // Add windows
  addWindow(thisPage->layout, homebutton);
  addWindow(thisPage->layout, learnbutton);
  addWindow(thisPage->layout, graphbutton);
  addWindow(thisPage->layout, button3);
  addWindow(thisPage->layout, voltagebutton);
  addWindow(thisPage->layout, currentbutton);
  addWindow(thisPage->layout, powerbutton);
  addWindow(thisPage->layout, reactivebutton);
  addWindow(thisPage->layout, voltageGraph);
  
  // Set onClick listeners
  setOnClick(homebutton, swapToMain);
  setOnClick(learnbutton, swapToLearning);
  setOnClick(graphbutton, lightLed);
  setOnClick(voltagebutton, changeToVoltage);
  setOnClick(currentbutton, changeToCurrent);
  setOnClick(powerbutton, changeToPower);
  
  return thisPage;
}

void updateGraphPage(Measurement * measurement, char draw){
  if (draw){
	Graph_addPoint(voltageGraph, activeGraph, measurement->voltage);
	Graph_addPoint(currentGraph, activeGraph, measurement->current);
	Graph_addPoint(powerGraph, activeGraph, measurement->P_power);
  }
  else{
	Graph_addPoint(voltageGraph, NULL, measurement->voltage);
	Graph_addPoint(currentGraph, NULL, measurement->current);
	Graph_addPoint(powerGraph, NULL, measurement->P_power);
  }
}

void changeToVoltage(){
  if (activeGraph != voltageGraph){
	activeGraph = voltageGraph;
	removeWindow(thisPage->layout);
	addWindow(thisPage->layout, voltageGraph);
	refreshGraph();
  }
}

void changeToCurrent(){
  if (activeGraph != currentGraph){
	activeGraph = currentGraph;
	removeWindow(thisPage->layout);
	addWindow(thisPage->layout, currentGraph);
	refreshGraph();
  }
}

void changeToPower(){
  if (activeGraph != powerGraph){
	activeGraph = powerGraph;
	removeWindow(thisPage->layout);
	addWindow(thisPage->layout, powerGraph);
	refreshGraph();
  }
}

void refreshGraph(){
  CLEAR_SCREEN();
  drawWindows(thisPage->layout);
}