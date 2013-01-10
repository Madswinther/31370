#include "parsing.h"
#include <stdlib.h>
#include <math.h>

void parse(char * Buffer, Measurement * measurement){
  
  // Get voltage
  char temp[9];
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+VOLTAGE_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  double voltage = strtol(temp, NULL, 16);
  measurement->voltage = (double)voltage*pow(2, -22)*VOLTAGE_GAIN;
  
  // Get current
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+CURRENT_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  double current = strtol(temp, NULL, 16);
  measurement->current = ((double)current*pow(2, -22))*CURRENT_GAIN;
  
  // Get Power
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+POWER_PARSE_OFFSET];
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