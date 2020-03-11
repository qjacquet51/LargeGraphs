#include <math.h>

void computePowerIteration(adjlist* g, STATS *s, double alpha, int t){

	unsigned long level_fifth = 0;
	unsigned long level_last_fifth = 0;

	// Initialisation de P
	unsigned long *P_prev = malloc(g->n*sizeof(unsigned long));
	unsigned long *P_next = calloc(g->n, sizeof(unsigned long));
	unsigned long i, k, u;
	unsigned long norm = 0;
	for (i=0; i<g->n; ++i){
		P_prev[i] = 1/g->n;
	}

	// Itérations
	for (k=1; k<=t; ++k){

		for (u=0; u<g->n; ++u){
			
			// On calcule les coeffs
			for (i = g->cd[u]; i<g->cd[u+1]; ++i){
				P_next[u] = 1/(g->cd[u+1]-g->cd[u])*P_prev[g->adj[i]];
			}
			norm += P_next[u]*P_next[u];

			// On rajoute une partie de l'identité
			P_next[i] = (1-alpha)*P_next[i]+alpha/g->n;
			P_next[i] /= sqrt(norm);
			
			// On passe à l'itérée suivante
			P_prev[i] = P_next[i];
			P_next[i] = 0;
			norm = 0;
		}
	}



};