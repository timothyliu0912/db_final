#include "graph.h"
#include "query.h"


// 0: succesful, -1: error
int update_term_property(graph* db, char *term, char* sound);
int update_edge_property(graph* db, char *edge_id, char* sound);
