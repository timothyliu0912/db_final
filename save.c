#include "graph.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int db_save(graph *db, char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT, 0700);
    write(fd, "word\n", 5);
    // save word
    // word_id word freq sound

    for (int i = 0; i < NODE_TABLE_LENGTH; ++i)
    {
        // puts("12345");
        graph_node_list *cur = db->node_table[i];
        if (cur == NULL)
            continue;
        while (cur != NULL)
        {
            write(fd, cur->node.id, strlen(cur->node.id));
            write(fd, " ", 1);
            write(fd, cur->node.word, strlen(cur->node.word));
            write(fd, " ", 1);
            // // freq
            char freq_str[10];
            word_freq_sound *fs_cur = cur->node.word_fs;
            while (fs_cur != NULL)
            {
                sprintf(freq_str, "%d", fs_cur->freq);
                write(fd, freq_str, strlen(freq_str));
                write(fd, ",", 1);
                write(fd, fs_cur->sound, strlen(fs_cur->sound));
                write(fd, " ", 1);
                fs_cur = fs_cur->next;
            }
            cur = cur->next;
            write(fd, "\n", 1);
        }
    }

    // edge_id w1 w2 freq
    write(fd, "relation\n", 9);
    for(int i=0; i<EDGE_TABLE_LENGTH; ++i)
    {
        graph_edge_list *cur = db->edge_table[i];
        while(cur != NULL) {
            write(fd, cur->id, strlen(cur->id));
            write(fd, " ", 1);
            write(fd, cur->point_from->node.word, strlen(cur->point_from->node.word));
            write(fd, " ", 1);
            write(fd, cur->point_to->node.word, strlen(cur->point_to->node.word));
            write(fd, " ", 1);
            char freq_str[10];
            sprintf(freq_str, "%d", cur->freq);
            write(fd, freq_str, strlen(freq_str));            
            cur = cur->next;
            write(fd, "\n", 1);
        }
    }
    return close(fd);
}