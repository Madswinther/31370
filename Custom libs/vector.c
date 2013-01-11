#include "vector.h"
#include "../Custom libs/gui.h"

Window * windowVector[];
static char pos = 0;
static char size = 1;

void addWindow(void * window){
  // Init vector if needed
  if (windowVector == NULL){
	Window * windowVector[size];
	windowVector = (Window*)malloc(sizeof(*windowVector));
  }
  // Grow vector if needed
  if (pos+1 >= size){
	Window * temp[size]; = windowVector;
	size *= 2;
	
  }
  windowVector[pos++] = (Window*)window;
  setOnClick(window, ged);
}

void drawWindows(){
  for(int i=0; i<pos; i++){
	drawWindow(windowVector[i]);
  }
}

char dispatchTouch(int x, int y){
  for(int i=0; i<pos; i++){
	if (onTouch(windowVector[i], x, y)){
	  return 1;  
	}
  }
  return 0;
}

void ged(){
	USB_H_LINK_LED_FCLR = USB_H_LINK_LED_MASK;  
}