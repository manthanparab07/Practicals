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

void startChat(int sockfd , struct sockaddr_in servaddr){
	char buff[MAX];
	int noBytes;

		bzero(buff,sizeof(buff));
		
		printf("Enter Message : ");
		bzero(buff,sizeof(buff));
		noBytes = 0 ;
		while((buff[noBytes++]=getchar()) != '\n');
		noBytes = sendto(sockfd,buff,strlen(buff),0,(SA*)&servaddr,sizeof(servaddr));
		if( noBytes <= 0 ){
			printf("Error : In Sending..\n");
			return;
		}
		bzero(buff,sizeof(buff));

		FILE *fp = fopen("demo.txt","w");
		if(fp == NULL){
			printf("Error : In Opening File...\n");
		} 

		while( strncmp("exit",buff,4) != 0 ){
			
			bzero(buff,sizeof(buff));
			noBytes = recvfrom( sockfd , buff , sizeof(buff) , 0 , NULL , NULL );
			if( noBytes <= 0 ){
				printf("Error : In Recieving..\n");
				return;
			}
			fprintf(fp, "%s", buff);
		}
		fclose(fp);
		printf("File Recieved Successfully..\n");
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

	startChat(sockfd,servaddr);

	close(sockfd);
}