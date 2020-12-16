#define ID_LENGTH 100
#define SOUND_LENGTH 100
#define WORD_LENGTH 1024
#define NODE_TABLE_LENGTH 200000
#define EDGE_TABLE_LENGTH 200000

typedef struct graph_edge graph_edge;
typedef struct word_ferq_sound word_ferq_sound;
typedef struct graph_node graph_node;
typedef struct graph_node graph_node;
typedef struct graph_edge_list graph_edge_list;
typedef struct graph graph;
typedef struct graph_node_list graph_node_list;
typedef struct node_table node_table;
typedef struct edge_table edge_table;
typedef struct graph graph;

struct graph_edge
{
    char id[ID_LENGTH];
    int pmi;
    graph_node *next_node;
};

struct graph_edge_list
{
    graph_edge edge;
    struct graph_edge_list *next;
};

struct word_ferq_sound
{
    int freq;
    char sound[SOUND_LENGTH];
    struct word_ferq_sound *next;
};

struct graph_node
{
    char id[ID_LENGTH];
    char word[WORD_LENGTH];
    word_ferq_sound *word_fs;
    graph_edge graph_edge_list;
};

struct graph_node_list
{
    graph_node graph_node;
    graph_node_list *next;
};

struct node_table
{
    graph_node_list *node_list[NODE_TABLE_LENGTH];
};

struct edge_table
{
    graph_edge_list *edge_list[EDGE_TABLE_LENGTH];
};

struct graph
{
    edge_table edge_hash_tb;
    node_table node_hash_tb;
    int word_cnt;
};
