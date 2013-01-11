#include "draw.h"
#include "includes.h"
#include "drv_glcd.h"
#include <math.h>

#define MAX_PROGRESS 1000

typedef struct {
	int progress, oldProgress;
	int x0, y0;
	int width, height;
	int backgroundColor;
	int foregroundColor;
} ProgressBar;

ProgressBar * ProgressBarInit(int x0, int y0, int width, int height, 
							int foreGroundColor, int backgroundColor) {

	ProgressBar * pbar = (ProgressBar *)malloc(sizeof(ProgressBar));
	pbar->x0 = x0;
	pbar->y0 = y0;
	pbar->width = width;
	pbar->height = height;
	pbar->foregroundColor = foregroundColor;
	pbar->backgroundColor = backgroundColor;
	pbar->progress = 0;
	pbar->oldProgress = 0;
	ProgressBarDraw(pbar);
	return pbar;
}


int getProgressPixelWidth(int progress, int width) {
	return (progress * width) / MAX_PROGRESS;
}


void ProgressBarDrawFull(ProgressBar * pbar) {
	int x0 = pbar->x0, y0 = pbar->y0; 
	int width = pbar->width, height = pbar->height;
	int foregroundColor = pbar->foregroundColor;
	int backgroundColor = pbar->backgroundColor;
	int blank = 0xFFFFFF;
	
	// Draw background rectangle
	drawFilledRectangle(x0, y0, width, height, backgroundColor, blank, 0);

	// Draw progress
	int pWidth = getPixelWidth(pbar->progress, pbar->width);
	drawFilledRectangle(x0, y0, pWidth, height, foregroundColor, blank, 0);
}

void ProgressBarUpdate(ProgressBar * pbar, int newProgress) {
	
	// Update current progress of the bar
	pbar->oldProgress = pbar->progress;
	pbar->progress = newProgress;
	
	// Check for invalid progress input
	if (pbar->progress > 100 || pbar->progress < 0) return;
	
	// Get change in progress
	int dp = pbar->progress - pbar->oldProgress;
	int oldPixWidth = getProgressPixelWidth(pbar->oldProgress);
	int newPixWidth = getProgressPixelWidth(pbar->progress);
	
	if (dp > 0) {
		// Progress should increase
		int xpos = pbar->x0 + oldPixWidth;
		int ypos = pbar->y0;
		int width = newPixWidth - oldPixWidth;
		
		// Draw new foreground
		drawFilledRectangle(xpos, ypos, width, pbar->height, pbar->foregroundColor, 0, 0);
			
	} else if (dp < 0) {
		// Progress should decrease
		int xpos = pbar->x0 + newPixWidth;
		int ypos = pbar->y0;
		int width = oldPixWidth - newPixWidth;
		
		// Draw background
		drawFilledRectangle(xpos, ypos, width, pbar->height, pbar->backgroundColor, 0, 0);
	}
	
	// Update progressbar progress
	pbar->progress = newProgress;	
}



