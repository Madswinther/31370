#include "includes.h"

Layout * thisLayout;

Layout * initMainLayout(){
  // Alloc space
  thisLayout = (Layout*)malloc(sizeof(Layout));
  
  // Create layout
  thisLayout = Layout_initLayout();
  
  RectangleWindow * welcome = GUI_initRectangleWindow(250, 0, 317, 50, BUTTON_SELECTED, BUTTON_BORDER);

  GUI_setText(welcome, "Welcome!");
  
  // Add windows
  Layout_addWindow(thisLayout, welcome);
  
  return thisLayout;
}



