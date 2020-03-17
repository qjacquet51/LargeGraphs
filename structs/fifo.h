#ifndef FIFO_DEF
#define FIFO_DEF

typedef struct {
	unsigned long *FIFO_list;
	unsigned long begin_FIFO;
	unsigned long end_FIFO;
	unsigned long size_FIFO;
	unsigned long *FIFO_marked;
} FIFO;

void initFIFO(FIFO *F, unsigned long size);
void reinitFIFO(FIFO *F);
void reinitFIFO_marked(FIFO *F, unsigned long size);
void freeFIFO(FIFO *F);
void pushFIFO(FIFO *F, unsigned long e);
unsigned long popFIFO(FIFO *F);
int getMarkFIFO(FIFO *F, unsigned long e);
unsigned long getSizeFIFO(FIFO *F);

#endif