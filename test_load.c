#include "graph.h"
#include "query.h"
#include "update.h"
#include "predict.h"
#include "load.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    graph db = create_graph();
    db_load(&db, "test");
}