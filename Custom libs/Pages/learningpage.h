#include "../layout.h"
#include "mainpage.h"

#ifndef __LEARNINGPAGE_H
#define __LEARNINGPAGE_H

extern Measurement * getMeasurement();

extern char Buffer[BUFFER_SIZE];

Page * initLearningPage();
void doLearn();

#endif
