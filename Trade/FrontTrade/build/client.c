#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX_BUF_SIZE 1024
#define PORT 9001 
int main() 
{  
    int sockfd, addrlen, n;  
    char buffer[MAX_BUF_SIZE] = {0}; 
    struct sockaddr_in addr; 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0)  
    {   
        fprintf(stderr, "socket falied\n");    
        exit(EXIT_FAILURE);
    }   
    addrlen = sizeof(struct sockaddr_in);  
    bzero(&addr, addrlen); 
    addr.sin_family = AF_INET;   
    addr.sin_port = htons(PORT); 
    addr.sin_addr.s_addr = inet_addr("192.168.1.20");  
    if(connect(sockfd,(struct sockaddr*)(&addr),sizeof(struct sockaddr)) == -1)
	{
		printf("connect error\n");
		exit(1);
	}
    while(1)  
    {    
        strcpy(buffer,"hello world");
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)(&addr), addrlen);      
        printf("client send msg is %s\n", buffer);    
        // n = recvfrom(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)(&addr), &addrlen);     
        // fprintf(stdout, "clinet Receive message from server is %s\n", buffer);  
    }  
    close(sockfd);   
    exit(0);  
    return 0;
}