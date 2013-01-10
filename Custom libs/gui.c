#include "gui.h"
#include "includes.h"

Window * initWindow(int left, int top, int right, int bottom, Bmp_t * pic){
	Window * temp;
	temp = (Window*)malloc(sizeof(*temp));
	temp->left = left;
	temp->right = right;
	temp->top = top;
	temp->bottom = bottom;
	temp->picture = pic;
	
	temp->clickable = 0;
	return temp;
}

void draw(Window * window){
	GLCD_LoadPic(window->left,window->top, window->picture, 0);
}

void setClickable(Window * window, char value){
	window->clickable = value; 
}

char onClick(Window * window, int x, int y){
	if (!window->clickable) return 0;
	
	// Handle click
	if (window->left <= x && x <= window->right && 
		window->top <= y && y <= window->bottom){
		return 1; 
	}
	
	return 0;
}



