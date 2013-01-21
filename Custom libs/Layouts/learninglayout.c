#include "includes.h"
#include <math.h>

ProgressBar * pb;

Layout * initLearningLayout(){
  // Alloc space
  Layout * temp;
  temp = (Layout*)malloc(sizeof(*temp));
  
  // Create layout
  temp = Layout_initLayout();
  
  RectangleWindow * beginlearning = GUI_initRectangleWindow(90, 50, 230, 100, BUTTON_BACKGROUND, BUTTON_BORDER);
  pb = ProgressBar_Init(10, 105, 300, 55, 0xFF0000, 0x3F3F3F);
  
  GUI_setText(beginlearning, "Start Learning");
  
  // Add windows
  Layout_addWindow(temp, beginlearning);
  Layout_addWindow(temp, pb);
  
  // Set onClick listeners
  GUI_setOnClick(beginlearning, doLearn);
  
  return temp;
}

void doLearn(){
  if (!isAnimating()){
	postAnimation(pb, 4, 0, ProgressBar_Update);
	GLCD_SetWindow(0, 0, 150, 50);  
	GLCD_TextSetPos(0,0);
	GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
	
	Measurement measurement;
	char N = 0;
	double activePower = 0;
	double reactivePower = 0;
	double harmonicPower = 0;
	
	while(isAnimating()){
	  // Data from UART0
	  UART_Check(Buffer);
	  
	  if (Buffer[0] != 'E'){
		Parsing_parse(Buffer, &measurement);
		N++;
		
		// Sum of all measurements
		activePower += measurement.P_power;
		reactivePower += measurement.Q_power;
		harmonicPower += measurement.H_power;
	  }
	}
	
	// Calculate average values
	activePower = activePower / (double) N;
	reactivePower = reactivePower / (double) N;
	harmonicPower = harmonicPower / (double) N;
	
	// Add device to devices screen
	addDevice(activePower, reactivePower, harmonicPower);
  }
}

void lightLedd(){
  USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;   
}