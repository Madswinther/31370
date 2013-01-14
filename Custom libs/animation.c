#include "includes.h"

static Animation * animationHolder[5];
static char animationHolderSize;

// All animations run on a 5ms interrupt-based routine
void initAnimations(){
  PCONP_bit.PCTIM2 = 1;                 // enable clock
  PCLKSEL1_bit.PCLK_TIMER2 = 0;         // Set prescaler to /4
  
  T2MCR_bit.MR0I = 1;                   // Set interrupt
  T2MCR_bit.MR0R = 1;                   // enable reset
  T2MCR_bit.MR0S = 0;                   // disable stop
  
  T2PR = 0x0;	// No more prescaling
  
  T2MR0 = 0x15F90;
  
  // Init timer 0 interrupt
  T2IR_bit.MR0INT = 1;  // clear pending interrupt
  VIC_SetVectoredIRQ(Timer2IntrHandler,5,VIC_TIMER2);
  VICINTENABLE |= 1UL << VIC_TIMER2;
  T2TCR_bit.CE = 1;     // counting Enable
  
  animationHolderSize = 0;
}

void postAnimation(Animation * animation){
  animationHolder[animationHolderSize++] = animation;
}

void Timer2IntrHandler(void){
  // iterate through posted animations and update/finish them
  for (int i=0; i<animationHolderSize; i++){
	if (animationHolder[i]->animate(animationHolder[i]->object, animationHolder[i]->increment)){
	  animationHolder[i] = NULL;
	  animationHolderSize--;
	}
  }
  
  // clear interrupt
  T2IR_bit.MR0INT = 1;
  VICADDRESS = 0;
}