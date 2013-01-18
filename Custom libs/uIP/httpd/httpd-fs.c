#include "httpd.h"
#include "httpd-fs.h"
#include "httpd-fsdata.h"
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

typedef struct {const char * str; const char len;}String;

const String xml_str = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", 38};
const String d_token = {"<D>", 3};
const String d_token_end = {"</D>", 4};
const String v_token = {"<V>", 3};
const String v_token_end = {"</V>", 4};

void XML_addData(double value){
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
  }
  else{
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

