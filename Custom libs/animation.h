#include <inttypes.h>
#include "includes.h"
#include "graphics/ProgressBar.h"

#ifndef __ANIMATION_H
#define __ANIMATION_H


typedef struct{
  	short increment;
	short value;
	void * pb;
	char (*animate)(void *, int);
} Animation;


void initAnimations();
void postAnimation(void * object, int increment, int value, char (*animate)(void *, int));
void Timer2IntrHandler(void);
char isAnimating();

#endif
