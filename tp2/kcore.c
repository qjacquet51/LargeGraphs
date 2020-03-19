#ifndef KCORE
#define KCORE

#include "../structs/stats.h"
#include "../structs/adjarray.h"
#include "../structs/min_heap.h"

void computeKCore(adjlist *g, STATS *s, char* result_file){
	long int *d = malloc(g->n*sizeof(long int)); // -1 si il a été utilisé
	unsigned long *kcore = malloc(g->n*sizeof(unsigned long)); // le numéro de k-core de chaque sommet
	unsigned long *forbidden = calloc(g->n, sizeof(unsigned long));

	unsigned long k, i, ind_min_d, cur_nb;
	long int min_d;
	long int c = 0;

	// On crée la liste triée des sommets, des positions et des degrés
	for (k=0; k<g->n; ++k){
		d[k] = g->cd[k+1] - g->cd[k];
	}

	Heap *h = CreateHeap(g->n, d); 
	for(i=0; i<g->n; ++i){
        insert(h, i);
    }


	while (cur_nb < g->n){

		// recherche du sommet
		ind_min_d = PopMin(h);
		min_d = h->weigths[ind_min_d];

		// on calcule le numéro de k core
		c = (c>min_d) ? c : min_d;
		kcore[ind_min_d] = c;
		forbidden[ind_min_d] = 1;

		// on met à jour les voisins
		for (i = g->cd[ind_min_d]; i<g->cd[ind_min_d+1]; ++i){
			if (forbidden[g->adj[i]] == 0){
				decreaseVal(h, g->adj[i], h->weigths[g->adj[i]]-1);
			}
		}
		
		++cur_nb;
		
	}

	// pour les stats
	s->k_core_value = c;

	
	FILE * fp;
   	fp = fopen (result_file,"w");
   	for (i=0; i<g->n; ++i){
   		if (g->cd[i+1]!=g->cd[i]){
   			fprintf(fp, "%lu\t%d\t%d\n", i, kcore[i], g->cd[i+1]-g->cd[i]);
   		}
   	}
    fclose (fp);


	// on libère la mémoire
	free(d);
	free(kcore);
	free(forbidden);

};

#endif