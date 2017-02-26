
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"
#include "graphgeneration.h"

int REM_EDGES = 0;
// Get rid of memory so there is room for edges
void g_free(edge** g, int numpoints) {

	int n;

	for (n = 0; n < numpoints; n ++) {
		edge* current = g[n];
		if (current) {
			edge* selected = current -> next;
			free(current);
			current = selected;
		}
	}
	free(g);
}


float throw(int numpoints, int dimension){
	if (dimension == 0){
		return 16.0 / (pow(log2((float)numpoints), 3));
	}
	else if (dimension == 2){
		return 16.0 / (pow(log2((float)numpoints), 3));
	}
	else if (dimension == 3){
		return  8.0 / (pow(log2((float)numpoints), 2));
	}
	else{
		return 4.0 / (pow(log2((float)numpoints), 3 / 2));
	
	}
}
// set up graph
edge **generate_graph(int numpoints, int dimension, graph_node* ptarray) {
	// seed pseudorandom number generator with time, always different
	srand48(time(NULL));
	int i;
	float cutoff = throw(numpoints, dimension);
	//allocate memory for the edges
	edge** g = malloc(sizeof(edge*)*numpoints);
	for (i = 0; i < numpoints; i++) {
		g[i] = NULL;
	}
	// array of all the points
	ptarray = malloc(sizeof(graph_node) * numpoints);
	// count number of edges after throwing away for optimization
	REM_EDGES = 0;

	switch (dimension) {
	case 0:
		cutoff;
		int i;
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float weight = rand() / (float)RAND_MAX;
				// prune
				if (weight <= cutoff) {
					edge* edge = malloc(sizeof(edge));
					edge->source = i, edge->target = j, edge->weight = weight;
					edge->next = g[i];
					g[i] = edge;
					REM_EDGES++;

			// Realloc for more space if cap reached
            //if (REM_EDGES >= cutoff) {
              //  edge = realloc(sizeof(edge));
				//}
			}

			}
		}
	case 2:
		cutoff;

		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX, ptarray[i].c = 0, ptarray[i].d = 0;
		}

		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				//euclidian math done here
				float cweight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2));
				if (cweight < cutoff) {
					edge* edge = malloc(sizeof(edge));
					edge->source = i, edge->target = j, edge->weight = cweight;
					edge->next = g[i];
					g[i] = edge;
					REM_EDGES++;
				}
			}
		}
	case 3:
		cutoff;

		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX,
			           ptarray[i].c = rand() / (float)RAND_MAX, ptarray[i].d = 0;
		}

		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				//euclidian calculations done here
				float cweight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2) + pow(ptarray[i].c - ptarray[j].c, 2));

				if (cweight < cutoff) {
					edge* edge = malloc(sizeof(edge));
					edge->source = i,
					      edge->target = j,
					            edge->weight = cweight;
					edge->next = g[i];
					g[i] = edge;
					REM_EDGES++;
				}
			}
		}
	default:
		cutoff;

		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX, ptarray[i].c = rand() / (float)RAND_MAX,
			           ptarray[i].d = rand() / (float)RAND_MAX;
		}
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {

				//euclidian calculation here
				float cweight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2) + pow(ptarray[i].c - ptarray[j].c, 2)
				                     + pow(ptarray[i].d - ptarray[j].d, 2));

				if (cweight < cutoff) {

					edge* edge = malloc(sizeof(edge));
					edge->source = i, edge->target = j, edge->weight = cweight;
					edge->next = g[i];
					g[i] = edge;
					REM_EDGES++;
				}
			}
		}
		return g;

	}

}

