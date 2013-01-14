#include "includes.h"
#include <stdlib.h>
#include <math.h>


#define NONPROT 0xFFFFFFFF

#ifndef SDRAM_DEBUG
#pragma segment=".crp"
#pragma location=".crp"
__root const unsigned crp = NONPROT;
#endif

#define LCD_VRAM_BASE_ADDR ((Int32U)&SDRAM_BASE_ADDR)

extern Int32U SDRAM_BASE_ADDR;
extern FontType_t Terminal_6_8_6;
extern FontType_t Terminal_9_12_6;
extern FontType_t Terminal_18_24_12;

void init();
void swapToPage (int page);

Page * currentPage;
Page * mainPage;
Page * learningPage;

int main(void){
  char Buffer[BUFFER_SIZE];
  // Init buffer
  for (int i=0; i<BUFFER_SIZE; i++){
	Buffer[i] = 0;
  }
  
  init();
  
  // Touch init
  ToushRes_t XY_Touch;
  Boolean Touch = FALSE;
  TouchScrInit();
  
  // Init font
  GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
  
  // Init UART
  UartInit(UART_0,4,NORM);
  
  // Init animations
  initAnimations();
  
  mainPage = initMainPage();
  learningPage = initLearningPage();
  
  swapToPage(0);
  
  Graph * graph = Graph_init(0,0,320, 180);
  
	Graph_xlim(graph, 0, 100);
	Graph_ylim(graph, 210, 240);
	//Graph_draw(graph);
  
  while(1){
	if(TouchGet(&XY_Touch))
    {
	  dispatchTouch(currentPage->layout, XY_Touch.X, XY_Touch.Y);
      if (Touch == FALSE){
        Touch = TRUE;
      }
    }
	else if(Touch)
    {
      USB_H_LINK_LED_FSET = USB_H_LINK_LED_MASK;
      Touch = FALSE;
    }
	
	
    // Data from UART0
	UartCheck(Buffer);
	
	if (Buffer[0] != 'E'){
	  
	  Measurement measurement;
	  parse(Buffer, &measurement);
	  
	  double vRMS = measurement.voltage;
	  double iRMS = measurement.current;
	  double pACT = measurement.P_power;
	  
	  if (currentPage == mainPage && 0){
		GLCD_SetWindow(0, 0, 150, 50);  
		GLCD_TextSetPos(0,0);
		GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
		GLCD_print(" Voltage: %f\r\n Current: %f\r\n Power: \t%f", vRMS, iRMS, pACT);
	  }
	}
  }
}

void swapToPage(int page){
  switch (page){
  case 0:
	//mainpage
	if (currentPage == mainPage) return;
	currentPage = mainPage;	
	break;
  case 1:
	if (currentPage == learningPage) return;
	currentPage = learningPage;
	break;
  }
  // Clear all graphics before changing page
  CLEAR_SCREEN();
  drawWindows(currentPage->layout);
  currentPage->drawn = 1;
}

void init(){
  GLCD_Ctrl (FALSE);
  // Init GPIO
  GpioInit();
#ifndef SDRAM_DEBUG
  // MAM init
  MAMCR_bit.MODECTRL = 0;
  MAMTIM_bit.CYCLES  = 3;   // FCLK > 40 MHz
  MAMCR_bit.MODECTRL = 2;   // MAM functions fully enabled
  // Init clock
  InitClock();
  // SDRAM Init
  SDRAM_Init();
#endif // SDRAM_DEBUG
  // Init VIC
  VIC_Init();
  // GLCD init
  GLCD_Init (NULL, NULL);
  // Disable Hardware cursor
  GLCD_Cursor_Dis(0);
  
  // Touched indication LED
  USB_H_LINK_LED_SEL = 0; // GPIO
  USB_H_LINK_LED_FSET = USB_H_LINK_LED_MASK;
  USB_H_LINK_LED_FDIR |= USB_H_LINK_LED_MASK;
  
  __enable_interrupt();
  
  // Enable GLCD
  GLCD_Ctrl (TRUE);
}
