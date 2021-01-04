#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "query.h"


int main(int argc,char *argv[]){
    graph db;

    db.word_cnt = 0; //initialize
    db.total_cnt = 0;
    int cnt = sent_insert(&db,"台南\0很棒\0\0","w96j0_\0cp31;4\0\0");
    cnt = sent_insert(&db,"台南\0很好\0\0","w96j0_\0cp3cl3\0\0");
    db.word_cnt += cnt;
    db.total_cnt += cnt;
    graph_node_list* target = find_term_node(&db,"很棒啦\0");
    if(target!=NULL){
        printf("%s\n",target->node.word_fs->sound);
        printf("%d\n",target->node.word_fs->freq);
    }
    else{
        printf("not found!!\n");
    }
    return 0;
}