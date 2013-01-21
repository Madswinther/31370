#include "includes.h"

Graph * voltageGraph;
Graph * currentGraph;
Graph * powerGraph;
Graph * activeGraph;

static Layout * thisLayout;

Layout * initGraphLayout(){
  // Alloc space
  thisLayout = (Layout*)malloc(sizeof(*thisLayout));
  
  // Create layout
  thisLayout = initLayout();
  
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
  addWindow(thisLayout, voltagebutton);
  addWindow(thisLayout, currentbutton);
  addWindow(thisLayout, powerbutton);
  addWindow(thisLayout, voltageGraph);
  
  // Set onClick listeners
  setOnClick(voltagebutton, changeToVoltage);
  setOnClick(currentbutton, changeToCurrent);
  setOnClick(powerbutton, changeToPower);
  
  return thisLayout;
}

void updateGraphLayout(Measurement * measurement, char draw){
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
	removeWindow(thisLayout);
	addWindow(thisLayout, voltageGraph);
	
	//change selected state
	setSelected(VOLTAGE_BUTTON);
	refreshGraph();
  }
}

void changeToCurrent(){
  if (activeGraph != currentGraph){
	activeGraph = currentGraph;
	removeWindow(thisLayout);
	addWindow(thisLayout, currentGraph);
	
	//change selected state
	setSelected(CURRENT_BUTTON);
	refreshGraph();
  }
}

void changeToPower(){
  if (activeGraph != powerGraph){
	activeGraph = powerGraph;
	removeWindow(thisLayout);
	addWindow(thisLayout, powerGraph);
	
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
	  ((RectangleWindow*)thisLayout->windows[button])->backgroundColor = BUTTON_SELECTED;
	}
	else{
	  ((RectangleWindow*)thisLayout->windows[i])->backgroundColor = BUTTON_BACKGROUND;
	}
	drawWindow(thisLayout->windows[i]);
  }
  
}

void refreshGraph(){
  drawWindows(thisLayout);
}