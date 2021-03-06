#include "httpd.h"
#include "includes.h"
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
	file->data = XML_getContent(XML_DATA);
	file->len = XML_getLength(XML_DATA);
	return 1;
  }
  else if (httpd_fs_strcmp(name, "/devices.xml") == 0){
	file->data = XML_getContent(XML_DEVICES);
	file->len = XML_getLength(XML_DEVICES);
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

