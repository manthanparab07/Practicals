#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define PORT 8080
#define SA struct sockaddr 

void sendMsg( int sockfd ){
	
	struct sockaddr_in clientAddr ;
	char buff[MAX];
	
	socklen_t addr_size = sizeof(clientAddr);
	
	recvfrom(sockfd,buff,MAX,0,(SA*)&clientAddr, &addr_size);
	// create file 
	FILE *fp;
	fp=fopen("mysqlScript.txt","r");		// open file uses both stdio and stdin header files
											// file should be present at the program directory

	if( fp == NULL ){
		printf("Error IN Opening File .. \n");
		return ;
	}
	
	bzero(buff,MAX);
	
	fseek(fp,0,SEEK_END);
  	size_t file_size=ftell(fp);
  	fseek(fp,0,SEEK_SET);
	
	if(fread(buff,file_size,1,fp)<=0)
    {
      printf("unable to copy file into buffer\n");
      exit(1);
    }
    
	 if(sendto(sockfd,buff,strlen(buff),0, (SA*)&clientAddr, addr_size)<0){
		printf("error in sending the file\n");
		exit(1);
	  	
  	}
  	bzero(buff,sizeof(buff));

	fclose (fp);							// close the file 
	
	printf("\nFile Sent successfully !!! \n");
	
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
