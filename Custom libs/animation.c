#include "includes.h"
#include "graphics/ProgressBar.h"

Animation * animationHolder;
int increment;

// All animations run on a 5ms interrupt-based routine
void initAnimations(){
  PCONP_bit.PCTIM2 = 1;                 // enable clock
  PCLKSEL1_bit.PCLK_TIMER2 = 0;         // Set prescaler to /4
  
  T2MCR_bit.MR0I = 1;                   // Set interrupt
  T2MCR_bit.MR0R = 1;                   // enable reset
  T2MCR_bit.MR0S = 0;                   // disable stop
  
  T2PR = 0x0;	// No more prescaling
  
  T2MR0 = 0x895440;
  
  // Init timer 0 interrupt
  T2IR_bit.MR0INT = 1;  // clear pending interrupt
  VIC_SetVectoredIRQ(Timer2IntrHandler,0,VIC_TIMER2);
  VICINTENABLE |= 1UL << VIC_TIMER2;
  T2TCR_bit.CE = 1;     // counting Enable
  
  animationHolder = NULL;  
}

void postAnimation(ProgressBar * object, int increment, char (*animatecall)(void *, int)){
  if (animationHolder == NULL){
    animationHolder = (Animation*)malloc(sizeof(*animationHolder));
	Animation ged = {increment, object, animatecall};
	animationHolder = &ged;
  }
}

void Timer2IntrHandler(void){
  // iterate through posted animations and update/finish them
  //for (int i=0; i<animationHolderSize; i++){
  if (animationHolder != NULL){
	if (animationHolder->animate(animationHolder->pb, animationHolder->increment)){
	  //animationHolder = NULL;
	}
	animationHolder->increment += 10;
	if (animationHolder->increment >= 1000){
		free(animationHolder);
		animationHolder = NULL;
	}
  }
  // }
  
  // clear interrupt
  T2IR_bit.MR0INT = 1;
  VICADDRESS = 0;
}