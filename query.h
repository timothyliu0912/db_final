graph_node_list* find_term_node(graph *db,char *term);
graph_node_list* find_term_node_by_id(graph *db,char *term_code);
graph_edge_list* find_edge_in_table(graph *db,char *front_term,char *end_term);
graph_edge_list* find_edge_in_table_by_id(graph *db,char *edge_code);
word_freq_sound* find_term_sound(graph *db,char *term,char *sound);