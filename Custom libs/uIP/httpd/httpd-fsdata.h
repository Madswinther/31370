/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: httpd-fsdata.h 47021 2011-09-27 16:58:17Z anderslu $
 */
#ifndef __HTTPD_FSDATA_H__
#define __HTTPD_FSDATA_H__

#include "../uip.h"

struct httpd_fsdata_file {
  const struct httpd_fsdata_file *next;
  const char *name;
  const char *data;
  const int len;
#ifdef HTTPD_FS_STATISTICS

#if HTTPD_FS_STATISTICS == 1
  u16_t count;
#endif /* HTTPD_FS_STATISTICS */

#endif /* HTTPD_FS_STATISTICS */
};

struct httpd_fsdata_file_noconst {
  struct httpd_fsdata_file *next;
  char *name;
  char *data;
  int len;
#ifdef HTTPD_FS_STATISTICS
#if HTTPD_FS_STATISTICS == 1
  u16_t count;
#endif /* HTTPD_FS_STATISTICS */
#endif /* HTTPD_FS_STATISTICS */
};

extern const struct httpd_fsdata_file file_index_html;
extern const struct httpd_fsdata_file file_testmis_html;
//extern const struct httpd_fsdata_file file_404_html;
//extern const struct httpd_fsdata_file file_style_css;
extern const struct httpd_fsdata_file file_test_xml;


#define HTTPD_FS_ROOT &file_test_xml
#define HTTPD_FS_NUMFILES 3


#endif /* __HTTPD_FSDATA_H__ */