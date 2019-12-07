>   ### Application Layer Protocol

### Electronic Mail

-   Architecture

    -   To explain the architecture of e-mail, we give four scenarios.

        -   First Case
            -   The sender and the receiver of the e-mail are users (or application programs) on the same system; they are directly connected to a shared system.
            -   **When the sender and the receiver of an e-mail are on the same system, we need only two user agents.**

        -   Second Scenario
            -    The sender and the receiver of the e-mail are users (or application
                programs) on two different systems. 
            -   The message needs to be sent over the Internet.
            -   **When the sender and the receiver of an e-mail are on different systems, we need two UAs and a pair of MTAs (client and server).**

        -   Third Scenario
            -   If one of the user (**sender**) is not directly connected to the mail system but are connected via LAN or WLAN while other are directly connected to the file system.
            -   **When the sender is connected to the mail server via a LAN or a WAN, we need two UAs and two pairs of MTAs (client and server).**

        -   Fourth Scenario
            -   When both sender and receiver are connected via LAN or WLAN .
            -   Then additional  MAA (**message access agent**) is used at receiver side.
            -    **When both sender and receiver are connected to the mail server via a LAN or a WAN,we need two UAs, two pairs of MTAs (client and server), and a pair of MAA (client and server).**

![image-20191206101201904](/home/hades/.config/Typora/typora-user-images/image-20191206101201904.png)

### MIME (Multipurpose Internet Mail Extensions)

-   As electronic mail has a simple structure there results in limitations such as
    -   It cannot send **NON ASCII** character i.e text in an other language.
    -   **Cannot** send binary , audio , video File.

-   MIME is a supplementary protocol that allows non-ASCII data to be sent through e-mail.
-   MIME transforms non-ASCII data at the sender site to NVT ASCII data and delivers them to the client MTA to be sent through the Internet.
-    The message at the receiving side is transformed back to the original data.
-   NVT (**Network Virtual Terminal**) Character Set
    -   It has two sets of characters, one for data and the other for control. 
    -   Both are 8-bit bytes.
    -    For data, NVT is an 8-bit character set in which the 7 lowest-order bits are the same as ASCII and the highest-order bit is **O** .
    -    To send **control** characters between computers (from client to server or vice versa), NVT uses an 8-bit character set in which the highest-order bit is set to **1** .

![image-20191206101940266](/home/hades/.config/Typora/typora-user-images/image-20191206101940266.png)

#### MIME defines five headers that can be added to the original e-mail header section to define the transformation parameters:

1. **MIME-Version**
    -   defines the version of MIME used.
2. **Content-Type**
    -   This header defines the type of data used in the body of the message.
    -   The content type ( TEXT , AUDIO  , VIDEO  ) and the content subtype ( HTML , PLAIN , JPEG , PNG ) are separated by a slash.
    -   Ex. HTML , Plain Text , AUDIO , VIDEO , BINARY ..etc
3. **Content-Transfer-Encoding**
    -   defines the method used to encode the messages into Os and Is for transport:
4. **Content-Id**
    -   uniquely identifies the whole message in a multiple-message environment.
5. **Content-Description**
    -   defines whether the body is image, audio, or video.

### Message Transfer Agent: SMTP

-   It is a push protocol.
-   The actual mail transfer is done through message transfer agents. To send mail, a system must have the client MTA, and to receive mail, a system must have a server MTA.
-   Similar to fourth scenario in email architecture .
-   SMTP is used two times, between the sender and the sender's mail server and between the two mail servers.

-   #### Command and responses 

    -   **SMTP uses commands and responses to transfer messages between an MTA client and
        an MTA server**.

    -   Each command or reply is terminated by a two-character (**carriage return and line feed**) end-of-line token.

    -   Command Format

        -   **Send From client to server.**
        -    Command **Keyword : arguments ( 0 or more )**

        -   Keywords                 Arguments
        -   HELO                          Sender's host name
        -   MAIL FROM             Sender of the message
        -   RCPTTO                     Intended recipient of the message
        -   DATA                          Body of the mail
        -   QUIT                           [no argument]
        -   RSET                          [no argument]
        -   HELP                          Commands

    -   Response Format
        -   It is sent form server to client.
        -   **A response is a three-digit code that may be followed by additional textual information.**

