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

#define XML_DATA_SIZE 200
#define XML_ENTRY_SIZE 15
static char XML_Data[XML_DATA_SIZE];
static char iter = 0;

const Streng xml_str = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", 38};
const Streng d_token = {"<D>", 3};
const Streng d_token_end = {"</D>", 4};
const Streng m_token = {"<M>", 3};
const Streng m_token_end = {"</M>", 4};
const Streng v_token = {"<V>", 3};
const Streng v_token_end = {"</V>", 4};
const Streng i_token = {"<I>", 3};
const Streng i_token_end = {"</I>", 4};
const Streng p_token = {"<P>", 3};
const Streng p_token_end = {"</P>", 4};
const Streng q_token = {"<Q>", 3};
const Streng q_token_end = {"</Q>", 4};
const Streng h_token = {"<H>", 3};
const Streng h_token_end = {"</H>", 4};


// Add contents of tekst into the xml data buffer
void XML_addString(const Streng * tekst) {
	for (char j = 0; j < tekst->len; j++) {
		XML_Data[iter+j] = tekst->str[j];
	}
	iter += tekst->len;
}

// Add element to the xml data buffer
void XML_addValue(double value, Streng * tag_start, Streng * tag_end) {
	
	// Add start tag
	XML_addString(tag_start);

	// Convert double to string
	char temp[7];
	int integers = (int)value;
	int decimals = (int)((value-integers)*100);
	snprintf(temp, 7, "%03d.%02d", integers, decimals);
	
	// Add value string to the xml buffer
	for (char j=0; j < 6; j++){
		XML_Data[iter+j] = temp[j];
	}
	iter += 6;
	
	// Add end tag
	XML_addString(tag_end);
}

// Add measurement element to the xml
void XML_addMeasurement(Measurement * data) {

	// Check for file size limit exceeded
	if (iter+XML_ENTRY_SIZE >= XML_DATA_SIZE) return;

	
	// Is it the first element to be added to the xml-file?
	if (iter == 0){
		// Initialize XML buffer, add xml-header
		XML_addString(&xml_str);
		
		// Add start tag of root element
		XML_addString(&d_token);
		
	} else{
		// If this is not the first element, overwrite the end tag of root element 
		iter -= d_token_end.len;
	}
		
	// Add start tag
	XML_addString(&m_token);
	
	// Add elements of measurement
	XML_addValue(data->voltage, (Streng *)&v_token, (Streng *)&v_token_end);
	XML_addValue(data->current, (Streng *)&i_token, (Streng *)&i_token_end);
	XML_addValue(data->P_power, (Streng *)&p_token, (Streng *)&p_token_end);
	XML_addValue(data->Q_power, (Streng *)&q_token, (Streng *)&q_token_end);
	XML_addValue(data->H_power, (Streng *)&h_token, (Streng *)&h_token_end);

	// Add end tag of measurement
	XML_addString((Streng *)&m_token_end);
	
	// Add end tag of root element
	XML_addString((Streng *)&d_token_end);	
}


/*
void XML_addData(double value){

	// Check for file size limit exceeded
	if (iter+XML_ENTRY_SIZE >= XML_DATA_SIZE) return;

  
	if (iter == 0){
		// Initialize XML stream
		for (char j = 0; j <  xml_str.len; j++){
			XML_Data[j] = xml_str.str[j];
		}
		iter += xml_str.len;
		
		// Add the root element
		for (char j=0; j < d_token.len; j++){
		XML_Data[iter+j] = d_token.str[j];
		}
		iter += d_token.len;
	} else{
		iter -= d_token_end.len;
	}
  
	// Add header
	for (char j=0; j < v_token.len; j++){
		XML_Data[iter+j] = v_token.str[j];
	}
	iter += v_token.len;
  
  
  // Add data
  char temp[7];
  int integers = (int)value;
  int decimals = (int)((value-integers)*100);
  snprintf(temp, 7, "%03d.%02d", integers, decimals);
  for (char j=0; j < 6; j++){
	XML_Data[iter+j] = temp[j];
  }
  iter += 6;
  
  // Add footer
  for (char j = 0; j < v_token_end.len; j++){
	XML_Data[iter+j] = v_token_end.str[j];
  }
  iter += v_token_end.len;
  
  
  // At end of root element
  for (char j=0; j < d_token_end.len; j++){
	XML_Data[iter+j] = d_token_end.str[j];
  }
  iter += d_token_end.len;
}
*/





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
  
  
  if (httpd_fs_strcmp(name, "/mis.xml") == 0){
	file->data = (char *) XML_Data;
	file->len = iter;
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

