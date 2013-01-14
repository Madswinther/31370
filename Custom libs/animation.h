#include <inttypes.h>
#include "includes.h"
#include "graphics/ProgressBar.h"

#ifndef __ANIMATION_H
#define __ANIMATION_H


typedef struct{
  	int increment;
	ProgressBar * pb;
	char (*animate)(void *, int);
} Animation;


void initAnimations();
void postAnimation(ProgressBar * object, int increment, char (*animate)(void *, int));
void Timer2IntrHandler(void);

#endif
