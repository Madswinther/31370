#include "includes.h"


static char XML_Data[XML_DATA_SIZE];
static int XML_Data_Length = 0;

static char XML_Devices[XML_DEVICES_SIZE];
static int XML_Devices_Length = 0;

const char * xml_header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

// Copy a string into current position in xml buffer
static void XML_copyString(const char * string, char * array, int * length){	
  while (*string != '\0') {
	array[(*length)++] = *(string++);
  }
}

// Add start tag of an xml node
static void XML_startTag(char id, char * array, int * length){
  array[(*length)++] = '<';
  array[(*length)++] = id;
  array[(*length)++] = '>';
}

// Add end tag of an xml node
static void XML_endTag(char id, char * array, int * length){
  array[(*length)++] = '<';
  array[(*length)++] = '/';
  array[(*length)++] = id;
  array[(*length)++] = '>';
}

// Convert double to string and add to buffer
static void XML_addDouble(double value, char * array, int * length){
  char temp[8];
  
  // handle sign
  if (value < 0) {
	temp[0] = '-';
	value *= -1;
  } else {
	temp[0] = ' ';
  }
  
  // Convert to string
  int integers = (int)value;
  int decimals = (int)((value-integers)*100);
  snprintf(temp, 8, "%03d.%02d", integers, decimals);
  
  // Add to xml_buffer
  XML_copyString(temp, array, length);
}

// Add single child node to the xml file
static void XML_addNode(double value, char id, char * array, int * length){
  XML_startTag(id, array, length);
  XML_addDouble(value, array, length);
  XML_endTag(id, array, length);
}

static void XML_addTime(){
  XML_startTag('T', XML_Data, &XML_Data_Length);
  
  // Get current time
  char seconds = RTC_getSeconds();
  char minutes = RTC_getMinutes();
  char hours = RTC_getHours();
  
  // Format as HHMMSS and add to data
  char temp[7];
  snprintf(temp, 7, "%02d%02d%02d", hours, minutes, seconds);
  XML_copyString(temp, XML_Data, &XML_Data_Length);
  
  XML_endTag('T', XML_Data, &XML_Data_Length);
}

static void XML_addStates(char deviceStates){
  XML_startTag('S', XML_Data, &XML_Data_Length);
  XML_Data[XML_Data_Length++] = deviceStates/10+0x30;
  XML_Data[XML_Data_Length++] = deviceStates%10+0x30;
  XML_endTag('S', XML_Data, &XML_Data_Length);
}


// Add one measurement to the xml file
void XML_addMeasurement(Measurement * m, char deviceStates) {
  
  // Check for free space in the xml file
  if (XML_Data_Length + XML_ENTRY_SIZE >= XML_DATA_SIZE) return;
  
  // If this is first measurement to be added, add xml header and root element
  if (XML_Data_Length == 0) {
	XML_copyString(xml_header, XML_Data, &XML_Data_Length);
	XML_startTag('D', XML_Data, &XML_Data_Length);
  } else {
	// If this is not the first element to be added, 
	// overwrite the end tag of the root element
	XML_Data_Length -= TAG_END_LENGTH;
  }
  
  // Add measurement nodes
  XML_startTag('M', XML_Data, &XML_Data_Length);
  XML_addNode(m->voltage, 'V', XML_Data, &XML_Data_Length);
  XML_addNode(m->current, 'I', XML_Data, &XML_Data_Length);
  XML_addNode(m->P_power, 'P', XML_Data, &XML_Data_Length);
  XML_addNode(m->Q_power, 'Q', XML_Data, &XML_Data_Length);
  XML_addNode(m->H_power, 'H', XML_Data, &XML_Data_Length);
  XML_addTime();
  XML_addStates(deviceStates);
  XML_endTag('M', XML_Data, &XML_Data_Length);
  
  // End root element
  XML_endTag('D', XML_Data, &XML_Data_Length);
}

// Add a new device to the XML file
void XML_addDevice(char * name){
  
  // If this is first measurement to be added, add xml header and root element
  if (XML_Devices_Length == 0) {
	XML_copyString(xml_header, XML_Devices, &XML_Devices_Length);
	XML_startTag('D', XML_Devices, &XML_Devices_Length);
  } else {
	// If this is not the first element to be added, 
	// overwrite the end tag of the root element
	XML_Devices_Length -= TAG_END_LENGTH;
  }
  
  // Name is always 5 bytes long
  XML_startTag('N', XML_Devices, &XML_Devices_Length);
  XML_copyString(name, XML_Devices, &XML_Devices_Length);
  XML_endTag('N', XML_Devices, &XML_Devices_Length);
  
  // End root element
  XML_endTag('D', XML_Devices, &XML_Devices_Length);
}

void XML_clearDevices(){
  // Reset XML file for devices
  XML_Devices_Length = 0;
}

char * XML_getContent(char which){
  if (which == XML_DATA) return XML_Data;
  if (which == XML_DEVICES) return XML_Devices;
  
  // Unknown
  return NULL;
}

int XML_getLength(char which){
  if (which == XML_DATA) return XML_Data_Length;
  if (which == XML_DEVICES) return XML_Devices_Length;
  
  // Unknown
  return 0;
}