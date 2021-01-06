#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "graph.h"
#include "query.h"
#include "update.h"
#include "predict.h"
void *socket_thread(void *arg)
{
    int forClientSockfd = *((int *)arg);
    char message[] = {"Hi,this is server.\n"};
    send(forClientSockfd,message,sizeof(message),0);
    
    while(1)
    {
        int cli_recv;
        char inputBuffer[256] = {};
        cli_recv = recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("%d\n",cli_recv);
        if(cli_recv ==0)
        {
            perror("recv error\n");
            exit(EXIT_FAILURE);  
            break;
        }
        printf("Get:%s\n",inputBuffer);
    }
}
int main(int argc , char *argv[])
{   
    graph db = create_graph();

    //socket的建立
    char inputBuffer[256] = {};
    char message[] = {"Hi,this is server.\n"};
    int sockfd = 0, forClientSockfd;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    listen(sockfd,5);

    pthread_t tid[10];
    int i = 0;
    while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        if (pthread_create(&tid[i++],NULL,socket_thread,&forClientSockfd) != 0)
        {
            printf("failed to create thread\n");
        }
    }
    return 0;
}