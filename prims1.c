#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "prims1.h"


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


//////////////////////////////////////////////
//////////////////////////////////////////////
//GRAPH CREATION//////////////////////////////
//////////////////////////////////////////////
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
	
// Count for edges after thrown away heavy edges 
int REM_EDGES = 0;
// set up graph
edge **generate_graph(int numpoints, int dimension, graph_node* ptarray) {
	// seed pseudorandom number generator
	srand48(time(NULL));

	edge** g = malloc(sizeof(edge*)*numpoints);
	int i;
	for (i = 0; i < numpoints; i++) {
		g[i] = NULL;
	}

	// array of all the points
	ptarray= malloc(sizeof(graph_node) * numpoints);

	// count number of edges after pruning
	REM_EDGES = 0;

	// different prune cutoff for each dimension
	float throw_edge;
	throw_edge = 100/(pow(log2((float)numpoints), 4));
	 
	 switch(dimension){
	 	case 0: 
	 	throw_edge = 100/(pow(log2((float)numpoints), 4));
		int i;
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float weight = rand() / (float)RAND_MAX;
				//forward edges 
				edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i; 
					forward_edge->target = j;
					forward_edge->weight = weight;


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
			ptarray[i].a = rand() / (float)RAND_MAX;
			ptarray[i].b = rand() / (float)RAND_MAX;
			ptarray[i].c = 0;
			ptarray[i].d = 0;
		}
		
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float curr_weight = sqrt(pow(ptarray[i].a- ptarray[j].a, 2)
						+ pow(ptarray[i].b-ptarray[j].b, 2));
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i; 
					forward_edge->target = j;
					forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j;
					back_edge->target = i;
					back_edge->weight = curr_weight;

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
			ptarray[i].a = rand() / (float)RAND_MAX;
			ptarray[i].b = rand() / (float)RAND_MAX;
			ptarray[i].c = rand() / (float)RAND_MAX;
			ptarray[i].d = 0;
		}
		
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float curr_weight = sqrt(pow(ptarray[i].a- ptarray[j].a, 2)
					+ pow(ptarray[i].b-ptarray[j].b, 2)
					+ pow(ptarray[i].c-ptarray[j].c, 2));
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i; 
					forward_edge->target = j;
					forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j;
					back_edge->target = i;
					back_edge->weight = curr_weight;

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
			ptarray[i].a = rand() / (float)RAND_MAX;
			ptarray[i].b = rand() / (float)RAND_MAX;
			ptarray[i].c = rand() / (float)RAND_MAX;
			ptarray[i].d = rand() / (float)RAND_MAX;
		}
		for (i = 0; i < numpoints; i++) {
			int j;
			for (j = i; j < numpoints; j++) {
				float curr_weight = sqrt(pow(ptarray[i].a - ptarray[j].a, 2)
					+ pow(ptarray[i].b - ptarray[j].b, 2)
					+ pow(ptarray[i].c - ptarray[j].c, 2)
					+ pow(ptarray[i].d - ptarray[j].d, 2));
				if (curr_weight < throw_edge) {
					REM_EDGES++;
					edge* forward_edge = malloc(sizeof(edge));
					forward_edge->source = i; 
					forward_edge->target = j;
					forward_edge->weight = curr_weight;

					edge* back_edge = malloc(sizeof(edge));
					back_edge->source = j;
					back_edge->target = i;
					back_edge->weight = curr_weight;

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


// Prim's algorithm, to find MST and return its weight

float prim(edge** g, graph_node* ptarray, int numpoints, int v_index, int n) {
	
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
		
	
	float final = 0.0;
	int run;
	for (run = 0; run < numtrials; run++) {
		graph_node* pointarray = malloc(sizeof(graph_node) * numpoints);
		edge** g = generate_graph(numpoints, dimension, pointarray);

		// if we prune off too many edges, we will get a zero-weighted MST
		float results= prim(g, pointarray, numpoints, 0,0);
		final+= results;

		free(pointarray);
		g_free(g, numpoints);
	}
	

	final = final / numtrials;
	
	printf("%f %i %i %i\n", final, numpoints, numtrials, dimension);

	return 0;
}


 