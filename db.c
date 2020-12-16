#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
// #include "md5.h"

int main(int argc,char *argv[]){
    puts("1235");
    MD5_CTX md5;  
    MD5Init(&md5); 
    graph db;
    puts("1235");

    db.word_cnt = 0; //initialize
    db.total_cnt = 0;
    int cnt = sent_insert(&db,"apple banana",&md5);
    puts("1235");

    printf("%d\n",cnt);
    return 0;
}