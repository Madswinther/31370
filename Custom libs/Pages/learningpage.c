#include "learningpage.h"
#include "mainpage.h"
#include "includes.h"

ProgressBar * pb;

Page * initLearningPage(){
  // Alloc space
  Page * temp;
  temp = (Page*)malloc(sizeof(*temp));
  
  // Create layout
  temp->layout = initLayout();
  temp->drawn = 0;
  
  RectangleWindow * homebutton = initRectangleWindow(0, 190, 80, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * learnbutton = initRectangleWindow(80, 190, 160, 239, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * graphbutton = initRectangleWindow(160, 190, 240, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * button3 = initRectangleWindow(240, 190, 319, 239, BUTTON_BACKGROUND, BUTTON_BORDER);
  RectangleWindow * beginlearning = initRectangleWindow(90, 50, 230, 100, BUTTON_BACKGROUND, BUTTON_BORDER);
  pb = ProgressBarInit(10, 105, 300, 55, 0xFF0000, 0x3F3F3F);
  
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
  if (!isAnimating()){
	postAnimation(pb, 1, 0, ProgressBarUpdate);
	GLCD_SetWindow(0, 0, 150, 50);  
	GLCD_TextSetPos(0,0);
	GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
	
	Measurement measurement;
	char position = 0;
	double voltagesum = 0;
	double powersum = 0;
	
	while(isAnimating()){
	  // Data from UART0
	  UartCheck(Buffer);
	  
	  if (Buffer[0] != 'E'){
		parse(Buffer, &measurement);
		position++;
		powersum += measurement.P_power;
		voltagesum += measurement.voltage;
	  }
	}
	
	// End of learning
	//double stationary_act_power = sum/(double)position;
	double avg_volt = voltagesum/(double)position;
	double avg_power = powersum/(double)position;
	
	double impedance = (avg_volt*avg_volt)*(1/avg_power);
	GLCD_print("z = %f", impedance);
  }
}

void lightLedd(){
  USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;   
}