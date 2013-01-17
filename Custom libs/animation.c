#include "includes.h"
#include "graphics/ProgressBar.h"

Animation * animationHolder;
char mAnimating;

// All animations run on a 5ms interrupt-based routine
void initAnimations(){
  // enable clock for this peripheral (timer2)
  PCONP_bit.PCTIM2 = 1;                 
  
  // Set prescaler to 4
  PCLKSEL1_bit.PCLK_TIMER2 = 0;         
  
  // Set interrupt flag on compare-match with MR0
  T2MCR_bit.MR0I = 1;                   
  
  // Reset MR0 on compare-match
  T2MCR_bit.MR0R = 1;                   
  
  // This value yields a 5ms interrupt time
  T2MR0 = 0x15F90;
  
  // Init timer 2 interrupt
  T2IR_bit.MR0INT = 1; 
  VIC_SetVectoredIRQ(Timer2IntrHandler,0,VIC_TIMER2);
  VICINTENABLE |= 1UL << VIC_TIMER2;
  
  // Start the timer (enable counting)
  T2TCR_bit.CE = 1;     
  
  // Allocate memory for the animationHolder
  animationHolder = (Animation*)malloc(sizeof(*animationHolder));
  animationHolder->pb = NULL;
  mAnimating = 0;
}

void postAnimation(void * object, int increment, int value, char (*animatecall)(void *, int)){
  // Posts an animation to be run using timer2. This call requires a starting value and a value
  // that is used as increment between frames. The object that is to be animated must itself
  // implement an update-function that returns 1 if the animation is finished, and 0 if the animation
  // is not yet done. This update-function must also be passed into this function (animatecall)
  if (animationHolder->pb == NULL){
	animationHolder->animate = animatecall;
	animationHolder->increment = increment;
	animationHolder->value = value;
	animationHolder->pb = object;
	
	// Start animating
	mAnimating = 1;
  }
}

void Timer2IntrHandler(void){
  // Update current animation
  if (animationHolder->pb != NULL){
	// Add increment to current value
	animationHolder->value += animationHolder->increment;
	if (animationHolder->animate(animationHolder->pb, animationHolder->value)){
	  // The update-function returned 1 - the animation is done. Remove it
	  animationHolder->pb = NULL;
	  mAnimating = 0;
	}
  }
  
  // clear interrupt
  T2IR_bit.MR0INT = 1;
  VICADDRESS = 0;
}

char isAnimating(){
  // Returns animation state
  return mAnimating;
}