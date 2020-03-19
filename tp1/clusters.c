#ifndef CLUSTERS
#define CLUSTERS

#include "../structs/fifo.h"
#include "../structs/adjarray.h"
#include "../structs/stats.h"

void findClusters(adjlist* g, STATS *s){

	// création d'une FIFO
	FIFO F;
	unsigned long first_unviewed = 0;
	unsigned long nb_nodes_in_cluster = 0;

	initFIFO(&F, g->n);

	unsigned long max_size = 0;
	unsigned long entry_max_size = 0;
	unsigned long i, u, v;

	while (first_unviewed < g->n){

		reinitFIFO(&F);
		pushFIFO(&F, first_unviewed);
		nb_nodes_in_cluster = 0;

		while (getSizeFIFO(&F)>0){

			// on pop un noeud
			u = popFIFO(&F);
			++ nb_nodes_in_cluster;

			// on met à jour le prochain qui n'a pas été vu
			if (first_unviewed == u){
				while (getMarkFIFO(&F, first_unviewed) != 0 && first_unviewed < g->n){
					++ first_unviewed;
				}
			}

			// parcours des voisins
			for (i = g->cd[u]; i<g->cd[u+1]; ++i){
				v = g->adj[i];

				if (getMarkFIFO(&F, v) == 0){
					pushFIFO(&F, v);
				}
			}
		}
		if (nb_nodes_in_cluster>1){

			if (nb_nodes_in_cluster > max_size){
				max_size = nb_nodes_in_cluster;
				entry_max_size = u;

			}
		}
	}

	s->max_size_cluster = max_size;
	s->ratio_max_size_cluster =  (float)max_size/(float)g->n;
	s->entry_max_size_cluster = entry_max_size;

	freeFIFO(&F);
};

#endif