-   **Mail Transfer Phases**
    -   The process of transferring a mail message occurs in three phases:
        -   connection establishment, 
        -   mail transfer, and
        -   connection termination.

Message Access Agent: POP and IMAP 

-   It is a pull protocol.
-   It is used to fetch data from the mail server to the receiver .

### Post Office Protocol (POP)

-   It is software is installed on the recipient computer.
-   Mail access starts with the client when the user needs to download e-mail from the mailbox on the mail server. 
-   The client opens a connection to the server on **TCP port 110**. 
-   It then sends its user name and password to access the mailbox. The user can then list
    and retrieve the mail messages, one by one.
-   POP3 has **two modes** : **the delete mode and the keep mode.** 
-   In the delete mode, the mail is deleted from the mailbox after each retrieval. In the keep mode, the mail remains in the mailbox after retrieval. 
-   The **delete** mode is normally used when the user is working at her permanent computer and can save and organise the received mail after reading or replying.
-    The **keep** mode is normally used when the user accesses her mail away from her primary computer (e.g., a laptop). The mail is read but kept in the system for later retrieval and organising.

#### Dis Advantage

-   It does not allow the user to organise her mail on the server.
-   The user cannot have different folders on the server.

### Internet Message Access Protocol (IMAP)

-   IMAP is more powerful than POP and has more features.

-   IMAP Functionality 
    1.   A user can check the e-mail header prior to downloading.
    2.  A user can search the contents of the e-mail for a specific string of characters prior to downloading.
    3.  A user can partially download e-mail. This is especially useful if bandwidth is limited and the e-mail contains multimedia with high bandwidth requirements.
    4.  A user can create, delete, or rename mailboxes on the mail server.
    5.  A user can create a hierarchy of mailboxes in a folder for e-mail storage.

### File Transfer Protocol (FTP)

-   It is the standard mechanism provided by **TCP/IP** for copying a file from one host to another.
-   FTP resolves several file transfer issues such as 
    1.  different file name conventions
    2.  different ways to represent text and data
    3.  different directory
        structures

-   It establishes two connections between the hosts. One connection is used for **data transfer**, the  other for **control information** (commands and responses). 
-   Port **20** is used for data connection and Port **21** is used for control connection  .
-   The client has three components: user interface, client control process, and the client data transfer process. 
-   The server has two components: the server control process and the server data transfer process. 
-   The control connection is made between the control processes. The data connection is made between the data transfer processes.

-   **When a user starts an FTP session, the control connection opens. While the control connection is open, the data connection can be opened and closed multiple times if several files are transferred. **

#### Communication over DATA connection

-   Each command or response is only one short line, so we need not worry about file format or file  structure. 
-   Each line is terminated with a two-character (carriage return and line feed) end-of-line token.

#### Communication over Data Connection

-   Three types 
    1.  A file is to be copied from the **server to the client**. This is called retrieving a file. It
        is done under the supervision of the **RETR** command.
    2.  A file is to be copied from the **client to the server**. This is called storing a file. It is done under the supervision of the STOR command.
    3.  A list of directory or file names is to be sent from the **server to the client**. This is done under the supervision of the LIST command.

#### Anonymous FTP

-   For public access, to enable anonymous FTP. To access these files, a user does not need to have an account or password. 
-   Instead, the user can use **anonymous** as the user name and **guest** as the password.
-   User access to the system is very limited .

### HTTP (HyperText Transfer Protocol)

-   It is a protocol used mainly to access data on the World Wide Web. 
-   HTTP functions as a combination of FTP and SMTP.
-   Similar to FTP because it transfer files using the services of TCP but differs that it has only one connection and no seperate control connection.
-   Similar to SMTP because the data transferred is looks like SMTP messages and the format of message is like MIME like  Headers.
-   But difference is SMTP is interpreted by user but HTTP message is interpreted by browser. 
-   Uses Well Known Port 80.

#### Structure 

-   **Request and Status Lines** 
    -   The first line in a request message is called a request line; the first line in the response message is called the status line.

