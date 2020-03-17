#ifndef TRIANGLES
#define TRIANGLES

#include "../structs/sort.h"
#include "../structs/adjarray.h"
#include "../structs/stats.h"

unsigned long intersect(unsigned long u, unsigned long v, unsigned long** tsl, unsigned long *size_tsl){
	
	unsigned long full_ix = 0;
    unsigned long sub_ix = 0;
    unsigned long curr_full, curr_sub;
    unsigned long nb = 0;

    while (full_ix < size_tsl[u] && sub_ix < size_tsl[v]){
        curr_full = tsl[u][full_ix];
        curr_sub = tsl[v][sub_ix];
        if (curr_full == curr_sub && v < curr_full){
            ++full_ix;
            ++sub_ix;
            ++nb;
            continue;
        }
        if (curr_full < curr_sub){
            ++ full_ix;
        }
        else{
            ++ sub_ix;
        }
    }
    return nb;
    
};

void findTriangles(adjlist *g, STATS *s){
	unsigned long u, i, j;
	unsigned long **tsl = malloc(g->n*sizeof(*tsl));
	unsigned long *size_tsl = calloc(g->n, sizeof(unsigned long));
	
	// construction de tsl
	for (u=0; u<g->n; ++u){
		tsl[u] = calloc(g->cd[u+1]-g->cd[u], sizeof(unsigned long));
		
		for (i = 0; i<g->cd[u+1]-g->cd[u]; ++i){
			if (g->adj[i+g->cd[u]]> u){
				tsl[u][size_tsl[u]] = g->adj[i+g->cd[u]];
				++size_tsl[u];
			}
		}
		if (size_tsl[u] >= 2){
			mergeSort(tsl[u], 0, size_tsl[u]-1);
		}
	}
	
	//recherche dans toutes les aretes
	unsigned long v;
	unsigned long nb_triangles = 0;
	for (u=0; u<g->n; ++u){
		for (i = g->cd[u]; i<g->cd[u+1]; ++i){
			v = g->adj[i];
			if (u<v){
				nb_triangles += intersect(u, v, tsl, size_tsl);
			}
		}
	}
	intersect(u, v, tsl, size_tsl);

	s->nb_triangles = nb_triangles;

	// on libère la mémoire
	free(size_tsl);
	free(tsl);
	
};

#endif