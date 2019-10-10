#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX 1000
#define PORT 8080
#define SA struct sockaddr 

void recvMsg( int sockfd , struct sockaddr_in serverAddr ){
	
	char buff[MAX];
	socklen_t addr_size = sizeof(serverAddr);
	
	
	bzero(buff,MAX);
	printf("File Name : ");
	fgets(buff,MAX,stdin);
		
		/*Send message to server*/
	sendto(sockfd,buff,strlen(buff),0,(SA*)&serverAddr,sizeof(serverAddr));
		
	if( strncmp("exit",buff,4) == 0 ){
		printf("Exiting .." );
		return ;
	}
		
	FILE *fp;
	fp=fopen("received.txt","w"); // stores the file content in recieved.txt in the program directory
	bzero(buff,MAX);
	
	if( fp == NULL ){
		printf("Error IN Opening File ");
		return ;
	}
	
	
	if( recvfrom(sockfd,buff,MAX,0,(SA*)&serverAddr,&addr_size) < 0 ){
	
		printf("Error In Recieving Files");
		return ;
	
	}
	
	if(fwrite(buff,1,strlen(buff),fp)<0)
    {
      printf("Error writting file\n");
      return ;
    }
    
	printf("File received successfully !! \n");
	printf("New File created is received.txt !! \n");

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
