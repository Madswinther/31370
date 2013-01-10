#include "includes.h"

#ifndef __GUI_H
#define __GUI_H

typedef struct{
  int left, right, top, bottom;
  Bmp_t * picture;
  char clickable;
} Window;

Window * initWindow(int left, int top, int right, int bottom, Bmp_t * pic);
void draw(Window * window);
char onClick(Window * window, int x, int y);

#endif // __GUI_H
