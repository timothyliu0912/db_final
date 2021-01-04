#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

graph create_graph()
{
	graph db;
	db.word_cnt = 0; //initialize
	db.total_cnt = 0;
	return db;
}

unsigned long long hash33(unsigned char *key)
{
	unsigned char *ptr = key;
	unsigned long long hashv;

	hashv = 0;
	while (*ptr)
	{
		hashv = (hashv << 5) + hashv + *ptr++;
	}
	return hashv;
}

void md5(char *word, char *hash_code)
{
	MD5_CTX md5_context;
	MD5_Init(&md5_context);
	unsigned char decrypt[17];							  //存放加密後的結果
	MD5_Update(&md5_context, word, strlen((char *)word)); //對欲加密的字符進行加密
	MD5_Final(decrypt, &md5_context);
	char *ktr = hash_code;
	for (int i = 0; i < 16; i++)
	{
		sprintf(ktr, "%02x", decrypt[i]);
		ktr += 2;
	}
	ktr = '\0';
}

int sent_insert(graph *db, char *sent, char *sound)
{
	graph_node_list *front_node_ptr = NULL;
	graph_node_list *end_node_ptr = NULL;
	graph_node_list *check_node_ptr = NULL;
	graph_edge_id *edge_id_ptr = NULL;
	graph_node_list *item_ptr = NULL;
	graph_edge_list *real_edge_ptr = NULL;
	graph_edge_list *check_edge_ptr = NULL;
	word_freq_sound *check_sound_ptr = NULL;
	char *ptr = sent;
	char *str = sound;
	int w_cnt = 0;
	char term1[100];
	char sound1[100];
	char term2[100];
	char sound2[100];
	int i = 0;
	int find_flag = 0;
	char key1[33];
	char key2[33];
	char node_concat_key[65];
	char edge_key[33];
	unsigned long long hash_term_key1;
	unsigned long long hash_term_key2;
	memset(key1, '\0', sizeof(char) * 33);
	memset(key2, '\0', sizeof(char) * 33);
	memset(term1, '\0', sizeof(char) * 100);
	memset(sound1, '\0', sizeof(char) * 100);
	memset(term2, '\0', sizeof(char) * 100);
	memset(sound2, '\0', sizeof(char) * 100);
	while (*ptr)
	{
		w_cnt += 1;
		sscanf(ptr, "%s", term1);
		sscanf(str, "%s", sound1);
		int w_skip = strlen(ptr) + 1;
		int s_skip = strlen(str) + 1;
		ptr += w_skip;
		str += s_skip;
		if (strlen(ptr) == 0)
		{
			break;
			//todo: concat with <end> node
		}
		else
		{
			sscanf(ptr, "%s", term2);
			sscanf(str, "%s", sound2);
		}
		// create node1 key
		md5(term1, key1);
		hash_term_key1 = hash33(key1);
		//if fist pair
		if (front_node_ptr == NULL)
		{
			// check if node1 existed
			find_flag = 0;
			check_node_ptr = db->node_table[hash_term_key1 % NODE_TABLE_LENGTH];
			while (check_node_ptr != NULL)
			{
				if (strcmp(check_node_ptr->node.id, key1) == 0)
				{
					front_node_ptr = check_node_ptr;
					find_flag = 1;
					check_sound_ptr = check_node_ptr->node.word_fs;
					while (check_sound_ptr != NULL)
					{
						if (strcmp(check_sound_ptr->sound, sound1) == 0)
						{
							check_sound_ptr->freq += 1;
							break;
						}
						else
						{
							if (check_sound_ptr->next == NULL)
							{
								word_freq_sound *sound_data = (word_freq_sound *)malloc(sizeof(word_freq_sound));
								sound_data->freq = 1;
								strcpy(sound_data->sound, sound);
								sound_data->next = NULL;
								check_sound_ptr->next = sound_data;
								break;
							}
							else
							{
								check_sound_ptr = check_sound_ptr->next;
							}
						}
					}
					break;
				}
				else
				{
					if (check_node_ptr->next == NULL)
					{
						break;
					}
					else
					{
						check_node_ptr = check_node_ptr->next;
					}
				}
			}
			// create node1
			if (!find_flag)
			{
				graph_node_list *list_item1 = (graph_node_list *)malloc(sizeof(graph_node_list));
				graph_node new_node1; // = (graph_node*)malloc(sizeof(graph_node));
				strcpy(new_node1.id, key1);
				strcpy(new_node1.word, term1);
				word_freq_sound *sound_data = (word_freq_sound *)malloc(sizeof(word_freq_sound));
				sound_data->freq = 1;
				strcpy(sound_data->sound, sound1);
				sound_data->next = NULL;
				new_node1.word_fs = sound_data;
				new_node1.in_edge_list = NULL;
				new_node1.out_from_edge_list = NULL;
				list_item1->node = new_node1;
				list_item1->next = NULL;
				if (db->node_table[hash_term_key1 % NODE_TABLE_LENGTH] == NULL)
				{
					db->node_table[hash_term_key1 % NODE_TABLE_LENGTH] = list_item1;
				}
				else
				{
					check_node_ptr->next = list_item1;
				}
				front_node_ptr = list_item1;
			}
		}
		// create node2 key
		md5(term2, key2);
		hash_term_key2 = hash33(key2);
		// check if node2 existed
		find_flag = 0;
		check_node_ptr = db->node_table[hash_term_key2 % NODE_TABLE_LENGTH];
		while (check_node_ptr != NULL)
		{
			if (strcmp(check_node_ptr->node.id, key2) == 0)
			{
				end_node_ptr = check_node_ptr;
				find_flag = 1;
				check_sound_ptr = check_node_ptr->node.word_fs;
				while (check_sound_ptr != NULL)
				{
					if (strcmp(check_sound_ptr->sound, sound2) == 0)
					{
						check_sound_ptr->freq += 1;
						break;
					}
					else
					{
						if (check_sound_ptr->next == NULL)
						{
							word_freq_sound *sound_data2 = (word_freq_sound *)malloc(sizeof(word_freq_sound));
							sound_data2->freq = 1;
							strcpy(sound_data2->sound, sound2);
							sound_data2->next = NULL;
							check_sound_ptr->next = sound_data2;
							break;
						}
						else
						{
							check_sound_ptr = check_sound_ptr->next;
						}
					}
				}
				break;
			}
			else
			{
				if (check_node_ptr->next == NULL)
				{
					break;
				}
				else
				{
					check_node_ptr = check_node_ptr->next;
				}
			}
		}
		// create node2
		if (!find_flag)
		{
			graph_node_list *list_item2 = (graph_node_list *)malloc(sizeof(graph_node_list));
			graph_node new_node2; // = (graph_node*)malloc(sizeof(graph_node));
			strcpy(new_node2.id, key2);
			strcpy(new_node2.word, term2);
			word_freq_sound *sound_data2 = (word_freq_sound *)malloc(sizeof(word_freq_sound));
			sound_data2->freq = 1;
			strcpy(sound_data2->sound, sound2);
			sound_data2->next = NULL;
			new_node2.word_fs = sound_data2;
			new_node2.in_edge_list = NULL;
			new_node2.out_from_edge_list = NULL;
			list_item2->node = new_node2;
			list_item2->next = NULL;
			if (db->node_table[hash_term_key2 % NODE_TABLE_LENGTH] == NULL)
			{
				db->node_table[hash_term_key2 % NODE_TABLE_LENGTH] = list_item2;
			}
			else
			{
				check_node_ptr->next = list_item2;
			}
			end_node_ptr = list_item2;
		}
		// create edge key
		memset(node_concat_key, '\0', sizeof(char) * 65);
		strcat(node_concat_key, key1);
		strcat(node_concat_key, key2);
		memset(edge_key, '\0', sizeof(char) * 33);
		md5(node_concat_key, edge_key);
		unsigned long long hash_edge_key = hash33(edge_key);
		// create edge in edge table
		find_flag = 0;
		check_edge_ptr = db->edge_table[hash_edge_key % EDGE_TABLE_LENGTH];
		while (check_edge_ptr != NULL)
		{
			if (strcmp(check_edge_ptr->id, edge_key) == 0)
			{
				check_edge_ptr->freq++;
				find_flag = 1;
				break;
			}
			else
			{
				if (check_edge_ptr->next == NULL)
				{
					break;
				}
				else
				{
					check_edge_ptr = check_edge_ptr->next;
				}
			}
		}
		if (!find_flag)
		{
			graph_edge_list *real_edge = (graph_edge_list *)malloc(sizeof(graph_edge_list));
			strcpy(real_edge->id, edge_key);
			real_edge->freq = 1;
			real_edge->point_to = end_node_ptr;
			real_edge->point_from = front_node_ptr;
			real_edge->next = NULL;
			if (db->edge_table[hash_edge_key % EDGE_TABLE_LENGTH] == NULL)
			{
				db->edge_table[hash_edge_key % EDGE_TABLE_LENGTH] = real_edge;
			}
			else
			{
				check_edge_ptr->next = real_edge;
			}
			// create edge in node
			graph_edge_id *edge_id_for_front = (graph_edge_id *)malloc(sizeof(graph_edge_id));
			strcpy(edge_id_for_front->id, edge_key);
			edge_id_for_front->next = NULL;
			graph_edge_id *edge_id_for_end = (graph_edge_id *)malloc(sizeof(graph_edge_id));
			strcpy(edge_id_for_end->id, edge_key);
			edge_id_for_end->next = NULL;
			// build connect
			if (front_node_ptr->node.out_from_edge_list == NULL)
			{
				front_node_ptr->node.out_from_edge_list = edge_id_for_front;
			}
			else
			{
				edge_id_ptr = front_node_ptr->node.out_from_edge_list;
				while (edge_id_ptr->next != NULL)
				{
					edge_id_ptr = edge_id_ptr->next;
				}
				edge_id_ptr->next = edge_id_for_front;
			}
			if (end_node_ptr->node.in_edge_list == NULL)
			{
				end_node_ptr->node.in_edge_list = edge_id_for_end;
			}
			else
			{
				edge_id_ptr = end_node_ptr->node.in_edge_list;
				while (edge_id_ptr->next != NULL)
				{
					edge_id_ptr = edge_id_ptr->next;
				}
				edge_id_ptr->next = edge_id_for_end;
			}
		}
		front_node_ptr = end_node_ptr;
	}
	return w_cnt;
}