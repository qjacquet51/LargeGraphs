#ifndef LABEL_PROPAGATION
#define LABEL_PROPAGATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../structs/adjarray.h"
#include "../structs/stats.h"

void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, u, n1, n2, ln1, ln2;
    unsigned long maximum, index;
    bool node_wtht_highest_freq=true;

    unsigned long *labels = calloc(g->n * sizeof(unsigned long));
    
    // Assgin unique label to each node
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

        // Suppose that we did not change any label
        node_wtht_highest_freq = false;
        // Set the label with the highest frequency among the neighbours
        for(i=0; i<g->n; ++i){
            unsigned long *n_labels = calloc(g->n, sizeof(unsigned long));

            for(u=g->cd[i]; u<g->cd[i+1]; ++u){
                n_labels[u] = n_labels[u] + 1;
            }

            // Find the maximum
            maximum = n_labels[0];
            index = 0;
            for(u=1; u<g->n; ++i){
                if(n_labels[u] > maximum){
                    maximum = n_labels[u];
                    index = u;
                }
            }
            
            // Change the label of the current node if needed
            if(labels[i] != labels[index]){
                labels[i] = labels[index];
                node_wtht_highest_freq = true;
            }
        }
    }
};

#endif