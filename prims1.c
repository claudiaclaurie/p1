#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"
#include "graphgeneration.h"
#include "heap.h"


//Implementation of Prim's algorithm- finds MST and returns the weight of MST.
float prims(edge** g, graph_node* ptarray, int numpoints, int v_index, int n) {

	//initialize visited nodes to zero
	int visited[numpoints];
	for (n = 0; n < numpoints; n++) visited[n] = 0;
	//return weight value
	float rweight = 0.0;

	//Initialize heap for placing edges
	//Allocate memory for the edges in the heap
	heap* x = malloc(sizeof(heap)*4);
	x->heap = malloc(sizeof(edge) * REM_EDGES * 4);
	//First initialize everything to zero
	x->heapsz = 0;
	edge first = {0, 0, 0, 0};
	//Insert first edge into the heap
	insert(x, &first);

	//While there are edges in the heap...
	while (x->heapsz != 0) {
		edge destroyed = deletemin(x);
		int d_e = destroyed.target;

		//If an edge has not been visited, mark as visited
		if (visited[d_e] != 1) {
			visited[d_e] = 1;
			//Set to current edge
			edge* current = g[d_e];

			while (current) {
				if (visited[current->target] != 1) {
					insert(x, current);
				}
				current = current->next;
			}
			float weightresult = (rweight += destroyed.weight);
		}
		
	}
	//Free memory from the heap to prevent seg fault
	//free(x);

	free(x->heap);
	//Return weight of the edge
	return rweight;
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("Wrong number of arguments supplied\n");
		return 0;
	}
	//Convert string arguments to integers
	int numpoints = atoi(argv[2]);
	int numtrials = atoi(argv[3]);
	int dimension = atoi(argv[4]);

	//Check to make sure dimensions are valid
	if (dimension == 1 || dimension > 4) {
		printf("invalid dimension input\n");
		return 0;
	}
	//Function to record runtime of algorithm
	time_t start = time(NULL);
	float final = 0.0;
	int run;
	//Here we run the algorithm based on argument input
	for (run = 0; run < numtrials; run++) {
		//Allocate memory for generated graoh
		graph_node* pointarray = malloc(sizeof(graph_node) * numpoints * 10);
		//Generate graph based on inputs 
		edge** g = generate_graph(numpoints, dimension, pointarray);

		// If too many edges have been thrown away, MST will be zero 
		float results = prims(g, pointarray, numpoints, 0, 0);
		final += results;

		free(pointarray);
		g_free(g, numpoints);
	}

	time_t end = time(NULL);

	final = final / numtrials;
	printf("total program runtime: %li\n", end - start);
	printf("%f %i %i %i\n", final, numpoints, numtrials, dimension);

	return 0;
}


