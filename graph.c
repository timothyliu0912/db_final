#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sent_insert(graph *db, char *sent, MD5_CTX *context)
{
    char *ptr = sent;
    int w_cnt = 0;
    char tmp[100];
    memset(tmp, '\0', sizeof(char) * 100);
    while (ptr)
    {
        scanf(ptr, tmp);
        w_cnt += 1;
        //insert to table
        unsigned char decrypt[17]; //存放加密後的結果
        unsigned char encrypt[7] = "123456";
        MD5Update(context, encrypt, strlen((char *)encrypt)); //對欲加密的字符進行加密
        MD5Final(decrypt, context);
        for (int i = 0; i < 16; i++)
        {
            printf("%02x", decrypt[i]);
        }
        printf("\n");
        int skip = strlen(ptr) + 1;
        ptr += skip;
    }
    return w_cnt;
}