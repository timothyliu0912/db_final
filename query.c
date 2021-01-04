#include<stdio.h>
#include<string.h>
#include"graph.h"
#include"query.h"

graph_node_list* find_term_node(graph *db,char *term){
    char key[33];
    memset(key,'\0',sizeof(char)*33);
    md5(term,key);
    unsigned long long hash_val = hash33(key);
    graph_node_list *ptr = db->node_table[hash_val%NODE_TABLE_LENGTH];
    
    if(db->node_table[hash_val%NODE_TABLE_LENGTH] == NULL){
            return NULL;
    }
    while(ptr!=NULL){
        if(strcmp(ptr->node.id,key) == 0){
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

graph_node_list* find_term_node_by_id(graph *db,char *term_code){
    unsigned long long hash_val = hash33(term_code);
    graph_node_list *ptr = db->node_table[hash_val%NODE_TABLE_LENGTH];
    while(ptr!=NULL){
        if(strcmp(ptr->node.id,term_code) == 0){
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

graph_edge_list* find_edge_in_table(graph *db,char *front_term,char *end_term){
    char key1[65];
    md5(front_term,key1);
    char key2[33];
    md5(end_term,key2);
    strcat(key1,key2);
    char edge_key[33];
    md5(key1,edge_key);
    unsigned long long hash_val = hash33(edge_key);
    graph_edge_list *ptr = db->edge_table[hash_val%NODE_TABLE_LENGTH];
    while(ptr!=NULL){
        if(strcmp(ptr->id,edge_key) == 0){
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

graph_edge_list* find_edge_in_table_by_id(graph *db,char *edge_code){
    unsigned long long hash_val = hash33(edge_code);
    graph_edge_list *ptr = db->edge_table[hash_val%NODE_TABLE_LENGTH];
    while(ptr!=NULL){
        if(strcmp(ptr->id,edge_code) == 0){
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;   
}

word_freq_sound* find_term_sound(graph *db,char *term,char *sound){
    graph_node_list *term_node = find_term_node(db,term);
    if(term_node == NULL){
        word_freq_sound *ptr = term_node->node.word_fs;
        while(ptr!=NULL){
            if(strcmp(ptr->sound,sound)==0){
                break;
            }else{
                ptr = ptr->next;
            }
        }
        return ptr;
    }
    else{
        return NULL;
    }
}