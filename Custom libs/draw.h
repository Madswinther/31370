#ifndef DRAW_H_
#define DRAW_H_

#include "drv_glcd.h"

typedef struct {
	int width, height;
	int xpos, ypos;
	int backgroundColor;
	int borderColor;
} Rectangle;

void drawRectangle(Rectangle * rectangle);

#endif