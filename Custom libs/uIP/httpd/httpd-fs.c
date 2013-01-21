#include "httpd.h"
#include "httpd-fs.h"
#include "httpd-fsdata.h"
#include "../Custom libs/parsing.h"
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif

//#include "httpd-fsdata.c"


#if HTTPD_FS_STATISTICS
static u16_t count[HTTPD_FS_NUMFILES];
#endif /* HTTPD_FS_STATISTICS */

#define XML_DATA_SIZE 3650
#define XML_ENTRY_SIZE 15
#define TAG_START_LENGTH 3
#define TAG_END_LENGTH 4

static char XML_Data[XML_DATA_SIZE];
static int XML_Length = 0;

const char * xml_header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

// Copy a string into current position in xml buffer
void XML_copyString(const char * string) {	
	while (*string != '\0') {
		XML_Data[XML_Length++] = *(string++);
	}
}

// Add start tag of an xml node
void XML_startTag(char id) {
	XML_Data[XML_Length++] = '<';
	XML_Data[XML_Length++] = id;
	XML_Data[XML_Length++] = '>';
}

// Add end tag of an xml node
void XML_endTag(char id) {
	XML_Data[XML_Length++] = '<';
	XML_Data[XML_Length++] = '/';
	XML_Data[XML_Length++] = id;
	XML_Data[XML_Length++] = '>';
}

// Convert double to string and add to buffer
void XML_addDouble(double value) {
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
	XML_copyString(temp);
}
	
// Add single child node to the xml file
void XML_addNode(double value, char id) {
	XML_startTag(id);
	XML_addDouble(value);
	XML_endTag(id);
}

// Add one measurement to the xml file
void XML_addMeasurement(Measurement * m) {
	
	// Check for free space in the xml file
	if (XML_Length + XML_ENTRY_SIZE >= XML_DATA_SIZE) return;
	
	// If this is first measurement to be added, add xml header and root element
	if (XML_Length == 0) {
		XML_copyString(xml_header);
		XML_startTag('D');
	} else {
		// If this is not the first element to be added, 
		// overwrite the end tag of the root element
		XML_Length -= TAG_END_LENGTH;
	}

	// Add measurement nodes
	XML_startTag('M');
	XML_addNode(m->voltage, 'V');
	XML_addNode(m->current, 'I');
	XML_addNode(m->P_power, 'P');
	XML_addNode(m->Q_power, 'Q');
	XML_addNode(m->H_power, 'H');
	XML_endTag('M');
	
	// End root element
	XML_endTag('D');
}





static u8_t httpd_fs_strcmp(const char *str1, const char *str2) {
  u8_t i;
  i = 0;
loop:
  
  if(str2[i] == 0 || str1[i] == '\r' || str1[i] == '\n') {
	return 0;
  }
  
  if(str1[i] != str2[i]) {
	return 1;
  }
  
  ++i;
  goto loop;
}


int httpd_fs_open(const char *name, struct httpd_fs_file *file) {
	#if HTTPD_FS_STATISTICS
	u16_t i = 0;
	#endif /* HTTPD_FS_STATISTICS */
  
  
  if (httpd_fs_strcmp(name, "/data.xml") == 0){
	file->data = (char *) XML_Data;
	file->len = XML_Length;
	return 1;
  }
  
  
  struct httpd_fsdata_file_noconst *f;
  
  for(f = (struct httpd_fsdata_file_noconst *)HTTPD_FS_ROOT;
	  f != NULL;
	  f = (struct httpd_fsdata_file_noconst *)f->next) {
		
		if(httpd_fs_strcmp(name, f->name) == 0) {
		  file->data = f->data;
		  file->len = f->len;
#if HTTPD_FS_STATISTICS
		  ++count[i];
#endif /* HTTPD_FS_STATISTICS */
		  return 1;
		}
#if HTTPD_FS_STATISTICS
		++i;
#endif /* HTTPD_FS_STATISTICS */
		
	  }
  return 0;
}

void httpd_fs_init(void) {
#if HTTPD_FS_STATISTICS
  u16_t i;
  for(i = 0; i < HTTPD_FS_NUMFILES; i++) {
	count[i] = 0;
  }
#endif /* HTTPD_FS_STATISTICS */
}


#if HTTPD_FS_STATISTICS
u16_t httpd_fs_count (char *name) {
  
  struct httpd_fsdata_file_noconst *f;
  u16_t i;
  
  i = 0;
  for(f = (struct httpd_fsdata_file_noconst *)HTTPD_FS_ROOT;
	  f != NULL;
	  f = (struct httpd_fsdata_file_noconst *)f->next) {
		
		if(httpd_fs_strcmp(name, f->name) == 0) {
		  return count[i];
		}
		++i;
	  }
  return 0;
}
#endif /* HTTPD_FS_STATISTICS */

