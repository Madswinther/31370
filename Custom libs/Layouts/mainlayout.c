#include "includes.h"

Layout * thisLayout;
static char currentLetter = 65;
static char letterHolder[] = {'0','\0'};
RectangleWindow * letter;

Layout * initMainLayout(){
	// Alloc space
	Layout * thisLayout;
	thisLayout = (Layout*)malloc(sizeof(*thisLayout));
	
	// Create layout
	thisLayout = Layout_initLayout();
	
	RectangleWindow * welcome = GUI_initRectangleWindow(250, 0, 317, 50, BUTTON_SELECTED, BUTTON_BORDER);
	
	// TEST
	RectangleWindow * next = GUI_initRectangleWindow(150, 100, 200, 150, BUTTON_SELECTED, BUTTON_BORDER);
	RectangleWindow * previous = GUI_initRectangleWindow(50, 100, 100, 150, BUTTON_SELECTED, BUTTON_BORDER);
	letter = GUI_initRectangleWindow(100, 100, 150, 150, BUTTON_SELECTED, BUTTON_BORDER);
	
	GUI_setText(welcome, "Welcome!");
	GUI_setText(previous, "P");
	GUI_setText(next, "N");
	
	//letterHolder = malloc( sizeof(char) * 2 );
	//letterHolder[0] = currentLetter;
	//letterHolder[1] = '\0';
	GUI_setText(letter, letterHolder);
  
	// Add windows
	Layout_addWindow(thisLayout, welcome);
	Layout_addWindow(thisLayout, next);
	Layout_addWindow(thisLayout, previous);
	Layout_addWindow(thisLayout, letter);
	
	GUI_setOnClick(next, nextLetter);
	
	return thisLayout;
}

static void nextLetter(){
  letterHolder[0] = currentLetter++;
  //GUI_setText(Layout_getWindow(thisLayout, 3), letterHolder);
  GUI_drawWindow(letter);
}


