#ifndef GEN_GRAPH
#define GEN_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void generate_graph(unsigned long n_nodes, double p, double q, char* input){

    unsigned long i, u;
    FILE *fptr;

    if(q > p){
        printf("Error: the values of q and p do not respect q <= p");
        exit(1);
    }

    // initializes the random number generator
    srand(time(NULL));

    fptr = fopen(input, "w");
    if(fptr == NULL)
    {
        printf("Error opening file!");
        exit(1);             
    }

    for(i=0; i<n_nodes; ++i){
        
        for(u=0; u<n_nodes; ++u){

            // Nodes in the same cluster
            if(abs(i-u) < 100){
                if(u!=i){
                    int r = rand() % 100;
                    if(r <= p*100){
                        fprintf(fptr, "%lu %lu\n", i, u);
                    }
                }
            }
            else {
                int r = rand() % 100;
                if(r <= q*100){
                    fprintf(fptr, "%lu %lu\n", i, u);
                }
            }
        }
    }

    fclose(fptr);
};

#endif