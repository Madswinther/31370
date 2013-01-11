#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#define MAX_PROGRESS 1000

typedef struct {
	int progress, oldProgress;
	int x0, y0;
	int width, height;
	int backgroundColor;
	int foregroundColor;
} ProgressBar;


ProgressBar * ProgressBarInit(int x0, int y0, int width, int height, int foreGroundColor, int backgroundColor);

int getProgressPixelWidth(int progress, int width);
void ProgressBarDrawFull(ProgressBar * pbar);
void ProgressBarUpdate(ProgressBar * pbar, int newProgress);

#endif
