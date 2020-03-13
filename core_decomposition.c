#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "min_heap.h"
#include "core_decomposition.h"

void DFS(int node, adjlist* g,
		 unsigned long &visitednode, unsigned long &degreenode, int k){

	// Mark the current node as visited
	visitednode[node] = 1;

	for (int i=)
}


void coreDecomposition(adjlist* g, int k){

	unsigned long **visitednode = calloc(g->n, sizeof(unsigned long));
	unsigned long **processednode = calloc(g->n, sizeof(unsigned long));

	int mindeg = init_max; // to define
	int startnode;

	// Store degrees of all nodes
	unsigned long **degreenodes = calloc(g->n, sizeof(unsigned long));
	for (int i=0; i<g->n; ++i){
		for (int u=0; u<g->cd[i+1]-g->cd[i]; ++u){
			degreenode[i] = g->adj[u];
		}

		if (degreenode[i] < mindeg){
			mindeg = degreenodes[i];
			startnode = i;
		}
	}

	
}