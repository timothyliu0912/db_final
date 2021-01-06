#include "graph.h"
#include "load.h"
#include "query.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int db_load(graph *db, char *path)
{

    FILE *fp = fopen(path, "r");
    LOAD_STATUS status = WORD;

    char line[2048];

    while (fgets(line, 2048, fp))
    {
        line[strlen(line) - 1] = 0;
        if (!strcmp(line, "word"))
            status = WORD;
        else if (!strcmp(line, "relation"))
            status = RELATION;
        else if (status == WORD)
        {
            add_word(db, line);
        }
        else if (status == RELATION)
        {
            // !TODO: add_relation(hash and graph)
            add_relation(db, line);
        }
    }
}

int add_relation(graph *db, char *line)
{
    char r_id[ID_LENGTH], word1[10], word2[10];
    int freq;

    sscanf(line, "%s %s %s %d", r_id, word1, word2, &freq);
    // printf("%s %s %s %d\n", r_id, word1, word2, freq);

    // create null edge
    graph_edge_list *edge = (graph_edge_list *)malloc(sizeof(graph_edge_list));
    edge->freq = freq;
    edge->next = NULL; // for hash
    strcpy(edge->id, r_id);

    // fetch word node
    graph_node_list *w1_node = find_term_node(db, word1);
    graph_node_list *w2_node = find_term_node(db, word2);

    // solve edge attr
    edge->point_to = w2_node;
    edge->point_from = w1_node;

    // solve node attr
    // in_edge_list (w2)
    graph_edge_id *w2_ge_id = (graph_edge_id *)malloc(sizeof(graph_edge_id));
    strcpy(w2_ge_id->id, r_id);
    w2_ge_id->next = NULL;
    if (w2_node->node.in_edge_list == NULL)
        w2_node->node.in_edge_list = w2_ge_id;
    else
    {
        graph_edge_id *cur = w2_node->node.in_edge_list;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = w2_ge_id;
    }
    // out_from_edge_list (w1)
    graph_edge_id *w1_ge_id = (graph_edge_id *)malloc(sizeof(graph_edge_id));
    strcpy(w1_ge_id->id, r_id);
    w1_ge_id->next = NULL;
    if (w1_node->node.in_edge_list == NULL)
        w1_node->node.in_edge_list = w1_ge_id;
    else
    {
        graph_edge_id *cur = w1_node->node.in_edge_list;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = w1_ge_id;
    }

    // hash
    unsigned long long hash_rid = hash33(r_id);
    if (db->edge_table[hash_rid % EDGE_TABLE_LENGTH] == NULL)
        db->edge_table[hash_rid % EDGE_TABLE_LENGTH] = edge;
    else
    {
        graph_edge_list *hash_list = db->edge_table[hash_rid % EDGE_TABLE_LENGTH];
        while (hash_list->next != NULL)
            hash_list = hash_list->next;
        hash_list->next = edge;
    }
    return 0;
}

int add_word(graph *db, char *line)
{
    // create graph node, graph node list, save by hash table
    char *p = strtok(line, " ");

    graph_node node;

    strcpy(node.id, p);
    p = strtok(NULL, " ");
    strcpy(node.word, p);
    p = strtok(NULL, " ");

    // read sound freq
    word_freq_sound *data = (word_freq_sound *)malloc(sizeof(word_freq_sound));
    word_freq_sound *end_data = data;
    end_data->next = NULL;
    while (p != NULL)
    {
        char *tmp = strdup(p);
        char *spl = strchr(tmp, ',');
        *spl = 0;
        end_data->freq = atoi(spl);
        strcpy(end_data->sound, spl + strlen(spl) + 1);
        p = strtok(NULL, " ");
        free(tmp);
        if (p != NULL)
        {
            end_data->next = (word_freq_sound *)malloc(sizeof(word_freq_sound));
            end_data = end_data->next;
            end_data->next = NULL;
        }
    }

    // construct item
    graph_node_list *gnl = (graph_node_list *)malloc(sizeof(graph_node_list));
    node.word_fs = data;
    gnl->node = node;
    gnl->next = NULL;

    // put into hash
    unsigned long long hash_key = hash33(node.id);
    if (db->node_table[hash_key % NODE_TABLE_LENGTH] == NULL)
        db->node_table[hash_key % NODE_TABLE_LENGTH] = gnl;
    else
    {
        // ! no test this branch
        graph_node_list *now = db->node_table[hash_key % NODE_TABLE_LENGTH];
        while (now->next != NULL)
            now = now->next;
        now->next = gnl;
    }
    return 0;
}
