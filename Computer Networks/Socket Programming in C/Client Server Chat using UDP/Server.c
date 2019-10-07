#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define PORT 8080
#define SA struct sockaddr 

void sendMsg( int sockfd ){
	
	struct sockaddr_in clientAddr ;
	char buff[MAX];
	
	socklen_t addr_size = sizeof(clientAddr);

	  while(1){
		/* Try to receive any incoming UDP datagram. Address and port of 
		  requesting client will be stored on serverStorage variable */
		recvfrom(sockfd,buff,MAX,0,(SA*)&clientAddr, &addr_size);
		
		if( strncmp("exit",buff,4) == 0 ){
			printf("Server Exiting...");
			return ;
		}
		
		printf("\nClient Response : %s",buff);
		
		bzero(buff,MAX);
		printf("Message : ");
		fgets(buff,MAX,stdin);
		
		/*Send uppercase message back to client, using serverStorage as the address*/
		sendto(sockfd,buff,strlen(buff),0,(SA*)&clientAddr,addr_size);
		
	  }
	

}

int main(){

  int sockfd ;
  struct sockaddr_in serverAddr;

  /* Create UDP socket */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl( INADDR_ANY );
  
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));  

  /*Bind socket with address struct*/
  bind(sockfd, (SA*) &serverAddr, sizeof(serverAddr));

  sendMsg(sockfd);
  
  close(sockfd);
  
  return 0;
  
  }
