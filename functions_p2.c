#include <math.h>
#include "min_heap.h"

void computePageRank(adjlist* g, STATS *s, double alpha, int t){

	// Initialisation de P
	double *P_prev = calloc(g->n,sizeof(double));
	double *P_next = calloc(g->n, sizeof(double));
	unsigned long i, u;
	int l, p, k;
	double norm = 0.0;
	for (i=0; i<g->n; ++i){ P_prev[i] = 1.0/g->n; }

	// Itérations
	for (k=1; k<=t; ++k){

		for (i=0; i<g->e; ++i){
			if (g->outD[g->edges[i].s] > 0){
				P_next[g->edges[i].t] += P_prev[g->edges[i].s]/g->outD[g->edges[i].s];
			}
		}
		for (u=0; u<g->n; ++u){
			norm += P_next[u]*P_next[u];

			// On rajoute une partie de l'identité
			P_next[u] = (1-alpha)*P_next[u]+alpha/g->n;
		}

		for (u=0; u<g->n; ++u){
			// On rescale
			P_next[u] /= sqrt(norm);
			
			// On passe à l'itérée suivante
			P_prev[u] = P_next[u];
			P_next[u] = 0.0;
		}
		norm = 0.0;
	}

	// On récupère les 5 meilleurs et 5 pires
	double *best_five_values = calloc(5, sizeof(double));
	double *worst_five_values = calloc(5,sizeof(double));
	for (p=0; p<5; ++p){ worst_five_values[p] = 1; }


	for (u=0; u<g->n; ++u){
		for (p=0; p<5; ++p){
			
			// si on a une amélioration dans les 5 meilleurs
			if (P_prev[u]>best_five_values[p]){

				//on décale tout
				for (l=5;l>p; --l){
					s->five_most_popular_pages[l] = s->five_most_popular_pages[l-1];
					best_five_values[l] = best_five_values[l-1];
				}
				s->five_most_popular_pages[p] = u;
				best_five_values[p] = P_prev[u];

				break;
			}

			// si on a une amélioration dans les 5 pires
			if (P_prev[u]<worst_five_values[p] && P_prev[u]>1.0/g->n+1e-5){

				//on décale tout
				for (l=5;l>p; --l){
					s->five_last_popular_pages[l] = s->five_last_popular_pages[l-1];
					worst_five_values[l] = worst_five_values[l-1];
				}
				s->five_last_popular_pages[p] = u;
				worst_five_values[p] = P_prev[u];

				break;
			}
		}
	}

	// on libère la mémoire
	free(P_next);
	free(P_prev);
};

void computeKCore(adjlist *g, STATS *s){
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
		kcore[ind_min_d] = g->n-cur_nb;
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

	// on libère la mémoire
	free(d);
	free(kcore);
	free(forbidden);

};