-   ### Request type

    -   Request type can be categorised into different types.
        -   GET                Requests a document from the server
        -   HEAD            Requests information about a document but not the document itself
        -   POST             Sends some information from the client to the server
        -   PUT                Sends a document from the server to the client
        -   TRACE           Echoes the incoming request
        -   CONNECT    Reserved
        -   OPTION        Inquires about available options

-   Status Code 
    -   It is a three bit field like those in SMTP and FTP protocol.

-   Status phrase. 
    -   This field is used in the response message.
    -    It explains the status code in text form. 

-   Header 
    -   The header exchanges additional information between the client and the server.

-   BODY 
    -   The body can be present in a request or response message. Usually, it contains
        the document to be sent or received.

#### Persistent Versus Non persistent Connection

-   Nonpersistent Connection
    -   In a non persistent connection, **one TCP connection is made for each request/response**.
        The following lists the steps in this strategy:
        -   The client opens a TCP connection and sends a request.
        -   The server sends the response and closes the connection.
        -   The client reads the data until it encounters an end-of-file marker; it then closes the
            connection.

-   In this strategy, for N different pictures in different files, the connection must be opened and closed N times. The non persistent strategy imposes high overhead on the server because the server needs N different buffers and requires a slow start procedure each
    time a connection is opened.

#### Persistent Connection

-   In a persistent connection, the server leaves the connection open for more requests after sending a response.
-   The server can close the connection at the request of a client or if a time-out has been reached.
-   The sender usually sends the length of the data with each response.

### Dynamic Host Configuration Protocol (DHCP)

-   It’s goal is to assign unique network (IP address) to the hosts .

-   It also provides other network address such as default gateway , subnet mask , and DNS address 

-   It is implemented as a Client/Server architecture.

-   The hosts run DHCP client whereas a router or a dedicated DHCP server can be used to DHCP server Program.

-   Prevent Manual Allocation of IP address by network administrator when the no of computers connected to a network is large.

-   Steps 

    1.  At network initialisation the host runs DHCP Client Program whereas somewhere in the network DHCP server will be running.

    2.  **DHCP Discover Message**

        -   Host searches for DHCP server on the network by sending a **broadcast address.**

        -   When the Client does not have an address it looks for DHCP server it then sends a broadcast message to all other devices on the network to identify and communicate to DHCP server .
        -   IP Sender      **0.0.0.0**   UDP Port **68** (As sender does not have an IP) ( 68 is reserved by DHCP CLIENT program )
        -   IP receiver  **255.255.255.255** UDP Port **67 **( 67 is reserved for DHCP Server )

    3.  **DHCP Offer**
        -   When the DHCP server receives the message  it then sends an IP address to the host as an **OFFER** along with expiration time .
        -   IP Sender       192.168.1.1 Port **67** ( This is the allocated IP offer ).
        -   IP Receiver    255.255.255.255 Port 68  

    4.  **DHCP Request**
        -   When the host accepts the IP address then it sends an request message to accept this IP address to the DHCP server.
        -   DHCP request sent to every on to the network as it is broadcast. 
        -   Shows it intent to accept specific offer.
        -   IP sender 0.0.0.0 UDP Port 68   --> Client to Server
        -   IP receiver 255.255.255.255 Port 67 --> Server 

    5.  **DHCP ACK**
        -   ​	When the DHCP server recieves request message then it sends the IP address to the host along with the subnet mask , default gateway and DNS address .
        -   The DHCP server then adds the host computer and its IP address in it’s allocated IP table along with Expiration time .
        -   The Expiration time allows the server to revoke the IP  address if the host do not ask for the address after expiration time . Useful when the host is disconnected or dropped.
        -   It will confirm that the host can start using the address for that negotiated amount of time.
        -   IP Sender 192.168.1.1 Port 67  ( It’s DHCP server IP address ) (server --> client)
        -   IP Receiver 255.255.255.255 Port 68 ( broadcast address )

Multiple DHCP server can be present in a network then the first request is considered.

-   DHCP decline - decline IP address allocated if the IP address is invalid or corrupted
-   DHCP release - to cancel the IP address allocation and release the lease time.
-   