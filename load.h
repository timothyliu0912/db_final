typedef enum  {
    WORD,
    RELATION,
} LOAD_STATUS;

int db_load(graph* db, char *path);
int add_word(graph *db, char *line);
int add_relation(graph *db, char *line);