#include "includes.h"

#ifndef __XML_H
#define __XML_H


#define XML_DATA_SIZE 3650
#define XML_DEVICES_SIZE 300
#define XML_ENTRY_SIZE 100
#define TAG_START_LENGTH 3
#define TAG_END_LENGTH 4

#define XML_DATA 0
#define XML_DEVICES 1

static void XML_copyString(const char * string, char * array, int * length);
static void XML_startTag(char id, char * array, int * length);
static void XML_endTag(char id, char * array, int * length);
static void XML_addDouble(double value, char * array, int * length);
static void XML_addNode(double value, char id, char * array, int * length);
static void XML_addTime();
static void XML_addStates(char deviceStates);
void XML_addMeasurement(Measurement * m, char deviceStates);
void XML_addDevice(char * name);
void XML_clearDevices();
char * XML_getContent(char which);
int XML_getLength(char which);

#endif // __XML_H
