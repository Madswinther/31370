#include "layout.h"
#include "../Custom libs/gui.h"

Layout * Layout_initLayout(){
  	// Initialize a layout. This is basically a struct holding pointers to a
  	// number of windows
	Layout * temp;
	temp = (Layout*)malloc(sizeof(*temp));
	
	temp->size = 0;
	return temp;
}

void Layout_addWindow(Layout * layout, void * window){
  // Add a window to the given layout
  layout->windows[layout->size] = (Window*)window;
  layout->size++;
}

void Layout_removeWindow(Layout * layout){
  // Pop the topmost window from the layout
  layout->windows[layout->size] = NULL;
  layout->size--;
}

void * Layout_getWindow(Layout * layout, char pos){
  // Returns the window at a given position in the layout
	return layout->windows[pos];
}

void Layout_drawWindows(Layout * layout){
  // Calls the appropriate Draw_ing methods, hereby Draw_ing all windows within
  // the given layout
  for(int i=0; i<layout->size; i++){
	GUI_drawWindow(layout->windows[i]);
  }
}

char Layout_dispatchTouch(Layout * layout, int x, int y){
  // Run onTouch checks for all windows in the specified layout. A successfull
  // reading returns 1, if no windows accept the touch, 0 is returned
  for(int i=0; i<layout->size; i++){
	if (GUI_onTouch(layout->windows[i], x, y)){
	  return 1;  
	}
  }
  return 0;
}
