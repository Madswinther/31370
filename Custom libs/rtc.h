#include "includes.h"

#ifndef __RTC_H
#define __RTC_H

void RTC_init();

char RTC_getSeconds();
char RTC_getMinutes();
char RTC_getHours();
void RTC_setTime(char seconds, char minutes, char hours);

#endif // __RTC_H
