#include "includes.h"
#include <stdlib.h>
#include <math.h>

#define NONPROT 0xFFFFFFFF
#define CRP1  	0x12345678
#define CRP2  	0x87654321
/*If CRP3 is selected, no future factory testing can be performed on the device*/
#define CRP3  	0x43218765

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


int main(void)
{
  char Buffer[50];
  // Init buffer
  for (int i=0; i<50; i++){
	Buffer[i] = 0;
  }
  pInt8U pBuffer;
  Int32U Size,TranSize;
  
  Boolean CdcConfigureStateHold;
  UartLineCoding_t UartLineCoding;  
  
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
  GLCD_Init (IarLogoPic.pPicStream, NULL);
  // Disable Hardware cursor
  GLCD_Cursor_Dis(0);
  // Init UART 0
  UartInit(UART_0,4,NORM);
  
  __enable_interrupt();
  
  // Enable GLCD
  GLCD_Ctrl (TRUE);
  
  GLCD_SetFont(&Terminal_9_12_6,0x0000FF,0x000cd4ff);
  GLCD_SetWindow(80,200,310,211);
  GLCD_TextSetPos(0,0);
  GLCD_print("\fCommunication device class");
  
  // Init UART
  // Update the baud rate
  UartLineCoding.dwDTERate = 115200;
  // Update the stop bits number
  UartLineCoding.bStopBitsFormat = UART_ONE_STOP_BIT;
  // Update the parity type
  UartLineCoding.bParityType = UART_NO_PARITY;
  // Update the word width
  UartLineCoding.bDataBits = UART_WORD_WIDTH_8;
  // Set UART line coding
  UartSetLineCoding(UART_0,UartLineCoding);
  
  int voltage = 0;
  int current = 0;
  int power = 0;
  
  GLCD_SetWindow(0,0,310,33);
  
  double VOLTAGE_GAIN = 95.87325813;
  double CURRENT_GAIN = 6.6416;
  double CURRENT_OFFSET = 0.0068; 
  
  while(1){
    // Data from UART1
	
	UartCheck(Buffer);
	
	if (Buffer[0] != 'E'){
 
	  // Get voltage
	  int i=0;
	  while(Buffer[i++] != 'x');
	  
	  
	  char temp[9];
	  for (int j=0; j<9; j++){
		temp[j] = Buffer[j+i+1];
	  }
	  temp[8] = '\0';
	  
	  voltage = strtol(temp, NULL, 16);
	  double vRMS = (double)voltage*pow(2, -22)*VOLTAGE_GAIN;
	  
	  // Get current
	  i += 8;
	  while(Buffer[i++] != 'x');
	  
	  for (int j=0; j<9; j++){
		temp[j] = Buffer[j+i+1];
	  }
	  temp[8] = '\0';
	  
	  current = strtol(temp, NULL, 16);
	  double iRMS = ((double)current*pow(2, -22))*CURRENT_GAIN+CURRENT_OFFSET;
	  
	  // Get Power
	  i += 8;
	  while(Buffer[i++] != 'x');
	  
	  for (int j=0; j<9; j++){
		temp[j] = Buffer[j+i+1];
	  }
	  temp[8] = '\0';
	  
	  power = strtol(temp, NULL, 16);
	  double pACT = ((double)(~(power & (1<<24)))*pow(2, -23));
	  if (power & (1<<24)){
		pACT *= -1;
	  }
	  
	  	GLCD_TextSetPos(0,0);
	  	GLCD_print(" Voltage: %f\r\n Current: %f\r\n Power: \t%f", vRMS, iRMS, pACT);
	}
  }
}
