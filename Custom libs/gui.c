#include "gui.h"
#include "includes.h"

PictureWindow * initPictureWindow(int left, int top, int right, int bottom, Bmp_t * pic){
  // Initializes a window specified by absolute coordinates and a bitmap
  PictureWindow * temp;
  temp = (PictureWindow*)malloc(sizeof(*temp));
  temp->left = left;
  temp->right = right;
  temp->top = top;
  temp->bottom = bottom;
  temp->picture = (Bmp_t*) pic;
  temp->type = 0;
  
  temp->clickable = 0;
  return temp;
}

RectangleWindow * initRectangleWindow(int left, int top, int right, int bottom, int backgroundColor, int borderColor){
  // Initializes a window specified by absolute coordinates, a background- and a bordercolor
  RectangleWindow * temp;
  temp = (RectangleWindow*)malloc(sizeof(*temp));
  temp->left = left;
  temp->right = right;
  temp->top = top;
  temp->bottom = bottom;
  temp->type = 1;
  temp->text = "\0";
  
  temp->backgroundColor = backgroundColor;
  temp->borderColor = borderColor;
  
  temp->clickable = 0;
  temp->hidden = 0;
  return temp;
}

void setText(void * window, char * text){
  // Sets the text to draw within a given window
  ((RectangleWindow*)window)->text = text;
}

void setOnClick(void * window, void (*function)()){
  // Sets a function to be called when this window is clicked
  ((Window*)window)->onClick = function;
  
  // Setting an Onclick will make the Window clickable
  ((Window*)window)->clickable = 1;
}

void drawWindow(void * window){
  // Draw the window based on its type. The type is contained within the first
  // byte of all the window structs
  Window * temp = (Window*)window;
  
  RectangleWindow * tempRect;
  
  switch (temp->type){
  case PICTUREWINDOW:
	// This is a picturewindow, draw the bitmap using the GLCD command
	GLCD_LoadPic(temp->left,temp->top, ((PictureWindow*)temp)->picture, 0);
	break;
  case RECTANGLEWINDOW:
	// This is a rectanglewindow, draw a rectangle using the user made graphics lib
	tempRect = (RectangleWindow*)window;
	
	// Should this window be drawn?
	if (tempRect->hidden == 1) return;
	
	drawFilledRectangle(tempRect->left, tempRect->top, tempRect->right - tempRect->left,
						tempRect->bottom - tempRect->top, tempRect->backgroundColor, tempRect->borderColor, 1);
	
	// Draw the text by computing the coordinates required to position the text in the
	// center of the window
	if (tempRect->text != "\0"){
	  // x-position can be found as the middle of the window minus half the size of the string(in pixels)
	  int xpos = (tempRect->right-tempRect->left-Terminal_9_12_6.H_Size*strlen(tempRect->text))/2;
	  
	  // y-position can be found as the middle of the window minues half the size of the font(in pixels)
	  int ypos = (tempRect->bottom-tempRect->top-Terminal_9_12_6.V_Size)/2;
	  
	  // Set the window position
	  GLCD_SetWindow(tempRect->left+xpos, tempRect->top+ypos, 
					 tempRect->left+xpos*2+Terminal_9_12_6.H_Size*strlen(tempRect->text), 
					 tempRect->top+ypos*2+Terminal_9_12_6.V_Size);
	  
	  // Draw the text that has been set
	  GLCD_TextSetPos(0, 0);
	  GLCD_SetFont(&Terminal_9_12_6, 0xFFFFFF, tempRect->backgroundColor);
	  GLCD_print("%s", tempRect->text);
	}
	break;
  case PROGRESSBAR:
	// This is a progressbar, draw it using the specifically designed progressbar method
	ProgressBarDrawFull((ProgressBar*)window);
	break;
  case GRAPH:
	// This is a graph, draw it using the specifically designed graph method
	Graph_draw((Graph*)window);
	break;
  }
}

void setHidden(void * window, char hide){
  // This only applies to rectanglewindows sofar
  if (((Window*)window)->type != RECTANGLEWINDOW) return;
  
  RectangleWindow * tempRect = (RectangleWindow*)window;
  
  // Hide or show?
  tempRect->hidden = hide;
  
  if (hide){
	drawFilledRectangle(tempRect->left, tempRect->top, tempRect->right - tempRect->left,
						tempRect->bottom - tempRect->top, 0x0, 0x0, 1);
  }
  else{
	drawWindow(window);
  }
}

char onTouch(void * window, int x, int y){
  // Checks wether the touch is within the bounds of this particular window
  Window * temp = (Window*)window;
  
  // Only clickable windows are eligible for receiving touches
  if (!temp->clickable) return 0;
  
  // Handle click
  if (temp->left <= x && x <= temp->right && 
	  temp->top <= y && y <= temp->bottom){
		// Call onClick function if one has been set
		if (temp->onClick != NULL){
		  temp->onClick();  
		}
		return 1; 
	  }
  
  return 0;
}



