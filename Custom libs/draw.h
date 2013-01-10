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
void drawFilledRectangle(Rectangle * rectangle, char drawBorder);
void drawVerticalLine(int x0, int y0, int length, int lineColor);
void drawHorizontalLine(int x0, int y0, int length, int lineColor);

#endif