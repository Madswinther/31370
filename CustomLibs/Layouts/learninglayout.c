#include "includes.h"
#include <math.h>

static char letterHolder[] = {97,'\0'};
static char wordHolder[] = {32, 32, 32, 32, '\0'};
static char index = 0;
static char timeout = 0;

static Layout * thisLayout;

Layout * initLearningLayout(){
  // Alloc space
  thisLayout = (Layout*)malloc(sizeof(Layout));
  
  // Create layout
  thisLayout = Layout_initLayout();
  
  // Create progressbar
  ProgressBar * pb = ProgressBar_Init(5, 125, 310, 50, 0xFF0000, 0x3F3F3F);
  
  // User text input
  PictureWindow * next = GUI_initPictureWindow(183, 4, 233, 55, &nextPic);
  PictureWindow * previous = GUI_initPictureWindow(85, 4, 135, 55, &previousPic);
  RectangleWindow * letter = GUI_initRectangleWindow(135, 5, 185, 55, BUTTON_SELECTED, BUTTON_BORDER);
  RectangleWindow * word = GUI_initRectangleWindow(85, 55, 235, 105, BUTTON_BACKGROUND, BUTTON_BORDER);
  
  // Set text of windows
  GUI_setText(letter, letterHolder);
  GUI_setText(word, wordHolder);
  
  // Add windows
  Layout_addWindow(thisLayout, pb);
  Layout_addWindow(thisLayout, next);
  Layout_addWindow(thisLayout, previous);
  Layout_addWindow(thisLayout, letter);
  Layout_addWindow(thisLayout, word);
  
  // Set onClick listeners
  GUI_setOnClick(word, doLearn);
  GUI_setOnClick(next, nextLetter);
  GUI_setOnClick(previous, previousLetter);
  GUI_setOnClick(letter, addToWord);
  
  return thisLayout;
}

void doLearn(){
  if (!Animation_isRunning()){
	Animation_post(Layout_getWindow(thisLayout, 0), 4, 0, ProgressBar_Update);
	GLCD_SetWindow(0, 0, 150, 50);  
	GLCD_TextSetPos(0,0);
	GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
	
	Measurement measurement;
	char N = 0;
	double activePower = 0;
	double reactivePower = 0;
	double harmonicPower = 0;
	
	while(Animation_isRunning()){
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
	addDevice(wordHolder, activePower, reactivePower, harmonicPower);
	
	// Reset learning layout
	resetAll();
  }
}

static void nextLetter(){
  if (timeout == 0){
	timeout = 1;
	Animation_post(NULL, 1, 0, resetTimeout);
	// Iterate through ASCII table. Only allow small letters and numbers 0 to 9
	letterHolder[0]++;
	if (letterHolder[0] == 58){
	  letterHolder[0] = 97;
	}
	else if (letterHolder[0] == 123){
	  letterHolder[0] = 48;
	}
	
	// Redraw window
	GUI_drawWindow(Layout_getWindow(thisLayout, 3));
  }
}

static void previousLetter(){
  if (timeout == 0){
	timeout = 1;
	Animation_post(NULL, 1, 0, resetTimeout);
	// Iterate through ASCII table. Only allow small letters and numbers 0 to 9
	letterHolder[0]--;
	if (letterHolder[0] == 96){
	  letterHolder[0] = 57;
	}
	else if (letterHolder[0] == 47){
	  letterHolder[0] = 122;
	}
	
	// Redraw window
	GUI_drawWindow(Layout_getWindow(thisLayout, 3));
  }
}

static void addToWord(){
  if (index < 4){
	if (timeout == 0){
	  timeout = 1;
	  Animation_post(NULL, 1, 0, resetTimeout);
	  wordHolder[index++] = letterHolder[0];
	}
  }
  
  // Redraw word
  GUI_drawWindow(Layout_getWindow(thisLayout, 4));
}

static char resetTimeout(void * null, int newValue){
  if (newValue > 5){
	// One second has passed, allow buttonpress again
	timeout = 0;
	return 1;
  }
  return 0;
}

static void resetAll(){
  for (int i=0; i<4; i++){
	wordHolder[i] = 32;
  }
  index = 0;
  
  // Redraw word
  GUI_drawWindow(Layout_getWindow(thisLayout, 4));
}