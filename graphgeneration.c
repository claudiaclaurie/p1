
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"
#include "graphgeneration.h"

//Pruning count
int REM_EDGES = 0;
// Funcion to get rid of memory so there is room for edges and does not seg fault 
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
	//free the graph 
	free(g);
}
//Pruning function to determine which edges to throw away 
float throw (int numpoints, int dimension) {
	if (dimension == 0) {

		if (numpoints < 300) 
			return 1.0;
		if (numpoints > 10000) 
			return 0.00205;
		return (1.0/((double) numpoints * 0.0493 + 2.13589339));
		//return 1.0/((float)numpoints);
		
	//return 1 / (pow(log2((float)numpoints), 3));
	}
	else if (dimension == 2) {
		return 64.0 / (pow(log2((float)numpoints), 3));
	}
	else if (dimension == 3) {
		return  16.0 / (pow(log2((float)numpoints), 2));
	}
	else {
		return 8.0 / (pow(log2((float)numpoints), 1.4401));

	}
}

// Generate the graph for each dimensional case 
edge **generate_graph(int numpoints, int dimension, graph_node* ptarray) {
	// Seed pseudorandom number generator with time, always different
	srand48(time(NULL));
	int i;
	//Pruning value that gets called for each dimensional case
	
	//Allocate memory for the edges
	edge** g = malloc(sizeof(edge*)*numpoints);
	for (i = 0; i < numpoints; i++) {
		g[i] = NULL;
	}
	//Allocate memory for an array of all the points
	ptarray = malloc(sizeof(graph_node) * numpoints);
	float cutoff = throw (numpoints, dimension);
	// Count number of edges after throwing away for optimization
	REM_EDGES = 0;
	//Switch based on dimensional cases 
	switch (dimension) {
	case 0:
		//pruning value call 
		cutoff;
		int i;
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float weight = rand() / (float)RAND_MAX;
				// Prune here
				
				if (weight <= cutoff) {
					//Allocade memory for edges 
					edge* edge_1 = malloc(sizeof(edge));
					edge_1->source = i, 
					edge_1->target = j, 
					edge_1->weight = weight;
					edge_1->next = g[i];
					g[i] = edge_1;
					
					edge* edge_2 = malloc(sizeof(edge));
					edge_2->source = j;
					edge_2->target = i; 
					edge_2->weight = weight; 
					edge_2->next = g[i];

					g[i] = edge_2;

					REM_EDGES++;	
					// Realloc for more space if cap reached
					//if (REM_EDGES >= cutoff) {
					//  edge = realloc(sizeof(edge));
					//}
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
				//Prune
				REM_EDGES++;
				//if (cweight < cutoff) {
					//Memory allocation 
					edge* edge_1 = malloc(sizeof(edge));
					edge_1->source = i, 
					edge_1->target = j, 
					edge_1->weight = cweight;
					edge_1->next = g[i];
					g[i] = edge_1;
					

					edge* edge_2 = malloc(sizeof(edge));
					edge_2->source = j;
					edge_2->target = i; 
					edge_2->weight = cweight; 
					edge_2->next = g[i];

					g[i] = edge_2;
				//}
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
				//Euclidian calculations done here
				float cweight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2) + pow(ptarray[i].c - ptarray[j].c, 2));
				//Pruning 
				REM_EDGES++;
				//if (cweight < cutoff) {
					//Memory allocation for edge 
					edge* edge_1 = malloc(sizeof(edge));
					edge_1->source = i,
					edge_1->target = j,
					edge_1->weight = cweight;
					edge_1->next = g[i];
					g[i] = edge_1;
					

					edge* edge_2 = malloc(sizeof(edge));
					edge_2->source = j;
					edge_2->target = i; 
					edge_2->weight = cweight; 
					edge_2->next = g[i];

				//}
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

				//Euclidian calculation here
				float cweight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2) + pow(ptarray[i].c - ptarray[j].c, 2)
				                     + pow(ptarray[i].d - ptarray[j].d, 2));
				//Pruning
				//if (cweight < cutoff) {
					//Allocate enough memory for edges
					edge* edge_1 = malloc(sizeof(edge));
					edge_1->source = i, edge_1->target = j, edge_1->weight = cweight;
					edge_1->next = g[i];
					g[i] = edge_1;
					REM_EDGES++;

					edge* edge_2 = malloc(sizeof(edge));
					edge_2->source = j;
					edge_2->target = i; 
					edge_2->weight = cweight; 
					edge_2->next = g[i];
				//}
			}
		}
		//Return generated random graph
		return g;

	}

}

