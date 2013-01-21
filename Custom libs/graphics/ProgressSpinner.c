#include "includes.h"
#include <math.h>
#include "ProgressSpinner.h"

ProgressSpinner * ProgressSpinner_Init(int x0, int y0, int size, int borderColor) {
  
  ProgressSpinner * pspinner = (ProgressSpinner *)malloc(sizeof(ProgressSpinner));
  
  // Mark as progressSpinner
  pspinner->type = 4;
  
  pspinner->cancelled = 0;
  pspinner->reverse = 0;
  
  pspinner->x0 = x0;
  pspinner->y0 = y0;
  
  // A progressSpinner is always a square
  pspinner->size = size;
  pspinner->borderColor = borderColor;
  
  // Compute animation starting point
  pspinner->progressX = -size/4;
  pspinner->progressY = size/4;
  pspinner->animRadius = size/4;
  return pspinner;
}

char ProgressSpinner_Update(void * object, int newProgress) {
  ProgressSpinner * pspinner = (ProgressSpinner*)object;
  
  // Delete old one
  Draw_Circle(pspinner->x0+pspinner->size/2+pspinner->progressX, pspinner->y0+pspinner->size/2+pspinner->progressY, 
			 pspinner->size/5, 0);
  
  // Check for cancellation
  if (pspinner->cancelled == 1) return 1;
  
  // Update current progress of the spinner
  int r2 = pspinner->animRadius * pspinner->animRadius;
  
  if (pspinner->reverse == 0){
	pspinner->progressY = (int) (sqrt(r2 - pspinner->progressX*pspinner->progressX) + 0.5);
	
	pspinner->progressX += 2;
	if (pspinner->progressX >= pspinner->animRadius){
	  pspinner->reverse = 1;
	}
  }
  else{
	pspinner->progressY = (int) -(sqrt(r2 - pspinner->progressX*pspinner->progressX) + 0.5);
	
	pspinner->progressX -= 2;
	if (pspinner->progressX <= -pspinner->animRadius){
	  pspinner->reverse = 0;
	}
  }
  
  // Draw new one
  Draw_Circle(pspinner->x0+pspinner->size/2+pspinner->progressX, pspinner->y0+pspinner->size/2+pspinner->progressY,
			 pspinner->size/5, pspinner->borderColor);
  return 0;
}

void ProgressSpinner_Cancel(ProgressSpinner * pspinner){
  pspinner->cancelled = 1;
}


