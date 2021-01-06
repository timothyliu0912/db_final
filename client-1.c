#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0;
    printf("hello\n");
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8700);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
        return 0;
    }
    printf("connect to server\n");
    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
    printf("%s\n",receiveMessage);
    while(1)
    {
        char send_query[100] = {0};
        if (send_query[strlen(send_query) - 1] == '\n')
            send_query[strlen(send_query)-1] == '\0';
        fgets(send_query,100,stdin);
        fflush(stdin);
        send(sockfd,send_query,200,0);
        //recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        //printf("%s",receiveMessage);
    }
    
    printf("close Socket\n");
    close(sockfd);
    return 0;
}