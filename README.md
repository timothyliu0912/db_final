# DB-Final

## structure

### Node

* _id: binary (md5(word))
* word: str
* count: int
* sound: List[str]
* next_edges: List[Edge*]
* prev_edges: List[Edge*]

### Edge

* _id: int binary (md5(prev_node->word) + md5(next_node->word))
* prev_node: Node*
* next_node: Node*
* weight: float, (PMI)
<!-- * factor -->

## Function

### insert
```c
int sent_insert(graph *db,char *sent,char *sound);
```

### update

```c
int update_term_property(graph* db, char *term, char* sound, int freq);
int update_edge_property_by_id(graph* db, char *edge_id, int w);
int update_edge_property(graph* db, char* word_from, char* word_to, int w);
```

### query

```c
graph_node_list* find_term_node(graph *db,char *term);
graph_node_list* find_term_node_by_id(graph *db,char *term_code);
graph_edge_list* find_edge_in_table(graph *db,char *front_term,char *end_term);
graph_edge_list* find_edge_in_table_by_id(graph *db,char *edge_code);
word_freq_sound* find_term_sound(graph *db,char *term,char *sound);
```
### predict

```c

```
