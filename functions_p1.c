typedef struct {
	unsigned long *FIFO_list;
	unsigned long begin_FIFO;
	unsigned long end_FIFO;
	unsigned long size_FIFO;
	unsigned long *FIFO_marked;
} FIFO;

void initFIFO(FIFO *F, unsigned long size){
	F->FIFO_list = malloc(size*sizeof(unsigned long));
	F->FIFO_marked = calloc(size, sizeof(unsigned long));
	F->begin_FIFO = 0;
	F->end_FIFO = 0;
	F->size_FIFO = 0;
};

void reinitFIFO(FIFO *F){
	F->begin_FIFO = 0;
	F->end_FIFO = 0;
	F->size_FIFO = 0;
};

void reinitFIFO_marked(FIFO *F, unsigned long size){
	free(F->FIFO_marked);
	F->FIFO_marked = calloc(size, sizeof(unsigned long));
};

void freeFIFO(FIFO *F){
	free(F->FIFO_marked);
	free(F->FIFO_list);
}
void pushFIFO(FIFO *F, unsigned long e){
	F->FIFO_list[F->end_FIFO] = e;
	++(F->end_FIFO);
	++(F->size_FIFO);
	F->FIFO_marked[e] = 1;
};

unsigned long popFIFO(FIFO *F){
	unsigned long e = F->FIFO_list[F->begin_FIFO];
	++(F->begin_FIFO);
	--(F->size_FIFO);
	F->FIFO_marked[e] = -1;
	return e;
};

int getMarkFIFO(FIFO *F, unsigned long e){
	return F->FIFO_marked[e];
}

unsigned long getSizeFIFO(FIFO *F){
	return F->size_FIFO;
}

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
			mergeSort(g, tsl[u], 0, size_tsl[u]-1);
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