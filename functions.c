typedef struct {
	unsigned long *FIFO_list;
	unsigned long begin_FIFO;
	unsigned long end_FIFO;
	unsigned long size_FIFO;
} FIFO;

void initFIFO(FIFO *F, unsigned long size){
	F->FIFO_list = malloc(size*sizeof(unsigned long));
	F->begin_FIFO = 0;
	F->end_FIFO = 0;
	F->size_FIFO = 0;
};

void pushFIFO(FIFO *F, unsigned long e){
	F->FIFO_list[F->end_FIFO] = e;
	++(F->end_FIFO);
	++(F->size_FIFO);
};

unsigned long popFIFO(FIFO *F){
	unsigned long e = F->FIFO_list[F->begin_FIFO];
	++(F->begin_FIFO);
	--(F->size_FIFO);
	return e;
};

int inFIFO(FIFO *F, unsigned long u){
	unsigned long i;
	for (i = 0; i<F->end_FIFO; ++i){
		if (u == F->FIFO_list[i]){
			return 1;
		}
	}
	return 0;
};

void applyBFS(adjlist* g, unsigned long s){

	// création d'une FIFO
	FIFO F;

	initFIFO(&F, g->n);
	pushFIFO(&F, s);

	while (F.size_FIFO>0){

		// on pop un noeud
		unsigned long u = popFIFO(&F);
		printf("Noeud %d\n", u);

		// parcours des voisins
		unsigned long i;
		for (i = g->cd[u]; i<g->cd[u+1]; ++i){
			unsigned long v = g->adj[i];

			if (inFIFO(&F, v) == 0){
				pushFIFO(&F, v);
			}
		}
	}
};