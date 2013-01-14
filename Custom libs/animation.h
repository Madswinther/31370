#include <inttypes.h>
#include "includes.h"

#ifndef __ANIMATION_H
#define __ANIMATION_H

typedef struct{
  	int increment;
	void * object;
	char (*animate)(void *, int);
} Animation;

void initAnimations();
void postAnimation(Animation * animation);
void Timer2IntrHandler(void);

#endif
