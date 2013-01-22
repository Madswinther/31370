#include "includes.h"
#include <string.h>

#define PICTUREWINDOW 0
#define RECTANGLEWINDOW 1
#define PROGRESSBAR 2
#define GRAPH 3

#ifndef __GUI_H
#define __GUI_H

extern FontType_t Terminal_9_12_6;

typedef struct{
  char type;
  short left, right, top, bottom;
  char clickable;
  void (*onClick)();
} Window;

typedef struct{
  char type;
  short left, right, top, bottom;
  char clickable;
  void (*onClick)();
  Bmp_t * picture;
} PictureWindow;

typedef struct{
  char type;
  short left, right, top, bottom;
  char clickable;
  char hidden;
  void (*onClick)();
  int backgroundColor, borderColor;
  char * text;
} RectangleWindow;

PictureWindow * GUI_initPictureWindow(int left, int top, int right, int bottom, Bmp_t * pic);
RectangleWindow * GUI_initRectangleWindow(int left, int top, int right, int bottom, int color, int bordercolor);
void GUI_setText(void * window, char * text);
void GUI_setOnClick(void * window, void (*function)());
void GUI_drawWindow(void * window);
void GUI_setHidden(void * window, char hide);
char GUI_onTouch(void * window, int x, int y);

#endif // __GUI_H
