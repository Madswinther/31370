#include "includes.h"
#include "../Custom libs/draw.h"

#ifndef __GUI_H
#define __GUI_H


typedef struct{
  char type;
  int left, right, top, bottom;
  Bmp_t * picture;
  char clickable;
} PictureWindow;

typedef struct{
  char type;
  int left, right, top, bottom;
  Rectangle rectangle;
  char clickable;
} RectangleWindow;

PictureWindow * initPictureWindow(int left, int top, int right, int bottom, Bmp_t * pic);
RectangleWindow * initRectangleWindow(int left, int top, int right, int bottom, int color, int bordercolor);
void drawPictureWindow(PictureWindow * window);
void drawRectangleWindow(RectangleWindow * window);
char onPictureTouch(PictureWindow * window, int x, int y);
char onRectangleTouch(RectangleWindow * window, int x, int y);

#endif // __GUI_H
