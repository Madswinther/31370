#include "gui.h"
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
  temp->text = "\0";
  
  temp->backgroundColor = backgroundColor;
  temp->borderColor = borderColor;
  
  temp->clickable = 0;
  return temp;
}

void setText(void * window, char * text){
  ((RectangleWindow*)window)->text = text;
}

void setOnClick(void * window, void (*function)()){
  ((Window*)window)->onClick = function;
  
  // Setting an Onclick will make the Window clickable
  ((Window*)window)->clickable = 1;
}

void drawWindow(void * window){
  Window * temp = (Window*)window;
  
  switch (temp->type){
  case PICTUREWINDOW:
	GLCD_LoadPic(temp->left,temp->top, ((PictureWindow*)temp)->picture, 0);
	break;
  case RECTANGLEWINDOW:
	RectangleWindow * tempRect = (RectangleWindow*)window;
	drawFilledRectangle(tempRect->left, tempRect->top, tempRect->right - tempRect->left,
						tempRect->bottom - tempRect->top, tempRect->backgroundColor, tempRect->borderColor, 1);
	if (tempRect->text != "\0"){
	  int xpos = (tempRect->right-tempRect->left-Terminal_9_12_6.H_Size*strlen(tempRect->text))/2;
	  int ypos = (tempRect->bottom-tempRect->top-Terminal_9_12_6.V_Size)/2;
	  GLCD_SetWindow(tempRect->left+xpos, tempRect->top+ypos, 
					 tempRect->left+xpos*2+Terminal_9_12_6.H_Size*strlen(tempRect->text), 
					 tempRect->top+ypos*2+Terminal_9_12_6.V_Size);
	  GLCD_TextSetPos(0, 0);
	  GLCD_SetFont(&Terminal_9_12_6, 0xFFFFFF, tempRect->backgroundColor);
	  GLCD_print(tempRect->text);
	}
	break;
  case PROGRESSBAR:
	ProgressBarDrawFull((ProgressBar*)window);
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



