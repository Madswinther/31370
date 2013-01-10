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

RectangleWindow * initRectangleWindow(int left, int top, int right, int bottom, int color, int borderColor){
  RectangleWindow * temp;
  temp = (RectangleWindow*)malloc(sizeof(*temp));
  temp->left = left;
  temp->right = right;
  temp->top = top;
  temp->bottom = bottom;
  temp->type = 1;
  
  Rectangle rectangle = {right-left, bottom-top, left, top, color, borderColor};
  temp->rectangle = rectangle;
  
  temp->clickable = 0;
  return temp;
}

void drawPictureWindow(PictureWindow * window){
  GLCD_LoadPic(window->left,window->top, window->picture, 0);
}

void drawRectangleWindow(RectangleWindow * window){
  drawFilledRectangle(&window->rectangle, 1);  
}

char onPictureTouch(PictureWindow * window, int x, int y){
  if (!window->clickable) return 0;
  
  // Handle click
  if (window->left <= x && x <= window->right && 
	  window->top <= y && y <= window->bottom){
		return 1; 
	  }
  
  return 0;
}

char onRectangleTouch(RectangleWindow * window, int x, int y){
  if (!window->clickable) return 0;
  
  // Handle click
  if (window->left <= x && x <= window->right && 
	  window->top <= y && y <= window->bottom){
		return 1; 
	  }
  
  return 0;
}



