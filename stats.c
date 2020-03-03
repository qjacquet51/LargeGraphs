typedef struct 
{
	unsigned long diameter;
	unsigned long entry_max_size_cluster;
	unsigned long max_size_cluster;
	double ratio_max_size_cluster;
} STATS;

void initSTATS(STATS *s){
	s->diameter = 0;
	s->entry_max_size_cluster = 0;
	s->max_size_cluster = 0;
	s->ratio_max_size_cluster = 0;
}

void showSTATS(STATS *s){
	printf("\n----------- STATISTIQUES ------------\n");
	printf("Taille plus grand cluster: %d\n", s->max_size_cluster);
	printf("Ratio plus grand cluster: %.5f\n", s->ratio_max_size_cluster);
	printf("Plus grand diametre trouve: %d\n", s->diameter);
	printf("-------------------------------------\n");
}