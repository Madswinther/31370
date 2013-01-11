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
void drawCircle(int x0, int y0, int radius, int borderColor){
	int x, y, r2;
        
	r2 = radius * radius;
	for (x = -radius; x <= radius; x++) {
		y = (int) (sqrt(r2 - x*x) + 0.5);
		DRAW_PIXEL(x0 + x, y0 + y, borderColor);
		DRAW_PIXEL(x0 + x, y0 - y, borderColor);
	}
}

void drawFilledCircle(int x0, int y0, int r, int backgroundColor, int borderColor, int drawBorder) {
	
	for (int x = -r; x <= r; x++) {
		int dy = (int)(sqrt(r*r - x*x));
		for (int y = -dy; y <= dy; y++) {
			DRAW_PIXEL(x0+x, y0+y, backgroundColor);
		}
	}
	
	if (drawBorder) drawCircle(x0,y0,r,borderColor);
}


void drawRectangle(int x0, int y0, int width, int height, int borderColor) {
	drawHorizontalLine(x0, y0, width, borderColor);
	drawHorizontalLine(x0, y0 + height, width, borderColor);
	drawVerticalLine(x0, y0, height, borderColor);
	drawVerticalLine(x0 + width, y0, height, borderColor);
}

void drawFilledRectangle(int x0, int y0, int width, int height, 
						int backgroundColor, int borderColor, int drawBorder) {
	
	// Draw background
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			DRAW_PIXEL(x0 + x, y0 + y, backgroundColor);
		}
	}
	
	// Draw border
	if (drawBorder) drawRectangle(x0, y0, width, height, borderColor);	
}

