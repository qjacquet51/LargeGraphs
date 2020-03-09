#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

char * getName(const char* inputFile, unsigned long idx){
	FILE *file=fopen(inputFile,"r");

	unsigned long index;
	char * name = malloc(300*sizeof(char));
	int i;

	while (fscanf(file,"%lu\t%[^\n]s", &index, name) != EOF){
		if (idx == index){ break; }
		for (i = 0; i<300; ++i){ name[i] = ' '; }
    }
    
	fclose(file);
	return name;
};