#include "includes.h"
#include <math.h>
#include "ProgressBar.h"

ProgressBar * ProgressBar_Init(int x0, int y0, int width, int height, 
							int foregroundColor, int backgroundColor) {
							  
	ProgressBar * pbar = (ProgressBar *)malloc(sizeof(ProgressBar));
	pbar->type = 2;
	pbar->x0 = x0;
	pbar->y0 = y0;
	pbar->width = width;
	pbar->height = height;
	pbar->foregroundColor = foregroundColor;
	pbar->backgroundColor = backgroundColor;
	pbar->progress = 0;
	pbar->oldProgress = 0;
	return pbar;
}


static int getPixelWidth(int progress, int width) {
	return (progress * width) / MAX_PROGRESS;
}


void ProgressBar_DrawFull(ProgressBar * pbar) {
	int x0 = pbar->x0, y0 = pbar->y0; 
	int width = pbar->width, height = pbar->height;
	int foregroundColor = pbar->foregroundColor;
	int backgroundColor = pbar->backgroundColor;
	int blank = 0xFFFFFF;
	
	// Draw background rectangle
	Draw_FilledRectangle(x0, y0, width, height, backgroundColor, blank, 0);

	// Draw progress
	int pWidth = getPixelWidth(pbar->progress, pbar->width);
	Draw_FilledRectangle(x0, y0, pWidth, height, foregroundColor, blank, 0);
}

char ProgressBar_Update(void * object, int newProgress) {
	ProgressBar * pbar = (ProgressBar*)object;
  
	if (newProgress > MAX_PROGRESS) newProgress = MAX_PROGRESS;
	
	// Update current progress of the bar
	pbar->oldProgress = pbar->progress;
	pbar->progress = newProgress;
	
	// Check for invalid progress input
	if (pbar->progress >= MAX_PROGRESS || pbar->progress < 0) return 1;
	
	// Get change in progress
	int dp = pbar->progress - pbar->oldProgress;
	int oldPixWidth = getPixelWidth(pbar->oldProgress, pbar->width);
	int newPixWidth = getPixelWidth(pbar->progress, pbar->width);
	
	if (dp > 0) {
		// Progress should increase
		int xpos = pbar->x0 + oldPixWidth;
		int ypos = pbar->y0;
		int width = newPixWidth - oldPixWidth;
		
		// Draw new foreground
		Draw_FilledRectangle(xpos, ypos, width, pbar->height, pbar->foregroundColor, 0, 0);
			
	} else if (dp < 0) {
		// Progress should decrease
		int xpos = pbar->x0 + newPixWidth;
		int ypos = pbar->y0;
		int width = oldPixWidth - newPixWidth;
		
		// Draw background
		Draw_FilledRectangle(xpos, ypos, width, pbar->height, pbar->backgroundColor, 0, 0);
	}	
	return 0;
}



