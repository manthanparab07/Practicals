---
title: Socket Programming in C
---

> ##### bzero(buff, MAX)

		#include <strings.h>
   		void bzero(void *s , size_t n );
	
- The **bzero**() function erases the data in the _n_ bytes of the memory starting at the location pointed to by _s_, by writing zeros (bytes containing '\\0') to that area.

- **size_t** is of `unsigned int` data type that ensures that it always represents a positive value. It is used to represent the size of an allocated block of memory.

> ##### read(sockfd, buff, sizeof(buff)); 

		#include <unistd.h>
		ssize_t read(int fd, void *buf, size_t count);

- read - read from a file descriptor
- **read**() attempts to read up to `count` bytes from file descriptor `fd` into the buffer starting at `buf`.
- `ssize_t` is the same as `size_t`, but is a signed type - read `ssize_t` as “signed `size_t`”. `ssize_t` is able to represent the number `-1`, which is returned by several system calls and library functions as a way to indicate error.

- ##### RETURN VALUE  

	- On success, the number of bytes read is returned 
	- (zero indicates end of file), and the file position is advanced by this number.
	- Negative Number means errorin read operation.

> getchar() 

		#include <stdio.h>
		int getchar(void);

- get a byte from a _stdin_ stream

> ##### write(sockfd, buff, sizeof(buff));

- write - write to a file descriptor


		#include <unistd.h>
		ssize_t write(int fd, const void *buf, size_t count);

- **write**() writes up to _count_ bytes from the buffer starting at _buf_ to the file referred to by the file descriptor _fd_.
- return value indicates the no of bytes written in socket. Reeturn value  -1 indicates error in writing. 


> #### struct sockaddr_in servaddr, cli;

- Create struct object of sockaddr_in which has following prototype.

		struct sockaddr_in {
        sa_family_t    sin_family; /* address family: AF\_INET */
        in_port_t      sin_port;   /* port in network byte order */
        struct in_addr sin_addr;   /* internet address */
  		};
		
		 \* Internet address. */
         struct in_addr {
            uint32_t  s_addr;     /* address in network byte order */
         };

- On raw sockets _sin_port_ is set to the IP protocol.

		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <netinet/ip.h>  \* superset of previous */

		tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
		udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
		raw_socket = socket(AF_INET, SOCK_RAW, protocol);

> #### Socket Syntax 
> sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	

		#include <sys/types.h>          /* See NOTES */
		#include <sys/socket.h>
		
		int socket(int domain, int type, int protocol);

- `socket()` creates an endpoint for communication and returns a file descriptor that refers to that endpoint.
- `domain` refers to communication domain such as local communical (UNIX), IPv4, IPv6 ...

		AF_INET - IPv4 Internet protocols

- The socket has the indicated `type`, which specifies the communication semantics such as TCP , UDP , RAW given by
	
		TCP - SOCK_STREAM 
		UDP - SOCK_UDP
		RAW - SOCK_RAW

- `protocol` specify protocol type - 0
- #### Return type 

	- On **success**, a file descriptor for the new socket is returned. 
	- On **error**, -1 is returned,


> #### Intialize Struct Object
> 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT); 	

- s_addr - stands for special address
- The s_addr member of struct sin_addr contains the host interface address in network byte order.
- There are several special addresses: 
- 	**INADDR_LOOPBACK** (127.0.0.1) always refers to the local host via the loopback device; 
- 	**INADDR_ANY** (0.0.0.0) means any address for binding.

- The **htonl**() function converts the unsigned integer **hostlong** from host byte order to network byte order.

- The **htons**() function converts the unsigned short integer **hostshort** from host byte order to network byte order.

> #### BIND 
> bind(sockfd, (SA*)&servaddr, sizeof(servaddr))
> 

	#include <sys/types.h>         
	#include <sys/socket.h>
	int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	
	struct sockaddr {
	    sa_family_t sa_family;
	    char        sa_data[14];
	}
		   
- ##### This operation is called “assigning a name to a socket”.
- **bind**() assigns the address specified by _addr_ to the socket referred to by the file descriptor sockfd.
- ##### The only purpose of this structure `soc_addr` is to cast the structure pointer passed in _addr_ in order to avoid compiler warnings.

> ##### LISTEN 
> listen(sockfd, 5)

- listen - listen for connections on a socket
		
		#include <sys/types.h>          
		#include <sys/socket.h>
		
		int listen(int sockfd, int backlog);

- listen() marks the socket referred to by sockfd as a passive socket,that is, as a socket that will be used to accept incoming connection requests using `accept`.
- The _backlog_ argument defines the maximum length to which the queue of pending connections for _sockfd_ may grow.  
- If a connection request arrives when the queue is full, the client may receive an error with an indication of **ECONNREFUSED** or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

> #### Accept 
> accept(sockfd, (SA*)&cli, &len);
> 

- accept a connection on a socket.

	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

- USED for connection based ( TCP ) 
-  It extracts the first connection request on the queue of pending connections for the listening socket, _sockfd_, creates a new connected socket, and returns a new file descriptor referring to that socket. 
-  The newly created socket is not in the listening state.  
-  The original socket _sockfd_ is unaffected by this call. 