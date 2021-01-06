#include "graph.h"
#include "query.h"
#include "update.h"
#include "predict.h"
#include "load.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_node(graph *db,  char *word);
void print_edge(graph *db,  char *word1,  char *word2);
void test_update(graph *db);
void test_insert(graph *db);
void test_predict(graph* db);
void test_save(graph* db);

int main()
{
    graph db = create_graph();
    db_load(&db, "test");
    test_insert(&db);
    test_update(&db);
    // test_save(&db);
}


void test_save(graph *db)
{
    db_save(db, "test");
}

void test_update(graph *db)
{
    update_term_property(db, "台南", "w123\00cp31\0", 333);
    graph_node_list *target = find_term_node(db, "台南\0");
    print_node(db, "台南");
    
    update_edge_property(db, "台南", "很好", 10000);
    print_edge(db, "台南", "很好");
    print_edge(db, "台南", "很棒");
}

void test_insert(graph *db)
{
    int cnt = sent_insert(db, "台南\0很棒\0個屁\0\0", "w96j0_\0cp31;4\0ek7qu4\0\0");
    cnt = sent_insert(db, "台南\0很好\0\0", "w96j0_\0cp3cl3\0\0");
    db->word_cnt += cnt;
    db->total_cnt += cnt;
    print_node(db, "台南");
}

void test_predict(graph* db)
{
    char desc[10];
    predicted_word_list result = predict_next_word(db, "台南\0很棒\0\0");
    for(int i=0; i<result.length; ++i)
    {
        printf("%s: %lf\n", result.candidates[i].word, result.candidates[i].score);
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
    {
        printf("not found!!\n");
    }
}

void print_edge(graph* db,  char* word1,  char* word2)
{
    graph_edge_list* t = find_edge_in_table(db, word1, word2);
    printf("%s\t%s: %d\n", word1, word2, t->freq);
}