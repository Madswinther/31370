#ifndef DRAW_H_
#define DRAW_H_

#include "drv_glcd.h"

void Draw_VerticalLine(int x0, int y0, int length, int lineColor);
void Draw_HorizontalLine(int x0, int y0, int length, int lineColor);
void Draw_Line(int x0, int y0, int x1, int y1, int lineColor);

void Draw_Circle(int x0, int y0, int radius, int borderColor);
void Draw_FilledCircle(int x0, int y0, int radius,int backgroundColor, 
						int borderColor, int Draw_Border);

void plot8points(int x0, int y0, int x, int y, int borderColor);
void plot4points(int x0, int y0, int x, int y, int borderColor);
						
						
void Draw_Rectangle(int x0, int y0, int width, int height, int borderColor);
void Draw_FilledRectangle(int x0, int y0, int width, int height, 
						int backgroundColor, int borderColor, int Draw_Border);

#endif
