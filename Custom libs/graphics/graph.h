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

#define GRAPH_DATA_POINTS	12



extern FontType_t Terminal_9_12_6;

typedef struct {
  	char type;
	int x0, y0;
	int width, height;
	double x_min, x_max;
	double y_min, y_max;
	int axis_x0, axis_y0;
	int axis_width, axis_height;
	char * title;
	char * xlabel;
	char * ylabel;
	int xpoints[GRAPH_DATA_POINTS];
	int ypoints[GRAPH_DATA_POINTS];
} Graph;


Graph * Graph_init(int x0, int y0, int width, int height, double y_min, double y_max);

void Graph_xlim(Graph * graph, double x_min, double x_max);
void Graph_title(Graph * graph, char * str);
void Graph_xlabel(Graph * graph, char * str);
void Graph_ylabel(Graph * graph, char * str);
int Graph_getPixelXCoord(Graph * graph, double xval);
int Graph_getPixelYCoord(Graph * graph, double yval);
void Graph_clear(Graph * graph);

void Graph_drawAxisNumber(Graph * graph, char axis, double pos);
void Graph_draw(Graph * graph);
void Graph_addPoint(Graph * graph, Graph * activeGraph, double y);
void Graph_plotPoints(Graph * graph);



#endif
