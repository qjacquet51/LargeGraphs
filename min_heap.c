#include<stdio.h>
#include<stdlib.h>

#include "min_heap.h"

/*int main(){
    unsigned long i;
    long int *weigths = malloc(9*sizeof(long int));

    for(i =9; i>0; i--){ weigths[i] = 2*i; }

    Heap *heap = CreateHeap(11, weigths); 

    for(i=9; i>0; i--){ insert(heap, i); }

    print(heap);

    decreaseVal(heap, 8, heap->weigths[8]-3);

    for(i=9;i>0;i--){ printf(" Pop Minima : %d\n", PopMin(heap)); }
    return 0;
}*/

Heap *CreateHeap(unsigned long capacity, long int *weigths){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation fails
    if(h == NULL){
        printf("Memory Error!");
        //return;
    }
    h->count=0;
    h->capacity = capacity;
    h->arr = (unsigned long *) malloc(capacity*sizeof(unsigned long)); //size in bytes
    h->weigths = weigths;
    h->to_index = (unsigned long *) malloc(capacity*sizeof(unsigned long));

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        //return;
    }
    return h;
}

void insert(Heap *h, unsigned long key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        h->to_index[key] = h->count;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,long index){
    unsigned long temp;
    unsigned long parent_node = (index-1)/2;

    if(h->weigths[h->arr[parent_node]] > h->weigths[h->arr[index]]){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->to_index[h->arr[parent_node]] = parent_node; // keep track
        h->arr[index] = temp;
        h->to_index[temp] = index; // keep track
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(Heap *h, unsigned long parent_node){
    long left = parent_node*2 + 1;
    long right = parent_node*2 + 2;
    unsigned long min;
    unsigned long temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->weigths[h->arr[left]] < h->weigths[h->arr[parent_node]])
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->weigths[h->arr[right]] < h->weigths[h->arr[min]])
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;
        h->to_index[h->arr[min]] = min; // keep track
        h->to_index[temp] = parent_node; // keep track

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

unsigned long PopMin(Heap *h){
    unsigned long pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return 0;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    if (h->count>0){
        heapify_top_bottom(h, 0);
    }
    return pop;
}

void decreaseKey(Heap *h, unsigned long i, long int new_weigth) 
{ 
    h->weigths[h->arr[i]] = new_weigth; 
    while (i != 0 && h->weigths[h->arr[(i-1)/2]] >= h->weigths[h->arr[i]]) {  
        unsigned long temp = h->arr[i];
        h->arr[i] = h->arr[(i-1)/2];
        h->arr[(i-1)/2] = temp;
        i = (i-1)/2; 
    } 
} 
void decreaseVal(Heap *h, unsigned long val, long int new_weigth){
    decreaseKey(h, h->to_index[val], new_weigth); 
}

void deleteKey(Heap *h, unsigned long i) 
{ 
    decreaseKey(h, i, -1000); 
    PopMin(h); 
}

void deleteVal(Heap *h, unsigned long val) 
{ 
    decreaseKey(h, h->to_index[val], -1000); 
    PopMin(h); 
} 

void print(Heap *h){
    unsigned long i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %lu (%d)",h->arr[i], h->weigths[h->arr[i]]);
    }
    printf("->__/\\__\n");
}