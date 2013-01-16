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
  
  // Compute normalizing factor
  double scale = pow(measurement->voltage / 235.0, 2);
  
  // Get current
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+CURRENT_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  int current = strtol(temp, NULL, 16);
  measurement->current = convertCurrent(current);
  
  // Get P Power
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+P_POWER_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  int power = strtol(temp, NULL, 16);
  double pACT = convertP_power(power);
  
  measurement->P_power = scale * pACT;
  
  // Get Reactive Power
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+Q_POWER_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  power = strtol(temp, NULL, 16);
  double pREAC = convertQ_power(power);
  
  measurement->Q_power = scale * pREAC;
  
  // Get Harmonic Power
  for (int j=0; j<9; j++){
	temp[j] = Buffer[j+H_POWER_PARSE_OFFSET];
  }
  temp[8] = '\0';
  
  power = strtol(temp, NULL, 16);
  double pHAR = convertH_power(power);
  
  measurement->H_power = scale * pHAR;
}

static double convertVoltage(int Vrms){
  return Vrms * VOLTAGE_GAIN * pow(2,-22);
}

static double convertCurrent(int Irms) {
  return Irms * CURRENT_GAIN * pow(2,-22);
}

static double convertP_power(int P_power){
  if (P_power >= 0x800000) {
	P_power ^= 0xFFFFFF;
	P_power += 1;
  }
  if (P_power < 0) P_power = 0;
  
  return P_power * P_POWER_GAIN;
}

static double convertQ_power(int Q_power){
  if (Q_power >= 0x800000) {
	Q_power ^= 0xFFFFFF;
	Q_power += 1;
  }
  
  return Q_power * Q_POWER_GAIN;
}

static double convertH_power(int H_power){
  if (H_power >= 0x800000) {
	H_power ^= 0xFFFFFF;
	H_power += 1;
  }
  
  return H_power * H_POWER_GAIN;
}