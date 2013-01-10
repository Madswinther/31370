#ifndef __PARSING_H
#define __PARSING_H

#define VOLTAGE_GAIN 95.929
#define CURRENT_GAIN 6.7242
#define POWER_GAIN 0.0012
#define POWER_OFFSET 10404

#define VOLTAGE_PARSE_OFFSET 1
#define CURRENT_PARSE_OFFSET 9
#define POWER_PARSE_OFFSET 18

typedef struct{
  double voltage;
  double current;
  double P_power;
} Measurement;

void parse(char * Buffer, Measurement * measurement);
#endif
