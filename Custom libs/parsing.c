#include "parsing.h"
#include <stdlib.h>
#include <math.h>

void parse(char * Buffer, Measurement * measurement){
  // Iterator
  int i = 0;
  
  // Get voltage
  while(Buffer[i++] != 'x');
  
  char temp[9];
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+i+1];
  }
  temp[8] = '\0';
  
  double voltage = strtol(temp, NULL, 16);
  measurement->voltage = (double)voltage*pow(2, -22)*VOLTAGE_GAIN;
  
  // Get current
  i += 8;
  while(Buffer[i++] != 'x');
  
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+i+1];
  }
  temp[8] = '\0';
  
  double current = strtol(temp, NULL, 16);
  measurement->current = ((double)current*pow(2, -22))*CURRENT_GAIN+CURRENT_OFFSET;
  
  // Get Power
  i += 8;
  while(Buffer[i++] != 'x');
  
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+i+1];
  }
  temp[8] = '\0';
  
  int power = strtol(temp, NULL, 16);
  double pACT = (double)(power & ~(1<<23));
  if (power & (1<<23)){
	pACT *= -1;
  }
  pACT = pACT*POWER_GAIN+POWER_OFFSET;
  
  measurement->P_power = pACT;
}