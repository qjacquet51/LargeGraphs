#include "adjarray.c"
#include "argparse.c"
#include "read_dic.c"
#include "sort.c"
#include "stats.c"
#include "functions_p1.c"
#include "functions_p2.c"

int main(int argc,char** argv){

	//---------- CHARGEMENT DES OPTIONS
	OPTIONS options;
	load_options(&options, argc, argv);

	adjlist* g;
	time_t t1,t2;

	//---------- CHARGEMENT GRAPHE
	printf("\nDEBUT Lecture graphe\n");
	t1=time(NULL);

	printf("\tReading edgelist from file %s\n",options.inputFile);
	g=readedgelist(options.inputFile);

	printf("\tNumber of nodes: %lu\n",g->n);
	printf("\tNumber of edges: %lu\n",g->e);

	printf("\tBuilding the adjacency list\n");
	mkadjlist(g);

	t2=time(NULL);

	printf("\t- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	printf("FIN Lecture graphe\n");


	STATS s;
	//====================== PROJET 1 ======================

	if (options.project == '1'){
		printf("\nDEBUT Calcul des clusters\n");
		findClusters(g, &s);
		printf("FIN Calcul des clusters\n");

		printf("\nDEBUT Calcul du diametre\n");
		findDiameter(g, &s);
		printf("DEBUT Calcul du diametre\n");

		printf("\nDEBUT Calcul des triangles\n");
		findTriangles(g, &s);
		printf("DEBUT Calcul des triangles\n");
	}

	//====================== PROJET 2 ======================
	if (options.project == '2'){
		printf("\nDEBUT Lecture nom pages\n");
		char * name = getName(options.dicFile, 13832572);
		printf("%s\n", name);
		printf("\nFIN Lecture nom pages\n");
	}



	showSTATS(&s);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}