#include "graph.h"
#include "includes.h"

// Initialize the graph window
Graph * Graph_init(int x0, int y0, int width, int height) {
  
  Graph * graph = (Graph *)malloc(sizeof(Graph));
  
  graph->x0 = x0;
  graph->y0 = y0;
  graph->width = width;
  graph->height = height;
  
  graph->axis_x0 = x0 + MARGIN_LEFT;
  graph->axis_y0 = y0 + MARGIN_TOP;
  graph->axis_width = width - MARGIN_LEFT - MARGIN_RIGHT;
  graph->axis_height = graph->height - MARGIN_TOP - MARGIN_BOTTOM;
  
  return graph;
}

void Graph_xlim(Graph * graph, double x_min, double x_max) {
  graph->x_min = x_min;
  graph->x_max = x_max;
}

void Graph_ylim(Graph * graph, double y_min, double y_max) {
  
  graph->y_min = y_min;
  graph->y_max = y_max;
}

void Graph_title(char * str) {
	graph->title = str;
}

void Graph_xlabel(char * str) {
	graph->xlabel = str;
}

void Graph_ylabel(char * str){
	graph->ylabel = str;
}

void Graph_drawAxisNumber(Graph * graph, char axis, double pos) {
  
	int x0, y0, x1, y1;
	
	// Check for invalid positions
	if (pos > 100) pos = 100;
	if (pos < 0) pos = 0;
	
	
	// Check for axis: 0 = X, 1 = Y
	if (axis == X_AXIS) {
		
		// Calculate number corresponding to relative position
		double number = (pos / 100.0) * (graph->x_max - graph->x_min) + graph->x_min;
		
		// Calculate text position and window dimensions
		x0 = graph->axis_x0 + (pos/100.0) * graph->axis_width - 3*Terminal_9_12_6.H_Size;
		y0 = graph->axis_y0 + graph->axis_height;
		x1 = x0 + Terminal_9_12_6.H_Size * 6;
		y1 = y0 + Terminal_9_12_6.V_Size;
			
	} else {
		// Calculate number corresponding to relative position
		double number = (pos / 100.0) * (graph->y_max - graph->y_min) + graph->y_min;
	
		// Calculate text position and window dimensions
		x0 = graph->x0 + 2;
		y0 = (int)(graph->axis_y0 + graph->axis_height - (pos / 100.0) * graph->axis_height - Terminal_9_12_6.V_Size/2);
		x1 = x0 + Terminal_9_12_6.H_Size * 6;
		y1 = y0 + Terminal_9_12_6.V_Size;
	}
	
	// Draw text
	GLCD_SetWindow(x0,y0,x1,y1);
	GLCD_SetFont(&Terminal_9_12_6, 0xFFFFFF, 0x0);
	GLCD_TextSetPos(0,0);
	GLCD_print("%.2f", number);
}



void Graph_draw(Graph * graph) {
  
  // Draw background of the graph
  drawFilledRectangle(graph->axis_x0, graph->axis_y0, 
						graph->axis_width, graph->axis_height, 
						GRAPH_BACK_COLOR, GRAPH_STROKE_COLOR, 1);
  
  // Draw x-axis numbers
  for (char i = 0; i < 6; i++) {
	Graph_drawAxisNumber(graph, X_AXIS, i * 20.0);
  }
  
  
  // Draw y-axis numbers
  for (char i = 0; i < 3; i++) {
	Graph_drawAxisNumber(graph, Y_AXIS, i * 50.0);
  }
  
}














