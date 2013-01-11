#include "gui.h"
#include "../Custom libs/draw.h"
#include "includes.h"

PictureWindow * initPictureWindow(int left, int top, int right, int bottom, Bmp_t * pic){
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
  RectangleWindow * temp;
  temp = (RectangleWindow*)malloc(sizeof(*temp));
  temp->left = left;
  temp->right = right;
  temp->top = top;
  temp->bottom = bottom;
  temp->type = 1;
  
  temp->backgroundColor = backgroundColor;
  temp->borderColor = borderColor;
    
  temp->clickable = 0;
  return temp;
}

void setOnClick(void * window, void (*function)()){
  ((Window*)window)->onClick = function;
}

void drawWindow(void * window){
  Window * temp = (Window*)window;
  
  switch (temp->type){
  case 0:
	// PictureWindow
	GLCD_LoadPic(temp->left,temp->top, ((PictureWindow*)temp)->picture, 0);
	break;
  case 1:
	// RectangleWindow
	RectangleWindow * tempRect = (RectangleWindow*)temp;
	drawFilledRectangle(tempRect->left, tempRect->top, tempRect->right - tempRect->left,
						tempRect->bottom - tempRect->top, tempRect->backgroundColor, tempRect->borderColor, 1);
	break;
  }
}

char onTouch(void * window, int x, int y){
  Window * temp = (Window*)window;
  
  if (!temp->clickable) return 0;
  
  // Handle click
  if (temp->left <= x && x <= temp->right && 
	  temp->top <= y && y <= temp->bottom){
		// Call listener
		if (temp->onClick != NULL){
			temp->onClick();  
		}
		return 1; 
	  }
  
  return 0;
}



