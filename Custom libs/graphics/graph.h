#include "includes.h"

#ifndef __GRAPH_H
#define __GRAPH_H

#define GRAPH_BACK_COLOR 	0xFFFFFF
#define GRAPH_LINE_COLOR 	0x0000FF
#define GRAPH_STROKE_COLOR	0x000000

#define MARGIN_TOP			10
#define MARGIN_BOTTOM		10
#define MARGIN_LEFT			40
#define MARGIN_RIGHT		0

#define X_AXIS				0
#define Y_AXIS				1


extern FontType_t Terminal_9_12_6;

typedef struct {
	int x0, y0;
	int width, height;
	double x_min, x_max;
	double y_min, y_max;
	char * title;
	char * xlabel;
	char * ylabel;
	int axis_x0, axis_y0;
	int axis_width, axis_height;
} Graph;


Graph * Graph_init(int x0, int y0, int width, int height);

void Graph_xlim(Graph * graph, double x_min, double x_max);
void Graph_ylim(Graph * graph, double y_min, double y_max);
void Graph_title(Graph * graph, char * str);
void Graph_xlabel(Graph * graph, char * str);
void Graph_ylabel(Graph * graph, char * str);


void Graph_drawAxisNumber(Graph * graph, char axis, double pos);
void Graph_draw(Graph * graph);

#endif
