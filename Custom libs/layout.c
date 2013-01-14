#include "layout.h"
#include "../Custom libs/gui.h"

Layout * initLayout(){
	Layout * temp;
	temp = (Layout*)malloc(sizeof(*temp));
	
	temp->size = 0;
	return temp;
}

void addWindow(Layout * layout, void * window){
  layout->windows[layout->size] = (Window*)window;
  layout->size++;
}

void * getWindow(Layout * layout, char pos){
	return layout->windows[pos];
}

void drawWindows(Layout * layout){
  for(int i=0; i<layout->size; i++){
	drawWindow(layout->windows[i]);
  }
}

char dispatchTouch(Layout * layout, int x, int y){
  for(int i=0; i<layout->size; i++){
	if (onTouch(layout->windows[i], x, y)){
	  return 1;  
	}
  }
  return 0;
}
