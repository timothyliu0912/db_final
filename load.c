#include "graph.h"
#include "save.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int db_load(graph*db, char* path)
{
    FILE* fp = fopen(path, "r");
    char line[2048];
    while (fgets(line, 2048, fp))
    {
        line[strlen(line) - 1] = 0;
        if(!strcmp(line, "word"))
    }
    
}