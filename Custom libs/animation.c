#include "includes.h"
#include "graphics/ProgressBar.h"

Animation * animationHolder;
char mAnimating;

// All animations run on a 5ms interrupt-based routine
void initAnimations(){
  PCONP_bit.PCTIM2 = 1;                 // enable clock
  PCLKSEL1_bit.PCLK_TIMER2 = 0;         // Set prescaler to /4
  
  T2MCR_bit.MR0I = 1;                   // Set interrupt
  T2MCR_bit.MR0R = 1;                   // enable reset
  T2MCR_bit.MR0S = 0;                   // disable stop
  
  T2PR = 0x0;	// No more prescaling
  
  T2MR0 = 0x15F90;
  
  // Init timer 2 interrupt
  T2IR_bit.MR0INT = 1;  // clear pending interrupt
  VIC_SetVectoredIRQ(Timer2IntrHandler,0,VIC_TIMER2);
  VICINTENABLE |= 1UL << VIC_TIMER2;
  T2TCR_bit.CE = 1;     // counting Enable
  
  animationHolder = (Animation*)malloc(sizeof(*animationHolder));
  animationHolder->pb = NULL;
  
  mAnimating = 0;
}

void postAnimation(void * object, int increment, int value, char (*animatecall)(void *, int)){
  if (animationHolder->pb == NULL){
	animationHolder->animate = animatecall;
	animationHolder->increment = increment;
	animationHolder->value = value;
	animationHolder->pb = object;
	mAnimating = 1;
  }
}

void Timer2IntrHandler(void){
  // iterate through posted animations and update/finish them
  if (animationHolder->pb != NULL){
	animationHolder->value += animationHolder->increment;
	if (animationHolder->animate(animationHolder->pb, animationHolder->value)){
	  animationHolder->pb = NULL;
	  mAnimating = 0;
	}
  }
  
  // clear interrupt
  T2IR_bit.MR0INT = 1;
  VICADDRESS = 0;
}

char isAnimating(){
	return mAnimating;
}