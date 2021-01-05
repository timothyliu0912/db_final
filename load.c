#include "load.h"
#include "graph.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

graph db_load(char *path)
{
    FILE *fp = fopen(path, "r");
    LOAD_STATUS status = WORD;
    graph db = create_graph();


    char line[2048];

    while (fgets(line, 2048, fp))
    {
        line[strlen(line) - 1] = 0;
        if (!strcmp(line, "word"))
        {
            status = WORD;
        }
        else if (!strcmp(line, "relation"))
        {
            status = RELATION;
        }
        else if (status == WORD)
        {
            add_word(&db, line);
        }
        else if (status == RELATION)
        {
            add_relation(&db, line);
        }
    }
    return db;
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
        char *spl = strchr(tmp, ",");
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
    graph_node_list* now = db->node_table[hash_key % NODE_TABLE_LENGTH];
    while(now->next != NULL) {
        now = now->next;
    }
    now->next = gnl;
}
