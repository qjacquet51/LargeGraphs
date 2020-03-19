#ifndef DIAMETERS
#define DIAMETERS

#include "../structs/fifo.h"
#include "../structs/adjarray.h"
#include "../structs/stats.h"

void findDiameter(adjlist* g, STATS *s){

	// création d'une FIFO
	FIFO F;

	initFIFO(&F, g->n);
	
	unsigned long start = s->entry_max_size_cluster;
	unsigned long end_level = s->entry_max_size_cluster;
	unsigned long tmp_end_level = 0;
	unsigned long level = 0;
	unsigned long max_nb_iter = 10;
	unsigned long nb_iter = 0;
	unsigned long i, u, v;

	while (nb_iter < max_nb_iter){

		++ nb_iter;
		reinitFIFO(&F);
		reinitFIFO_marked(&F, g->n);
		start = end_level;
		pushFIFO(&F, start);
		level = 0;

		while (getSizeFIFO(&F)>0){

			// on pop un noeud
			u = popFIFO(&F);

			// parcours des voisins
			for (i = g->cd[u]; i<g->cd[u+1]; ++i){
				v = g->adj[i];

				if (getMarkFIFO(&F, v) == 0){
					pushFIFO(&F, v);

					// on marque le dernier du palier en cours
					tmp_end_level = v;
				}
			}
			// on met à jour le dernier élement du palier
			if (u == end_level && tmp_end_level != end_level){
				end_level = tmp_end_level;
				++ level;
			}
		}
	}

	s->diameter = level;

	freeFIFO(&F);
};

#endif