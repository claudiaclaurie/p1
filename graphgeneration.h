
#ifndef __GRAPHGENERATION__
#define __GRAPHGENERATION__

extern REM_EDGES;

void g_free(edge** g, int numpoints);
edge **generate_graph(int numpoints, int dimension, graph_node* ptarray);
float throw(int numpoints, int dimension);


#endif 