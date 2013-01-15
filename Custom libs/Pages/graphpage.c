#include "learningpage.h"
#include "mainpage.h"

Graph * voltageGraph;
Graph * currentGraph;
Graph * powerGraph;
Graph * activeGraph;

static Page * thisPage;

Page * initGraphPage(){
  // Alloc space
  thisPage = (Page*)malloc(sizeof(*thisPage));
  
  // Create layout
  thisPage->layout = initLayout();
  thisPage->drawn = 0;
  
  // Default buttons
  RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * devicesbutton = initRectangleWindow(240, 190, 319, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  
  // Buttons for changing graph window
  RectangleWindow * voltagebutton = initRectangleWindow(285, 10, 320, 45, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * currentbutton = initRectangleWindow(285, 60, 320, 95, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * powerbutton = initRectangleWindow(285, 110, 320, 145, BUTTON_BACKGROUND, BUTTON_BORDER);
  setText(voltagebutton, "V");
  setText(currentbutton, "I");
  setText(powerbutton, "P");
  
  // Setup Graph
  voltageGraph = Graph_init(0, 0, 280, 180, 230, 240);
  currentGraph = Graph_init(0, 0, 280, 180, 0, 0.3);
  powerGraph = Graph_init(0, 0, 280, 180, 0, 50);
  activeGraph = voltageGraph;
  
  setText(homebutton, "Home");
  setText(learnbutton, "Learn");
  setText(graphbutton, "Graph");
  setText(devicesbutton, "Devices");
  
  // Add windows
  addWindow(thisPage->layout, homebutton);
  addWindow(thisPage->layout, learnbutton);
  addWindow(thisPage->layout, graphbutton);
  addWindow(thisPage->layout, devicesbutton);
  addWindow(thisPage->layout, voltagebutton);
  addWindow(thisPage->layout, currentbutton);
  addWindow(thisPage->layout, powerbutton);
  addWindow(thisPage->layout, voltageGraph);
  
  // Set onClick listeners
  setOnClick(homebutton, swapToMain);
  setOnClick(learnbutton, swapToLearning);
  setOnClick(graphbutton, lightLed);
  setOnClick(devicesbutton, swapToDevices);
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
	
	//change selected state
	setSelected(VOLTAGE_BUTTON);
	refreshGraph();
  }
}

void changeToCurrent(){
  if (activeGraph != currentGraph){
	activeGraph = currentGraph;
	removeWindow(thisPage->layout);
	addWindow(thisPage->layout, currentGraph);
	
	//change selected state
	setSelected(CURRENT_BUTTON);
	refreshGraph();
  }
}

void changeToPower(){
  if (activeGraph != powerGraph){
	activeGraph = powerGraph;
	removeWindow(thisPage->layout);
	addWindow(thisPage->layout, powerGraph);
	
	//change selected state
	setSelected(POWER_BUTTON);
	refreshGraph();
  }
}

static void setSelected(int button){
  // Reset backgroundcolor for all graph-buttons
  for (int i=4; i<7; i++){
	if (i == button){
	  // Set a specific graph button to display the selected state
	  ((RectangleWindow*)thisPage->layout->windows[button])->backgroundColor = BUTTON_SELECTED;
	}
	else{
	  ((RectangleWindow*)thisPage->layout->windows[i])->backgroundColor = BUTTON_BACKGROUND;
	}
	drawWindow(thisPage->layout->windows[i]);
  }
  
}

void refreshGraph(){
  CLEAR_SCREEN();
  drawWindows(thisPage->layout);
}