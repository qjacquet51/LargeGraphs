#ifndef MIN_HEAP_H
#define MIN_HEAP_H

struct Heap{
    unsigned long *arr;
    unsigned long count;
    unsigned long capacity;
    unsigned long heap_type; // for min heap , 1 for max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity);
void insert(Heap *h, int key);
void print(Heap *h);
void heapify_bottom_top(Heap *h, long index);
void heapify_top_bottom(Heap *h, unsigned long parent_node);
int PopMin(Heap *h);

#endif