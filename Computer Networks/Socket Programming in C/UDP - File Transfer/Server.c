#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080
#define MAX 30
#define SA struct sockaddr

void startChat(int sockfd){
	char buff[MAX];
	int noBytes;
	
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);

		bzero(buff,sizeof(buff));
		noBytes = recvfrom( sockfd , buff , sizeof(buff) , 0 , (SA*) &cliaddr , &len );
		if( noBytes <= 0 ){
			printf("Error : In Recieving..\n");
			return;
		}else
			printf("Client : %s", buff );

		bzero(buff,sizeof(buff));
		
		FILE *fp = fopen("lol.txt","r");

		if(fp == NULL){
			printf("Error : In Opening File...\n");
		}

		bzero(buff,sizeof(buff));

		while( fgets(buff,sizeof(buff),fp) != NULL ){
			noBytes = sendto(sockfd,buff,strlen(buff),0,(SA*)&cliaddr,len);
			if( noBytes <= 0 ){
				printf("Error : In Sending..\n");
				return;
			}
			bzero(buff,sizeof(buff));
			noBytes = 0 ;
		}


		strcpy(buff,"exit");
		 sendto(sockfd,buff,strlen(buff),0,(SA*)&cliaddr,len);

		printf("File Sent Successfully..\n");
		return;
}

void main(){
	int sockfd ;
	struct sockaddr_in servaddr ;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	if(sockfd == -1){
		printf("Error : Socket Creations Failed..\n");
		exit(0);
	}else
		printf("Socket Created..\n");

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);


	if( bind(sockfd,(SA*)&servaddr,sizeof(servaddr)) != 0 ){
		printf("Error  : Bind Failed..\n");
		exit(0);
	}else	
		printf("Bind Successfull..\n");

	startChat(sockfd);

	close(sockfd);
}