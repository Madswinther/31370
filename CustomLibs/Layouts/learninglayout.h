#include "includes.h"

#ifndef __LEARNINGLAYOUT_H
#define __LEARNINGLAYOUT_H

extern Measurement * getMeasurement();

extern char Buffer[BUFFER_SIZE];

Layout * initLearningLayout();
void doLearn();
static void nextLetter();
static void previousLetter();
static void addToWord();
static char resetTimeout(void * null, int newValue);
static void resetAll();

#endif
