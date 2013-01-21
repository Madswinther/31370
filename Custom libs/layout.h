#include "includes.h"
#include "../Custom libs/gui.h"

#ifndef __LAYOUT_H
#define __LAYOUT_H

typedef struct{
	char size;
	Window * windows[10];
} Layout;

Layout * Layout_initLayout();
void Layout_addWindow(Layout * layout, void * window);
void * Layout_getWindow(Layout * layout, char pos);
void Layout_removeWindow(Layout * layout);
void Layout_drawWindows(Layout * layout);
char Layout_dispatchTouch(Layout * layout, int x, int y);

#endif // __LAYOUT_H
