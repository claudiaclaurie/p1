#ifndef __PRIMS1_H__
#define __PRIMS1_H__

// graph point
typedef struct graph_node {
	float a;
	float b;
	float c;
	float d;
}graph_node;


// edge between points
typedef struct edge {
	int source;
	int target;
	float weight;
	struct edge* next;		
}edge;

// heap to store edges, for Prim's algorithm
typedef struct heap {
	unsigned int heapsz;
	edge* heap;
}heap;



#endif