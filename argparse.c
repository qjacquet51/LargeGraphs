#include <stdio.h>  
#include <unistd.h>

typedef struct
{
    char* inputFile;
    char* dicFile;
    char project;
} OPTIONS;

void load_options(OPTIONS *options, int argc, char** argv){
    printf("\nDEBUT Lecture des options\n");
    int opt;
    options->inputFile = "none";
    options->dicFile = "none";
    options->project = '2';
    
    while((opt = getopt(argc, argv, ":f:p:d:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'd':
                printf("\tDictionnaire nom pages: %s\n", optarg);  
                options->dicFile = optarg;
                break;    
            case 'p':  
                printf("\tProjet: %s\n", optarg);  
                options->project = optarg[0];
                break;  
            case 'f':  
                printf("\tInput file: %s\n", optarg); 
                options->inputFile = optarg; 
                break;  
            case ':':  
                printf("\tOption needs a value\n");  
                break;  
            case '?':  
                printf("\tUnknown option: %c\n", optopt); 
                break;  
        }  
    }
    printf("FIN Lecture des options\n");
};