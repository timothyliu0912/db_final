typedef struct
{
    char word[10];
    double score;
} predicted_word;

typedef struct
{
    int length;
    predicted_word candidates[100];
} predicted_word_list;

predicted_word_list predict_next_word(graph *db, char *sent);
double cal_pmi(int x_freq, int y_freq, int xy_freq, int tot_cnt);
predicted_word create_predicted_word(char *word, double score);

