#include <openssl/md5.h>
#include <unistd.h>
#define ID_LENGTH 33
#define SOUND_LENGTH 100
#define WORD_LENGTH 1024
#define NODE_TABLE_LENGTH 200000
#define EDGE_TABLE_LENGTH 200000

typedef struct graph_edge graph_edge;
typedef struct word_freq_sound word_freq_sound;
typedef struct graph_node graph_node;
typedef struct graph_edge_list graph_edge_list;
typedef struct graph graph;
typedef struct graph_node_list graph_node_list;
typedef struct graph_edge_id graph_edge_id;

struct graph_edge_id
{
    char id[ID_LENGTH];
    graph_edge_id *next;
};

struct graph_edge_list
{
    char id[ID_LENGTH];
    int freq;
    graph_node_list *point_to;
    graph_node_list *point_from;
    struct graph_edge_list *next;
};

struct word_freq_sound
{
    int freq;
    char sound[SOUND_LENGTH];
    struct word_freq_sound *next;
};

struct graph_node
{
    char id[ID_LENGTH];
    char word[WORD_LENGTH];
    word_freq_sound *word_fs;
    graph_edge_id *in_edge_list;
    graph_edge_id *out_from_edge_list;
};

struct graph_node_list
{
    graph_node node;
    graph_node_list *next; // for hash
};

struct graph
{
    graph_node_list *node_table[NODE_TABLE_LENGTH];
    graph_edge_list *edge_table[EDGE_TABLE_LENGTH];
    int word_cnt;
    int total_cnt;
};

void md5(char *word,char *hash_code);
unsigned long long hash33(unsigned char *key);
int sent_insert(graph *db,char *sent,char *sound);
graph create_graph();