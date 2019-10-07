#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX 100
#define PORT 8080
#define SA struct sockaddr 

void recvMsg( int sockfd , struct sockaddr_in serverAddr ){
	
	char buff[MAX];
	
	  while(1){
	  	
	  	bzero(buff,MAX);
		printf("Message : ");
		fgets(buff,MAX,stdin);
		
		/*Send message to server*/
		sendto(sockfd,buff,strlen(buff),0,(SA*)&serverAddr,sizeof(serverAddr));
		
		if( strncmp("exit",buff,4) == 0 ){
			printf("Exiting .." );
			return ;
		}
		
		bzero(buff,MAX);
		
		/*Receive message from server*/
		recvfrom(sockfd,buff,MAX,0,NULL, NULL);

		printf("Server Response : %s\n",buff);

	  }

}

int main(){

  int sockfd;
  struct sockaddr_in serverAddr;
  
  /*Create UDP socket*/
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));  

  recvMsg(sockfd,serverAddr);
  
  close(sockfd);

  return 0;
}
