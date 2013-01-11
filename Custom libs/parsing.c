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
  
  int voltage = strtol(temp, NULL, 16);
  measurement->voltage = convertVoltage(voltage);
  
  // Get current
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+CURRENT_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  int current = strtol(temp, NULL, 16);
  measurement->current = convertCurrent(current);
  
  // Get Power
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+POWER_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  int power = strtol(temp, NULL, 16);
  double pACT = convertPower(power);
  
  measurement->P_power = pACT;
}

double convertVoltage(int Vrms){
	return Vrms * VOLTAGE_GAIN * pow(2,-22);
}
 
double convertCurrent(int Irms) {
	return Irms * CURRENT_GAIN * pow(2,-22);
}

double convertPower(int powerInt) {
 
	if (powerInt >= 0x800000) {
		powerInt ^= 0xFFFFFF;
		powerInt += 1;
	}
 
	return powerInt * POWER_GAIN;
}