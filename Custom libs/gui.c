#include "gui.h"
#include "includes.h"

Window * initWindow(int left, int top, int right, int bottom, Bmp_t * pic){
	Window * temp = (Window*)malloc(sizeof(temp));
	temp->left = left;
	temp->right = right;
	temp->top = top;
	temp->bottom = bottom;
	temp->picture = pic;
	
	temp->clickable = 0;
	return temp;
}

void draw(Window * window){
	//GLCD_SetWindow(window->left,window->top,window->right,window->bottom);
	GLCD_LoadPic(window->left,window->top, window->picture, 0);
	//GLCD_LoadPic(
}

char onClick(Window * window, int x, int y){
	if (!window->clickable) return 0;
	
	// Handle click
	if (window->left <= x && x <= window->right && window->top <= y && y <= window->bottom){
		return 1; 
	}
	
	return 0;
}



