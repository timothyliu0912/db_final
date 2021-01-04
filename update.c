#include "graph.h"
#include "query.h"
#include <stdio.h>
#include <string.h>

int update_term_property(graph *db, char *term, char *sound, int freq)
{
    /*
    term: select term
    sound: this word sound, if null: ignore
    freq: this word freq, if -1: ignore
    */

    graph_node *node = &find_term_node(db, term)->node;
    if (sound != NULL)
        strcpy(node->word_fs->sound, sound);
    if (freq != -1) {
        db->total_cnt += freq - node->word_fs->freq;
        node->word_fs->freq = freq;
    }
    return 0; // succesful
}

int update_edge_property_by_id(graph *db, char *edge_id, int new_w)
{
    /*
   edge_id: MD5
   new_w: new edge weight
    */
    graph_edge_list *edge = find_edge_in_table_by_id(db, edge_id);
    edge->freq = new_w;
    return 0;
}

int update_edge_property(graph *db, char *word_from, char *word_to, int w)
{
    /*
   edge_id: MD5
   word_from: from node
   word_to: to node
   int w: new edge weight
    */
    graph_edge_list *edge = find_edge_in_table(db, word_from, word_to);
    edge->freq = w;
    return 0;
}
