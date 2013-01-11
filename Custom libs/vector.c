#include "vector.h"
#include "../Custom libs/gui.h"

Window * windowVector[10];
static char pos = 0;

void addWindow(void * window){
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