#include "includes.h"
#include "../Custom libs/gui.h"

#ifndef __LAYOUT_H
#define __LAYOUT_H

typedef struct{
	int size;
	Window * windows[10];
} Layout;

Layout * initLayout();
void addWindow(Layout * layout, void * window);
void * getWindow(Layout * layout, char pos);
void drawWindows(Layout * layout);
char dispatchTouch(Layout * layout, int x, int y);
void ged();

#endif // __LAYOUT_H
