#include "includes.h"

#ifndef __UART_H
#define __UART_H

#define UART_MAX_BAUD_RATE    256000

// Define UARTs
typedef enum _UartNum_t
{
  UART_0 = 0, UART_1, UART_2, UART_3,
} UartNum_t;

typedef enum _UartMode_t
{
  NORM = 0, IRDA
} UartMode_t;

typedef enum _UartParity_t
{
  UART_ODD_PARITY = 0, UART_EVEN_PARITY,
  UART_FORCE_1_PARITY, UART_FORCE_0_PARITY,
  UART_NO_PARITY
} UartParity_t;

typedef enum _UartStopBits_t
{
  UART_ONE_STOP_BIT = 0, UART_TWO_STOP_BIT,
} UartStopBits_t;

typedef enum _UartWordWidth_t
{
  UART_WORD_WIDTH_5 = 0, UART_WORD_WIDTH_6,
  UART_WORD_WIDTH_7, UART_WORD_WIDTH_8
} UartWordWidth_t;

typedef struct _UartLineCoding_t
{
  Int32U          dwDTERate;
  UartStopBits_t  bStopBitsFormat;
  UartParity_t    bParityType;
  UartWordWidth_t bDataBits;
} UartLineCoding_t, * pUartLineCoding_t;

extern Int32U SYS_GetFpclk(Int32U Periphery);

void UartCheck(char * externBuffer);
void Uart0Isr(void);
Boolean UartInit(UartNum_t Uart,Int32U IrqSlot, UartMode_t UartMode);
void UartSetLineCoding(UartNum_t Uart,UartLineCoding_t UartCoding);
void UartCalcDivider(Int32U Freq, Int32U Baud, pInt32U pDiv, pInt32U pAddDiv, pInt32U pMul);

#endif // __UART_H
