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


ProgressSpinner * ProgressSpinnerInit(int x0, int y0, int size, int borderColor);

int getPixelWidth(int progress, int width);
char ProgressSpinnerUpdate(void * object, int newProgress);
void cancelProgressSpinner(ProgressSpinner * pspinner);

#endif
