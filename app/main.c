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

Measurement measurement;
Page * currentPage;
Page * mainPage;
Page * learningPage;
Page * graphPage;
Page * devicesPage;

char Buffer[BUFFER_SIZE];

int main(void){
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
  graphPage = initGraphPage();
  devicesPage = initDevicesPage();
  
  swapToPage(0);
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
	  
	  parse(Buffer, &measurement);
	  
	  // Notify the graph
	  updateGraphPage(&measurement, currentPage == graphPage);
	  
	  double vRMS = measurement.voltage;
	  double iRMS = measurement.current;
	  double pACT = measurement.P_power;
	  double pREAC = measurement.Q_power;
	  double pHAR = measurement.H_power;
	  
	  if (currentPage == mainPage){
		GLCD_SetWindow(0, 0, 150, 70);  
		GLCD_TextSetPos(0,0);
		GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
		GLCD_print(" Voltage: %f\r\n Current: %f\r\n Power: \t%f\r\n Reac: \t%f\r\n Har: \t%f", vRMS, iRMS, pACT, pREAC, pHAR);
	  }
	}
  }
}

void swapToPage(int page){
  if (isAnimating()) return;
  
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
  case 2:
	if (currentPage == graphPage) return;
	currentPage = graphPage;
	break;
  case 3:
	if (currentPage == devicesPage) return;
	currentPage = devicesPage;
	break;
  }
  // Clear all graphics before changing page
  CLEAR_SCREEN();
  drawWindows(currentPage->layout);
  currentPage->drawn = 1;
}

Measurement * getMeasurement(){
  return &measurement;
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
