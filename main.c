#include "adjarray.c"
#include "sort.c"
#include "stats.c"
#include "functions.c"

int main(int argc,char** argv){

	char* file = argv[1];//"instances/email-Eu-core.txt";

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


	//------------ Test des fonctions
	STATS s;

	printf("\nDEBUT Calcul des clusters\n");
	findClusters(g, &s);
	printf("FIN Calcul des clusters\n");

	printf("\nDEBUT Calcul du diametre\n");
	findDiameter(g, &s);
	printf("DEBUT Calcul du diametre\n");

	printf("\nDEBUT Calcul des triangles\n");
	findTriangles(g, &s);
	printf("DEBUT Calcul des triangles\n");

	showSTATS(&s);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}