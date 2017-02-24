#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"
#include "graphgeneration.h"


// Insert a new edge element into the heap
void insert(heap* heap, edge* new) {

	//indexing function 
	int root(int i) {
		return (i-1) / 2;
	}

	heap -> heapsz++; // insert in the last place 
	int now = heap->heapsz; //adjustment of position 


	while ( now > 0 && heap -> heap[root(now)].weight > new->weight) {
		heap -> heap[now] = heap -> heap[root(now)];
		now = root(now);
	}

	heap -> heap[now] = *new;
}



// order the heap to be a MinHeap
void heapify(heap* heap, int i) {
	//indexing functions 
	int fwd(int i) {
		return 2*i + 2;  
	}	
	int back(int i) {
		return 2*i + 1;
	}
	
	int left = back(i);
	int right = fwd(i);
	int grt;
	if (left < heap -> heapsz && heap -> heap[left].weight <= heap -> heap[right].weight) grt = left;
		else grt= i;
	if (right < heap -> heapsz && heap -> heap[right].weight <= heap -> heap[grt].weight) grt = right; 

	if (grt != i) {
		
		// swap two edges
				/*
		void swap( int* a, int* b )
		{
		    int t = *a;
		    *a = *b;
		    *b = t;
		}
		*/
		edge swp = heap -> heap[i];
		heap -> heap[i] = heap -> heap[grt];
		heap -> heap[grt] = swp;
		heapify(heap, grt);
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
void isInMinHeap(heap* heap, int v)
{
	//check if vertex v is is in the heapify heap 
}
 

// deletes minimum node and returns it
// Check for empty before calling deletemin
edge deletemin(heap* heap) {

	edge minElement = (heap->heap[0]);
	heap->heapsz--;
	
	heap->heap[0] = heap->heap[heap->heapsz];
	
		heapify(heap, 0);
	
	return minElement;
}





// Prim's algorithm, to find MST and return its weight

float prims(edge** g, graph_node* ptarray, int numpoints, int v_index, int n) {
	
	int visited[numpoints];
		for (n = 0; n < numpoints; n++) visited[n] = 0;
	

	float rweight = 0.0;

//initialize heap 
	heap* x = malloc(sizeof(heap));
	x->heap = malloc(sizeof(edge)*REM_EDGES);
	x->heapsz = 0;
	edge first = {0,0,0,0};
	insert(x, &first);


	while (x->heapsz != 0) {
		edge destroyed = deletemin(x);
		int d_e = destroyed.target;

		if (visited[d_e] != 1) {

			visited[d_e] = 1;
			edge* current = g[d_e];
			
			while (current) {
				if (visited[current->target] !=1) {
					insert(x, current);
				}
				current= current->next;
			}
				float weightresult = (rweight += destroyed.weight);
		}	
	}
	free(x);
	free(x->heap);
	return rweight;
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("wrong number of arguments supplied\n");
		return 0;
	}

	int numpoints= atoi(argv[2]);
	int numtrials= atoi(argv[3]);
	int dimension= atoi(argv[4]);

	 if(dimension == 1 || dimension > 4){
        printf("invalid dimension input\n");
        return 0;
    }
		
	clock_t begin = clock();
	float final = 0.0;
	int run;
	for (run = 0; run < numtrials; run++) {

		graph_node* pointarray = malloc(sizeof(graph_node) * numpoints);

		edge** g = generate_graph(numpoints, dimension, pointarray);

		// if we prune off too many edges, we will get a zero-weighted MST
		float results= prims(g, pointarray, numpoints, 0,0);
		final+= results;

		free(pointarray);
		g_free(g, numpoints);
	}
	

	final = final / numtrials;
	
	printf("%f %i %i %i\n", final, numpoints, numtrials, dimension);

	return 0;
}


 