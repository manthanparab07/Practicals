// Write CPP code here 
#include <netdb.h> 
#include <stdio.h> 		
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#define MAX 100
#define PORT 8080 
#define SA struct sockaddr 

void sendCalculation(int sockfd) 
{ 
	char buff[MAX]; 	// to store expression from client
	for( ;; ){
		bzero(buff,MAX);	// empty the buffer 
		
		printf("\n\nEnter Expression ( exit ) : ");
		scanf("%s",buff);
		write(sockfd , buff , sizeof(buff) );		// write to the stream 
		if(strncmp("exit",buff,4) == 0 ){
		
			printf("Exiting ...\n");
			return ;
			
		}
		bzero(buff,MAX);
		read(sockfd,buff,sizeof(buff));
		printf("Operation Result : %f",*((float*)buff));		// convert char ptr to float ptr then to float
	}
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for sending Expression 
	sendCalculation(sockfd); 

	// close the socket 
	close(sockfd); 
} 


