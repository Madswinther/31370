#define UART_GLOBAL
#include "uart.h"

static char UART_Buffer[BUFFER_SIZE];
static int iterator = 0;
char RxFlag = 0;

void UartCheck(char * externUART_Buffer){
  if (RxFlag){	
	// Flag is high, copy the contents of the internal UART buffer to the main
	// Buffer
	for (int i=0; i<BUFFER_SIZE; i++){
	  externUART_Buffer[i] = UART_Buffer[i];
	  
	  // Clear the internal UART buffer
	  UART_Buffer[i] = 0;
	}
	RxFlag = 0;
  }
  else{
	// A full command has not been received yet.
	externUART_Buffer[0] = 'E';
  }
}

static void Uart0Isr(void){
  //Int32U UartIntId = U0IIR, LineStatus, Counter;
  
  // RxFlag must be low and first character must equal
  // Z for the transmission to be valid
  if (!RxFlag){
	if (iterator == 0){
	  if (U0RBR == 'Z'){
		// Starting character received
		UART_Buffer[iterator] = 'Z';
		iterator = 1;
	  }
	}
	else{
	  // Transmission has been started by a valid character, just continue streaming
	  UART_Buffer[iterator] = U0RBR;
	  iterator++;
	  
	  // Check for carriage return. This signified the end of a transmission
	  if (iterator >= BUFFER_SIZE || UART_Buffer[iterator-1] == '\r'){
		iterator = 0;
		
		// Set the flag high to allow the buffer to be passed onto the main program
		RxFlag = 1;
	  }
	}
  }
  else{
	// U0RBR must always be read
	if (U0RBR == 0);
  }
  VICADDRESS = 0;  // Clear interrupt in VIC.
}


Boolean UartInit(UartNum_t Uart,Int32U IrqSlot, UartMode_t UartMode){
  volatile Int8U Tmp;
  // Init buffer
  for (int i=0; i<BUFFER_SIZE; i++){
	UART_Buffer[i] = 0;
  }
  RxFlag = 0;
  
  // Enable UART0
  PCONP_bit.PCUART0 = 1;
  // Assign Port 0,1 to UART0
  // TX
  PINSEL0_bit.P0_2 = 1;
  // RX
  PINSEL0_bit.P0_3 = 1;
  
  U0LCR = 0x03; // Word Length =8, no parity , 1 stop
  U0FCR = 0x7;  // Enable and Clear the UART0 FIFO, Set RX FIFO interrupt level - 1 char
  // Transmit enable
  U0TER_bit.TXEN = 1;
  Tmp = U0IER;  // Clear pending interrupts
  // enable RBR Interrupt
  U0IER = 0x01;
  
  VIC_SetVectoredIRQ(Uart0Isr,IrqSlot,VIC_UART0);
  VICINTENABLE |= 1<<VIC_UART0;
  
  // Set up Line Coding
  UartLineCoding_t UartLineCoding;  
  UartLineCoding.dwDTERate = 115200;	// Update the baud rate
  UartLineCoding.bStopBitsFormat = UART_ONE_STOP_BIT;	// Update the stop bits number
  UartLineCoding.bParityType = UART_NO_PARITY;	// Update the parity type
  UartLineCoding.bDataBits = UART_WORD_WIDTH_8;	// Update the word width
  UartSetLineCoding(UART_0,UartLineCoding);	// Set UART line coding
  
  return(TRUE);
}

/*************************************************************************
* Function Name: UartSetLineCoding
* Parameters:  UartNum_t Uart,UartLineCoding_t pUartCoding
*
* Return: None
*
* Description: Init UART Baud rate, Word width, Stop bits, Parity type
*
*************************************************************************/
void UartSetLineCoding(UartNum_t Uart,UartLineCoding_t UartCoding)
{
  Int32U Mul, Div, AddDiv, Freq;
  
  // Check parameters
  if ((UartCoding.dwDTERate == 0) || (UartCoding.dwDTERate > UART_MAX_BAUD_RATE))
  {
    return;
  }
  Freq = SYS_GetFpclk(UART0_PCLK_OFFSET);
  UartCalcDivider(Freq,UartCoding.dwDTERate,&Div,&AddDiv,&Mul);
  U0LCR_bit.WLS = UartCoding.bDataBits;
  U0LCR_bit.SBS = UartCoding.bStopBitsFormat;
  U0LCR_bit.PE  =(UartCoding.bParityType == UART_NO_PARITY)?0:1;
  U0LCR_bit.PS  = UartCoding.bParityType;
  U0LCR_bit.DLAB = 1;
  U0DLL = Div & 0xFF;
  U0DLM = (Div >> 8) & 0xFF;
  U0FDR = AddDiv + (Mul << 4);
  U0LCR_bit.DLAB = 0;
}

static void UartCalcDivider(Int32U Freq, Int32U Baud,
							pInt32U pDiv, pInt32U pAddDiv, pInt32U pMul)
{
  Int32U Temp, Error = (Int32U)-1;
  Int32U K1, K2, K3, Baudrate;
  Int32U DivTemp, MulTemp, AddDivTemp;
  
  //
  for(MulTemp = 1; MulTemp < 16; ++MulTemp)
  {
    K1 = Freq*MulTemp;
    for(AddDivTemp = 1; AddDivTemp < 16; ++AddDivTemp)
    {
      K3 = (MulTemp + AddDivTemp)<<4;
      K2 =  K3 * Baud;
      DivTemp = K1/K2;
      // if DIVADDVAL>0, UnDL must be UnDL >= 0x0002 or the UART will
      // not operate at the desired baud-rate!
      if(DivTemp < 2)
      {
        continue;
      }
      Baudrate = DivTemp * K3;
      Baudrate = K1/Baudrate;
      Temp = (Baudrate > Baud)? \
		(Baudrate - Baud): \
		  (Baud - Baudrate);
		  if (Temp < Error)
		  {
			Error = Temp;
			*pDiv = DivTemp;
			*pMul = MulTemp;
			*pAddDiv = AddDivTemp;
			if(Error == 0)
			{
			  return;
			}
		  }
    }
  }
}

