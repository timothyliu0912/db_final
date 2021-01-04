#include "update.h"

int update_term_property(graph* db, char *term, char* sound, int freq);
{
    /*
    term: select term
    sound: this word sound, if null: ignore
    freq: this word freq, if -1: ignore
    */
    graph_node*  node = & find_term_node(db, term) -> node;
    if (sound != NULL)
        strcpy(node.sound, sound);
    if(freq != -1)
        node->freq = freq;
    return 0; // succesful
}

// int update_edge_property(graph* db, char *edge_id, char* sound)
// {

// }