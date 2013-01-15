#include <inttypes.h>

#ifndef __PARSING_H
#define __PARSING_H

#define VOLTAGE_GAIN 95.929
#define CURRENT_GAIN 6.7242
#define P_POWER_GAIN 0.001244
#define Q_POWER_GAIN 0.001
#define H_POWER_GAIN 0.01

#define VOLTAGE_PARSE_OFFSET 1
#define CURRENT_PARSE_OFFSET 9
#define P_POWER_PARSE_OFFSET 17
#define Q_POWER_PARSE_OFFSET 25
#define H_POWER_PARSE_OFFSET 33

typedef struct{
  double voltage;
  double current;
  double P_power;
  double Q_power;
  double H_power;
} Measurement;



void parse(char * Buffer, Measurement * measurement);
static double convertVoltage(int Vrms);
static double convertCurrent(int Irms);
static double convertP_power(int P_power);
static double convertQ_power(int Q_power);
static double convertH_power(int H_power);
#endif
