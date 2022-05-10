#ifndef filehandler_h
#define filehandler_h


#include <stdio.h> 
#define MAXC 21

struct names
{
    char name[MAXC];
}; typedef struct names Names; 

int beginning();
void fileReader(Names words[]);

#endif
