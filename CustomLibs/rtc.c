#include "includes.h"


void RTC_init(){
  // Enable Clock for the RTC
  PCONP_bit.PCRTC = 1;
  
  // Use 32kHz internal oscillator
  CCR = 0;
  CCR_bit.CLKSRC = 1;
  
  // Disable ALL interrupts
  CIIR = 0;
  CISS = 0;
  
  // Reset current time(Will start the timer)
  RTC_setTime(0,0,0);
}

char RTC_getSeconds(){
  // Return bits 0-5 of CTIME0 register
  return SEC;
}

char RTC_getMinutes(){
  // Return bits 8-13 of CTIME0 register
  return MIN;
}

char RTC_getHours(){
  // Return bits 16-20 of CTIME0 register
  return HOUR;
}

void RTC_setTime(char hours, char minutes, char seconds){
  // Disable counting
  CCR_bit.CLKEN = 0;
  
  HOUR = hours;
  MIN = minutes;
  SEC = seconds;
  
  // Enable counting
  CCR_bit.CLKEN = 1;
}