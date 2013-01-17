#include "layout.h"
#include "../Custom libs/gui.h"

Layout * initLayout(){
  	// Initialize a layout. This is basically a struct holding pointers to a
  	// number of windows
	Layout * temp;
	temp = (Layout*)malloc(sizeof(*temp));
	
	temp->size = 0;
	return temp;
}

void addWindow(Layout * layout, void * window){
  // Add a window to the given layout
  layout->windows[layout->size] = (Window*)window;
  layout->size++;
}

void removeWindow(Layout * layout){
  // Pop the topmost window from the layout
  layout->windows[layout->size] = NULL;
  layout->size--;
}

void * getWindow(Layout * layout, char pos){
  // Returns the window at a given position in the layout
	return layout->windows[pos];
}

void drawWindows(Layout * layout){
  // Calls the appropriate drawing methods, hereby drawing all windows within
  // the given layout
  for(int i=0; i<layout->size; i++){
	drawWindow(layout->windows[i]);
  }
}

char dispatchTouch(Layout * layout, int x, int y){
  // Run onTouch checks for all windows in the specified layout. A successfull
  // reading returns 1, if no windows accept the touch, 0 is returned
  for(int i=0; i<layout->size; i++){
	if (onTouch(layout->windows[i], x, y)){
	  return 1;  
	}
  }
  return 0;
}
