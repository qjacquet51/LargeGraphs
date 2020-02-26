#include "adjarray.c"
#include "functions.c"

int main(int argc,char** argv){

	char* file = "data/email-Eu-core.txt";

	adjlist* g;
	time_t t1,t2;

	//---------- CHARGEMENT GRAPHE
	t1=time(NULL);

	printf("Reading edgelist from file %s\n",file);
	g=readedgelist(file);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));


	//------------ BFS
	applyBFS(g, 0);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}