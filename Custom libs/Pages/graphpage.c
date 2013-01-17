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
  
  // Buttons for changing graph window
  RectangleWindow * voltagebutton = initRectangleWindow(285, 10, 320, 45, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * currentbutton = initRectangleWindow(285, 60, 320, 95, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * powerbutton = initRectangleWindow(285, 110, 320, 145, BUTTON_BACKGROUND, BUTTON_BORDER);
  setText(voltagebutton, "V");
  setText(currentbutton, "I");
  setText(powerbutton, "P");
  
  // Setup Graph
  voltageGraph = Graph_init(0, 0, 280, 180, 230, 240);
  currentGraph = Graph_init(0, 0, 280, 180, 0, 1);
  powerGraph = Graph_init(0, 0, 280, 180, 0, 100);
  activeGraph = voltageGraph;
 
  // Add windows
  addWindow(thisPage->layout, voltagebutton);
  addWindow(thisPage->layout, currentbutton);
  addWindow(thisPage->layout, powerbutton);
  addWindow(thisPage->layout, voltageGraph);
  
  // Set onClick listeners
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
  for (int i=0; i<3; i++){
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
  drawWindows(thisPage->layout);
}