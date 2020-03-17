#ifndef FIFO_F
#define FIFO_F

#include "fifo.h"

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

#endif

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