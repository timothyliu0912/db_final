#include "graph.h"
#include "predict.h"
#include "query.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

predicted_word create_predicted_word(char *word, double score)
{
    predicted_word t;
    strcpy(t.word, word);
    t.score = score;
    return t;
}

inline double cal_pmi(int x_freq, int y_freq, int xy_freq, int tot_cnt)
{
    // log(pxy(x,y)/(p(x)*p(y)),2)
    double px = (double)x_freq / tot_cnt,
           py = (double)y_freq / tot_cnt,
           pxy = (double)xy_freq / tot_cnt;
    return log2(pxy / (px * py));
}

predicted_word_list predict_next_word(graph *db, char *sent)
{
    char *last_word = sent;
    predicted_word_list cands;
    int cand_idx = 0;
    while (last_word)
    {
        int word_len = strlen(last_word) + 1;
        if (*(last_word + word_len) == 0)
        {
            break;
        }
        last_word += word_len;
    }
    graph_node a_node = find_term_node(db, last_word)->node;
    graph_edge_id *now_edge_id = a_node.out_from_edge_list;
    while (now_edge_id != NULL)
    {
        graph_edge_list *edge = find_edge_in_table_by_id(db, now_edge_id->id);
        graph_node b_node = edge->point_to->node;
        double pmi = cal_pmi(a_node.word_fs->freq, b_node.word_fs->freq, edge->freq, db->total_cnt);
        cands.candidates[cand_idx++] = create_predicted_word(b_node.word, pmi);
        // pick the word's next edge
        now_edge_id = now_edge_id->next;
    }
    cands.length = cand_idx;
    return cands;
}