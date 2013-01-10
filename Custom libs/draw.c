#include "draw.h"
#include "includes.h"
#include "drv_glcd.h"

void drawRectangle(Rectangle * rectangle) {
  	LCD_SET_WINDOW(rectangle->xpos, rectangle->width+rectangle->xpos, rectangle->ypos, rectangle->height+rectangle->height);
  
  
	for (int i = 0; i < rectangle->width; i++) {
		for (int j = 0; j < rectangle->height; j++) {
			LCD_WRITE_PIXEL(rectangle->backgroundColor);
		}
	}
}