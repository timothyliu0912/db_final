#include "graph.h"
#include "load.h"
#include "predict.h"
#include "query.h"
#include "save.h"
#include "update.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_node(graph *db, char *word);
void print_edge(graph *db, char *word1, char *word2);
void process_line(char *line, char *bopomo, char *words);

void test_update(graph *db);
void test_insert(graph *db);
void test_predict(graph *db);

// !ERROR: sent_insert error
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    graph db = create_graph();

    char line[100000], bopomo[60000], words[40000];
    // sent insert
    int cnt = 0;
    while (fgets(line, 100000, fp))
    {
        if (cnt == 2)
            break;
        cnt++;

        // puts(line);
        line[strlen(line) - 1] = 0;
        memset(bopomo, 0, sizeof bopomo);
        memset(words, 0, sizeof words);
        process_line(line, bopomo, words);
        printf("%d\n", cnt);

        sent_insert(&db, words, bopomo);
    }
    // print_node(&db, "數學");
    // puts("1234");
    // save db
    // db_save(&db, "test");
}

void process_line(char *line, char *bopomo, char *words)
{
    char *buf = strtok(line, ","); // split word
    while (buf != NULL)
    {
        char *spl = strchr(buf, ' ');
        *spl = 0;
        strcat(words, buf);
        strcat(words, " ");
        strcat(bopomo, spl + 1);
        strcat(bopomo, " ");

        *spl = ' ';
        buf = strtok(NULL, ",");
    }
    char *p = words;

    while (*p != 0){
        if (*p == ' ')
            *p = 0;
        ++p;
    }
    *(p+1) = 0;

    p = bopomo;
    while (*p != 0){
        if (*p == ' ')
            *p = 0;
        ++p;
    }
    *(p+1) = 0;
    
    p = bopomo;
    while(*p != 0){
        puts(p);
        p = p + strlen(p) + 1;
    }
}

void print_node(graph *db,  char *word)
{
    graph_node_list *target = find_term_node(db, word);
    if (target != NULL)
    {
        printf("%s\n", target->node.word_fs->sound);
        printf("%d\n", target->node.word_fs->freq);
    }
    else
        printf("not found!!\n");
}
