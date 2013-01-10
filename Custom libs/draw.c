#include "draw.h"
#include "includes.h"
#include "drv_glcd.h"
void drawHorizontalLine(int x0, int y0, int length, int lineColor) {
	for (int i = 0; i < length; i++) {
		DRAW_PIXEL(i + x0, y0, lineColor);
	}
}

void drawVerticalLine(int x0, int y0, int length, int lineColor) {
	for (int i = 0; i < length; i++) {
		DRAW_PIXEL(x0, y0 + i, lineColor);
	}
}

void drawRectangle(Rectangle * rectangle) {

	drawHorizontalLine(rectangle->x0, rectangle->y0, 
						rectangle->width, rectangle->borderColor);
	
	drawHorizontalLine(rectangle->x0, rectangle->y0 + rectangle->height,
						rectangle->width, rectangle->borderColor);

	drawVerticalLine(rectangle->x0, rectangle->y0, 
						rectangle->height, rectangle->borderColor);
	
	drawVerticalLine(rectangle->x0 + rectangle->width, rectangle->y0,
						rectangle->width, rectangle->borderColor);
}


void drawFilledRectangle(Rectangle * rectangle, char drawBorder) {
	// Draw background
	for (int i = 0; i < rectangle->width; i++) {
		for (int j = 0; j < rectangle->height; j++) {
			DRAW_PIXEL(i,j,rectangle->bakcgroundColor);
		}
	}
	
	// Draw border
	if (drawBorder) {
		drawRectangle(rectangle);
	}
}



