
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"
#include "graphgeneration.h"

int REM_EDGES = 0;


//////////////////////////////////////////////
//GRAPH CREATION//////////////////////////////

// Get rid of memory so there is room for edges 
void g_free(edge** g, int numpoints) {
	
	int n;

	for (n =0; n < numpoints; n ++) {

		edge* current = g[n];
		
		if (current) {

			edge* selected = current -> next;
			free(current);
			current = selected;
		}
	}
	free(g);
}
	

// set up graph
edge **generate_graph(int numpoints, int dimension, graph_node* ptarray) {
	// seed pseudorandom number generator with time, always different 
	srand48(time(NULL));
	int i; 

	//allocate memory for the edges
	edge** g = malloc(sizeof(edge*)*numpoints);
	if (g == NULL){
		return NULL;
	}
	for (i = 0; i < numpoints; i++) {
		g[i] = NULL;
	}

	// array of all the points
	ptarray= malloc(sizeof(graph_node) * numpoints);

	// count number of edges after throwing away for optimization 
	REM_EDGES = 0;

	// thro away edges that make the graph to large- optimization 
	float throw_edge;
	throw_edge = 100/(pow(log2((float)numpoints), 3));
	 
	 switch(dimension){
	 	case 0: 
	 	throw_edge;
		int i;
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float weight = rand() / (float)RAND_MAX;
				//forward edges 
				edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i, forward_edge->target = j, forward_edge->weight = weight;
				// prune
				if (weight <= throw_edge) {
					REM_EDGES++;
					//backwardeedges 
					
					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j;
					back_edge->target = i;
					back_edge->weight = weight;

					forward_edge->next = g[i];
					g[i] = forward_edge;

					back_edge->next = g[j];
					g[j] = back_edge;
				}
			}
		}
		case 2:
		throw_edge;
		
		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX, ptarray[i].c = 0, ptarray[i].d = 0;
		}
		
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				
				//euclidian math done here 
				float curr_weight = sqrt(pow(ptarray[i].a- ptarray[j].a, 2)+ pow(ptarray[i].b-ptarray[j].b, 2));
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i, forward_edge->target = j, forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j, back_edge->target = i, back_edge->weight = curr_weight;

					forward_edge->next = g[i];
					g[i] = forward_edge;

					back_edge->next = g[j];
					g[j] = back_edge;
				}				
			}
		}
		case 3: 
		throw_edge;
		
		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX, 
			ptarray[i].c = rand() / (float)RAND_MAX, ptarray[i].d = 0;
		}
		
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				//euclidian calculations done here 
				float curr_weight = sqrt(pow(ptarray[i].a- ptarray[j].a, 2) + pow(ptarray[i].b-ptarray[j].b, 2) + pow(ptarray[i].c-ptarray[j].c, 2));
				
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i, forward_edge->target = j, forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j, back_edge->target = i, back_edge->weight = curr_weight;

					forward_edge->next = g[i];
					g[i] = forward_edge;

					back_edge->next = g[j];
					g[j] = back_edge;
				}				
			}
		}
		default:
		throw_edge;
		
		for (i = 0; i < numpoints; i++) {
			float weight = rand() / (float)RAND_MAX;
			ptarray[i].a = rand() / (float)RAND_MAX, ptarray[i].b = rand() / (float)RAND_MAX, ptarray[i].c = rand() / (float)RAND_MAX,
			 ptarray[i].d = rand() / (float)RAND_MAX;
		}
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {

				//euclidian calculation here 
				float curr_weight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2) + pow(ptarray[i].b - ptarray[j].b, 2) + pow(ptarray[i].c - ptarray[j].c, 2)
					+ pow(ptarray[i].d - ptarray[j].d, 2));
				
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i, forward_edge->target = j, forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j, back_edge->target = i, back_edge->weight = curr_weight;

					forward_edge->next = g[i];
					g[i] = forward_edge;

					back_edge->next = g[j];
					g[j] = back_edge;
				}
			}
		}
		return g;

	 }

}
