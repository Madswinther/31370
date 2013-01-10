#include "vector.h"
#include "../Custom libs/gui.h"

PictureWindow * windowVector[10];
static char pos = 0;

void addWindow(void * window){
  windowVector[pos++] = (PictureWindow*)window;
}

void drawWindows(){
  for(int i=0; i<pos; i++){
	if (windowVector[i]->type == 0){
	  drawPictureWindow(windowVector[i]);
	}
	else{
	  drawRectangleWindow((RectangleWindow*)windowVector[i]);
	}
  }
}

char dispatchTouch(int x, int y){
  for(int i=0; i<pos; i++){
	if (windowVector[i]->type == 0){
	  if (onPictureTouch(windowVector[i], x, y)){
		return 1;
	  }
	}
	else{
	  if(onRectangleTouch((RectangleWindow*)windowVector[i], x, y)){
		return 1;
	  }
	}
  }
  return 0;
}