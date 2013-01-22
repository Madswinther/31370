#ifndef PROGRESSSPINNER_H_
#define PROGRESSSPINNER_H_


typedef struct {
  	char type;
	short progressX, progressY;
	short x0, y0;
	short size;
	short animRadius;
	char reverse;
	char cancelled;
	int borderColor;
} ProgressSpinner;


ProgressSpinner * ProgressSpinner_Init(int x0, int y0, int size, int borderColor);

char ProgressSpinner_Update(void * object, int newProgress);
void ProgressSpinner_Cancel(ProgressSpinner * pspinner);

#endif
