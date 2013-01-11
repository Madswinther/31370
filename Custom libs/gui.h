#include "includes.h"
#include "../Custom libs/draw.h"
#include <string.h>

#define PICTUREWINDOW 0
#define RECTANGLEWINDOW 1
#define PROGRESSBAR 2

#ifndef __GUI_H
#define __GUI_H

extern FontType_t Terminal_9_12_6;

typedef struct{
  char type;
  int left, right, top, bottom;
  char clickable;
  void (*onClick)();
} Window;

typedef struct{
  char type;
  int left, right, top, bottom;
  char clickable;
  void (*onClick)();
  Bmp_t * picture;
} PictureWindow;

typedef struct{
  char type;
  int left, right, top, bottom;
  char clickable;
  void (*onClick)();
  int backgroundColor, borderColor;
  char * text;
} RectangleWindow;

PictureWindow * initPictureWindow(int left, int top, int right, int bottom, Bmp_t * pic);
RectangleWindow * initRectangleWindow(int left, int top, int right, int bottom, int color, int bordercolor);
void setText(void * window, char * text);
void setOnClick(void * window, void (*function)());
void drawWindow(void * window);
char onTouch(void * window, int x, int y);

#endif // __GUI_H
