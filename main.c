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

	printf("\tLecture du fichier %s\n",options.inputFile);
	g=readedgelist(options.inputFile);

	printf("\tNombre de sommets: %lu\n",g->n);
	printf("\tNombre d'aretes: %lu\n",g->e);

	printf("\tConstruction de la liste d'adjacence ...\n");
	if (options.project == '1'){ mkadjlist(g, 0); }
	else { mkadjlist(g, 1); }

	t2=time(NULL);
	printf("FIN Lecture graphe en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));


	STATS s;
	//====================== PROJET 1 ======================

	if (options.project == '1'){
		printf("\nDEBUT Calcul des clusters\n");
		t1 = time(NULL);
		findClusters(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul des clusters en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

		printf("\nDEBUT Calcul du diametre\n");
		t1 = time(NULL);
		findDiameter(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul du diametre en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

		printf("\nDEBUT Calcul des triangles\n");
		t1 = time(NULL);
		findTriangles(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul des triangles en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	}

	//====================== PROJET 2 ======================
	if (options.project == '2'){
		//printf("\nDEBUT Lecture nom pages\n");
		//printf("%s\n", getName(options.dicFile, 13832572));
		//printf("\nFIN Lecture nom pages\n");

		printf("\nDEBUT Page Rank\n");
		t1 = time(NULL);
		computePageRank(g, &s, 0.15, 20);
		t2 = time(NULL);
		printf("FIN Page Rank en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	}



	showSTATS(&s, &options);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}