#include "draw.h"
#include "includes.h"
#include "drv_glcd.h"
#include <math.h>

void drawHorizontalLine(int x0, int y0, int length, int lineColor) {
	for (int i = 0; i < length; i++) {
		DRAW_PIXEL(i + x0, y0, lineColor);
	}
}

void drawVerticalLine(int x0, int y0, int length, int lineColor){
	for (int i = 0; i < length; i++) {
		DRAW_PIXEL(x0, y0 + i, lineColor);
	}
}

// Implemented with Bresenham's algorithm (taken from the site
// http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm
void drawLine(int x0, int y0, int x1, int y1, int lineColor) {
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
 
	for(;;){
		DRAW_PIXEL(x0, y0, lineColor);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

// Circle rasterization algorithm (modified from version from the following site)
// http://groups.csail.mit.edu/graphics/classes/6.837/F98/Lecture6/circle.html
void drawCircle(int x0, int y0, int radius, int lineColor){
	int x, y, r2;
        
	r2 = radius * radius;
	for (x = -radius; x <= radius; x++) {
		y = (int) (sqrt(r2 - x*x) + 0.5);
		DRAW_PIXEL(x0 + x, y0 + y, lineColor);
		DRAW_PIXEL(x0 + x, y0 - y, lineColor);
	}
}

void drawRectangle(Rectangle * rectangle) {

	drawHorizontalLine(rectangle->xpos, rectangle->ypos, 
						rectangle->width, rectangle->borderColor);
	
	drawHorizontalLine(rectangle->xpos, rectangle->ypos + rectangle->height,
						rectangle->width, rectangle->borderColor);

	drawVerticalLine(rectangle->xpos, rectangle->ypos, 
						rectangle->height, rectangle->borderColor);
	
	drawVerticalLine(rectangle->xpos + rectangle->width, rectangle->ypos,
						rectangle->height, rectangle->borderColor);
}


void drawFilledRectangle(Rectangle * rectangle, char drawBorder) {
	// Draw background
	for (int i = 0; i < rectangle->width; i++) {
		for (int j = 0; j < rectangle->height; j++) {
			DRAW_PIXEL(rectangle->xpos+i,rectangle->ypos+j,rectangle->backgroundColor);
		}
	}
	
	// Draw border
	if (drawBorder) {
		drawRectangle(rectangle);
	}
}




