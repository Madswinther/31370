#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#define MAX_PROGRESS 1000

typedef struct {
  	char type;
	short progress, oldProgress;
	short x0, y0;
	short width, height;
	int backgroundColor;
	int foregroundColor;
} ProgressBar;


ProgressBar * ProgressBar_Init(int x0, int y0, int width, int height, int foreGroundColor, int backgroundColor);

static int getPixelWidth(int progress, int width);
void ProgressBar_DrawFull(ProgressBar * pbar);
char ProgressBar_Update(void * object, int newProgress);

#endif
