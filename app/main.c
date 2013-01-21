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
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

extern Int32U SDRAM_BASE_ADDR;
extern FontType_t Terminal_6_8_6;
extern FontType_t Terminal_9_12_6;
extern FontType_t Terminal_18_24_12;

void init();
void swapToLayout (int layout);

Measurement measurement;
Layout * currentLayout;
Layout * mainLayout;
Layout * learningLayout;
Layout * graphLayout;
Layout * devicesLayout;
Layout * navigationBar;

char Buffer[BUFFER_SIZE];

int main(void){
  // Init buffer
  for (int i=0; i<BUFFER_SIZE; i++){
	Buffer[i] = 0;
  }
  
  //uIP
  unsigned int i;
  uip_ipaddr_t ipaddr;
  struct timer periodic_timer, arp_timer;
  clock_init(2);
  timer_set(&periodic_timer, CLOCK_SECOND / 2);
  timer_set(&arp_timer, CLOCK_SECOND * 10);
  
  init();
  
  // Touch init
  ToushRes_t XY_Touch;
  Boolean Touch = FALSE;
  TouchScrInit();
  
  // Init font
  GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
  
  // Init UART
  UART_init(UART_0,4,NORM);
  
  // Init Real Time Clock
  RTC_init();
  
  // Init animations
  initAnimations();
  
  // Init navigationBar
  navigationBar = initNavigationBar();
  
  // Init pages
  mainLayout = initMainLayout();
  learningLayout = initLearningLayout();
  graphLayout = initGraphLayout();
  devicesLayout = initDevicesLayout();
  
  swapToLayout(0);
  
  // Initialize the ethernet device driver
  do{
	GLCD_TextSetPos(0,0);
  }
  while(!tapdev_init());
  GLCD_TextSetPos(0,0);
  
  // uIP web server
  // Initialize the uIP TCP/IP stack.
  uip_init();
  
  uip_ipaddr(ipaddr, 192,168,0,100);
  uip_sethostaddr(ipaddr);
  uip_ipaddr(ipaddr, 192,168,0,1);
  uip_setdraddr(ipaddr);
  uip_ipaddr(ipaddr, 255,255,255,0);
  uip_setnetmask(ipaddr);
  
  // Initialize the HTTP server.
  httpd_init();
  
  while(1){
	if(TouchGet(&XY_Touch))
	{
	  // Check if the current Layout accepts the touch
	  if (!Layout_dispatchTouch(currentLayout, XY_Touch.X, XY_Touch.Y)){
		// Touch not accepted, pass it on to the navigationBar
		Layout_dispatchTouch(navigationBar, XY_Touch.X, XY_Touch.Y);
	  }
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
	UART_Check(Buffer);
	
	if (Buffer[0] != 'E'){
	  
	  Parsing_parse(Buffer, &measurement);
	  
	  // Notify the graph
	  updateGraphLayout(&measurement, currentLayout == graphLayout);
	  checkDevices(&measurement, currentLayout);
	  
	  double vRMS = measurement.voltage;
	  double iRMS = measurement.current;
	  double pACT = measurement.P_power;
	  double pREAC = measurement.Q_power;
	  double pHAR = measurement.H_power;
	  
	  if (currentLayout == mainLayout){
		GLCD_SetWindow(0, 0, 150, 70);  
		GLCD_TextSetPos(0,0);
		GLCD_SetFont(&Terminal_9_12_6,0xFFFFFF,0x000000);
		GLCD_print(" Voltage: %f\r\n Current: %f\r\n Power: \t%f\r\n Reac: \t%f\r\n Har: \t%f", vRMS, iRMS, pACT, pREAC, pHAR);
	  }
	}
	
	// HANDLE uIP
	uip_len = tapdev_read(uip_buf);
	if(uip_len > 0)
	{
	  if(BUF->type == htons(UIP_ETHTYPE_IP)) {
		uip_arp_ipin();
		uip_input();
		/* If the above function invocation resulted in data that
		should be sent out on the network, the global variable
		uip_len is set to a value > 0. */
		if(uip_len > 0) {
		  uip_arp_out();
		  tapdev_send(uip_buf,uip_len);
		}
	  }
	  else if(BUF->type == htons(UIP_ETHTYPE_ARP))
	  {
		uip_arp_arpin();
		/* If the above function invocation resulted in data that
		should be sent out on the network, the global variable
		uip_len is set to a value > 0. */
		if(uip_len > 0) {
		  tapdev_send(uip_buf,uip_len);
		}
	  }
	}
	else if(timer_expired(&periodic_timer)) {
	  timer_reset(&periodic_timer);
	  for(i = 0; i < UIP_CONNS; i++) {
		uip_periodic(i);
		/* If the above function invocation resulted in data that
		should be sent out on the network, the global variable
		uip_len is set to a value > 0. */
		if(uip_len > 0) {
		  uip_arp_out();
		  tapdev_send(uip_buf,uip_len);
		}
	  }
#if UIP_UDP
	  for(i = 0; i < UIP_UDP_CONNS; i++) {
		uip_udp_periodic(i);
		/* If the above function invocation resulted in data that
		should be sent out on the network, the global variable
		uip_len is set to a value > 0. */
		if(uip_len > 0) {
		  uip_arp_out();
		  tapdev_send();
		}
	  }
#endif /* UIP_UDP */
	  /* Call the ARP timer function every 10 seconds. */
	  if(timer_expired(&arp_timer)) {
		timer_reset(&arp_timer);
		uip_arp_timer();
	  }
	}
  }
}

void swapToLayout(int page){
  if (isAnimating()) return;
  
  switch (page){
  case 0:
	//mainpage
	if (currentLayout == mainLayout) return;
	currentLayout = mainLayout;	
	break;
  case 1:
	if (currentLayout == learningLayout) return;
	currentLayout = learningLayout;
	break;
  case 2:
	if (currentLayout == graphLayout) return;
	currentLayout = graphLayout;
	break;
  case 3:
	if (currentLayout == devicesLayout) return;
	currentLayout = devicesLayout;
	break;
  }
  // Clear all graphics before changing page
  CLEAR_SCREEN();
  Layout_drawWindows(currentLayout);
  Layout_drawWindows(navigationBar);
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
