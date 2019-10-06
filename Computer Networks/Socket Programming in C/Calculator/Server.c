#include <stdlib.h> // for basic memmory allocation and deallocation
#include <stdio.h> // for file read and write
#include <netdb.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

#define MAX 100
#define PORT 8080 
#define SA struct sockaddr 



void doCalculation(int sockfd) 
{ 
	char buff[MAX]; 	// to store message from client
	int n; 				// for traversing buffer buff
	
	float a , b , result ;
	char ch ;
	
	
	// infinite loop for chat 
	for (;;) { 
	
		result = 0.00 ;
		a = 0 ;
		b = 0 ;
		bzero(buff, MAX); 		// empties the buffer

		// read the message from client and copy it in buffer 
		if ( read(sockfd, buff, sizeof(buff) ) == 0 ){
		
			printf(" --- Failed To Read \n --- Maybe Socket Is Closed .. \n --  Exiting \n ");
			return;
		
		}
		
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
		
		sscanf( buff , "%f%c%f" , &a, &ch, &b );
	
		printf("\n\n Operation Requested is %f %c %f \n",a,ch,b);
		
		
		
		switch( ch ){
		
			case '+' : result = a + b ;
						break ;
			case '-' : result = a - b ;
						break ;
			case '*' : result = a * b ;
						break ;
			case '/' : result = a / b ;
						break ;
			default : write( sockfd , "Invalid Token. " , sizeof("Invalid Token. ") );
			
		}
		
		write(sockfd,&result,sizeof(result));
	
	} 
	
	
	
} 


int main() 
{ 
	int sockfd, connfd, len; 				// create socket file descriptor 
	struct sockaddr_in servaddr, cli; 		// create structure object of sockaddr_in for client and server

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 			// creating a TCP socket ( SOCK_STREAM )
	
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	
	// empty the 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET;					// specifies address family with IPv4 Protocol 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 	// binds to any address
	servaddr.sin_port = htons(PORT); 				// binds to PORT specified

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 	// accepts connection from socket
	
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for recieving Expression and 
	doCalculation(connfd); 

	// After transfer close the socket 
	close(sockfd); 
} 

