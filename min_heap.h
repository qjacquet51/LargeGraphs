#ifndef MIN_HEAP_H
#define MIN_HEAP_H

struct Heap{
    unsigned long *arr;
    unsigned long count;
    unsigned long capacity;
    unsigned long heap_type; // for min heap , 1 for max heap
    long int *weigths;
    unsigned long *to_index;
};
typedef struct Heap Heap;

Heap *CreateHeap(unsigned long capacity, long int *weigths);
void insert(Heap *h, unsigned long key);
void print(Heap *h);
void heapify_bottom_top(Heap *h, long index);
void heapify_top_bottom(Heap *h, unsigned long parent_node);
unsigned long PopMin(Heap *h);
void decreaseKey(Heap *h, unsigned long index, long int weigth);
void deleteKey(Heap *h, unsigned long i);
void decreaseVal(Heap *h, unsigned long index, long int weigth);
void deleteVal(Heap *h, unsigned long i);

#endif