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

void Graph_setXscale(Graph * graph, double x_min, double x_max) {
  graph->x_min = x_min;
  graph->x_max = x_max;
}

void Graph_setYscale(Graph * graph, double y_min, double y_max) {
  
  graph->y_min = y_min;
  graph->y_max = y_max;
}


void Graph_drawAxisNumber(Graph * graph, double number, double pos) {
  
  int x0, y0, x1, y1;
  
  if (pos > 100) pos = 100;
  if (pos < 0) pos = 0;
  
  // Calculate text position and window dimensions
  x0 = graph->x0 + 2;
  y0 = (int)(graph->axis_y0 + graph->axis_height - (pos / 100.0) * graph->axis_height - Terminal_9_12_6.V_Size/2);
  x1 = x0 + Terminal_9_12_6.H_Size * 6;
  y1 = y0 + Terminal_9_12_6.V_Size;

  GLCD_SetWindow(x0,y0,x1,y1);
  GLCD_SetFont(&Terminal_9_12_6, 0xFFFFFF, 0x0);
  GLCD_TextSetPos(0,0);
  GLCD_print("%.2f", number);
}


void Graph_draw(Graph * graph) {
  
  // Draw background of the graph
  drawFilledRectangle(graph->axis_x0, graph->axis_y0, graph->axis_width, graph->axis_height, GRAPH_BACK_COLOR, GRAPH_STROKE_COLOR, 1);
  
  // Draw vertical axis numbers
  Graph_drawAxisNumber(graph, graph->y_max, 100.0);
  Graph_drawAxisNumber(graph, 0.5 * (graph->y_max - graph->y_min) + graph->y_min, 50.0);
  Graph_drawAxisNumber(graph, graph->y_min, 0.0);
  
  
}

