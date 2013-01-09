#ifndef __PARSING_H
#define __PARSING_H

#define VOLTAGE_GAIN 95.291
#define VOLTAGE_OFFSET 1.5293
#define CURRENT_GAIN 6.7012
#define CURRENT_OFFSET 0.0017
#define POWER_GAIN 0.0012
#define POWER_OFFSET 10404

typedef struct{
  double voltage;
  double current;
  double P_power;
} Measurement;

void parse(char * Buffer, Measurement * measurement);
#endif
