// #include "graph.h"
// #include "query.h"


// 0: succesful, -1: error
int update_term_property(graph* db, char *term, char* sound, int freq);
int update_edge_property_by_id(graph* db, char *edge_id, int w);
int update_edge_property(graph* db, char* word_from, char* word_to, int w);

