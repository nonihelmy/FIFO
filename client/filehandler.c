#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include "filehandler.h"

#define MAXC 21


void fileReader(Names words[]);

int beginning()
{
    srand(time(NULL));
    char namme[MAXC];
    Names words[100];
    fileReader(words); 

    int points = 0;

    while (1)
    {
        int v = rand() % 50;
        printf("Type the following word\n%s\n", words[v].name);
        scanf(" %s", namme);
        if (strcmp(namme, words[v].name) == 0)
        {
            int Currentpoints = strlen(namme);
            printf("Correct spelling! Poang tillagd\n");
            points += Currentpoints;
            printf("Points: %d\n", points);
        }
        else
        {
            printf("You spelled wrong!\n");
        }
    }

    return 0;
} 

void fileReader(Names words[]){
    FILE *fp; 
    fp = fopen("../resource/words.txt", "r");

    if (fp != NULL)
    {
        for (int i = 0; i < 50; i++)
        {
            fscanf(fp, " %s", words[i].name);
        }
    }
    fclose(fp);
}