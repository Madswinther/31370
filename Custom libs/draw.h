#ifndef DRAW_H_
#define DRAW_H_

#include "drv_glcd.h"

typedef struct {
	int width, height;
	int xpos, ypos;
	int backgroundColor;
	int borderColor;
} Rectangle;


void drawVerticalLine(int x0, int y0, int length, int lineColor);
void drawHorizontalLine(int x0, int y0, int length, int lineColor);
void drawLine(int x0, int y0, int x1, int y1, int lineColor);

void drawCircle(int x0, int y0, int radius, int borderColor);
void drawFilledCircle(int x0, int y0, int radius,int backgroundColor, 
						int borderColor, int drawBorder);

void drawRectangle(int x0, int y0, int width, int height, int borderColor);
void drawFilledRectangle(int x0, int y0, int width, int height, 
						int backgroundColor, int borderColor, int drawBorder);

#endif
