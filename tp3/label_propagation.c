#ifndef LABEL_PROPAGATION
#define LABEL_PROPAGATION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../structs/adjarray.h"
#include "../structs/stats.h"

void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, u, n1, n2, ln1, ln2;
    bool node_wtht_highest_freq=true;

    unsigned long *labels = calloc(g->n * sizeof(unsigned long));
    
    // Assgin unique lqbel to each node
    for(i=0; i<g->n; ++i) labels[i] = i;

    while(node_wtht_highest_freq){
        
        // random shuffle
        for(u=0; u<g->n; ++u){
            //srand(time(NULL));
            n1 = rand()%g->n;
            n2 = rand()%g->n;
            printf("\n n1: %lu", n1);
            printf("\n n2: %lu", n2);
            ln1 = labels[n1];
            ln2 = labels[n2];
            labels[n2] = ln1;
            labels[n1] = ln2;
        }

        // Set the label with the highest frequency among the neighbours
        for(i=0; i<g->n; ++i){
            
        }
    }

};

#endif