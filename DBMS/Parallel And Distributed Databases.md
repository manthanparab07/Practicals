>   ### Parallel And Distributed Databases

-   Parallel query processing enable the faster operations of databases i.e **faster** response to the transaction.
-   Distributed Databases allows the data to reside where they are generated or **most** needed but still accessible to other sites or departments. Data can reside across different geographical location and multiple copies can be created to ensure that even if one fails other database is employed in case of failure and also for data backup.  

### Types of Parallelism

1.  **Coarse Granularity Parallelism**
    -   Computer system having fewer number of processors and all sharing same main memory.
    -   Database running on such machine do not attempt to partition a single query across different cores but instead execute single transaction on each core as a result the throughput of the database increases although the time required to execute each transaction does not changes. 

2.  **Fine Granularity Parallelism **
    -   The computer has large no of processors and the database running on these machine attempt to parallelize single task ( i.e queries ).

### Transaction Remote Procedure Calls

-   It is an interface that is used to connect a client and a server.
-   These calls appear to be as a ordinary procedure call to the programmer but all the procedure calls are wrapped inside a transaction at the server side so that in case the transaction fails the system is able to undo the effect of individual remote procedure calls(RPC). 

-   JDBC , ODBC .. etc

### Speed Up

-   Running a given task in lesser time by increasing the degree of parallelism.
-   Focuses on reducing time taken to execute a given task.

### Scale Up

-   Handling a large no. of task by increasing the degree of parallelism.
-   Focuses on handling more task at a given time.
-   Scale-up relates to the ability to process larger tasks in the same amount of time by providing more resources

### Linear and sub linear Speed up

-   Suppose that the execution time of a task on a larger machine is **T(L)**  while the execution time of the same task on a smaller machine is **T(S)**.
-   The **speedup** due to parallelism is defined as **T(S)/T(L)** .
-   The parallel system is said to have a **linear** speed if the speed up is N when the larger system has up to N time more resources than the smaller system.
-   zIf the speed up is less than N then it is called **sub linear** speed up.

### Linear and sub linear Scale up

-   Scale up relates to the ability to process larger tasks in the same amount of time by providing more resources.
-   --  go to book 775 

### Parallel Database Architectures

-   To ensure parallelism different processor must communicate with each other.

1.  **Shared Memory**

    -   All processor in a system share **same** Memory and disk ( where the actual data of database is present ) via bus or interconnection network( bus , mesh , hyper cube ).
    -   **Advantage** 
        -   Due to shared memory , the processor have **excellent** communication with other processors i.e data in shared memory can be accessed by any processor without being moved with software.

    -   **Disadvantage**
        -   Shared-memory machines is that the architecture is not scalable beyond 32 or 64 processors because the **memory bus** or the interconnection network becomes a **bottleneck** (since it is shared by all processors).

    -   Moreover as each processor can have large cache’s which can store the data used by processor and can avoid access to shared memory but however it’s not always there and the processor might need to access shared memory. Additional overhead occurs  in form of cache **coherent** i.e data in processor cache , shared memory and disk must be synchronised.

2.  **Shared Disk**

    -   In shared disk all processor can access database (disks) via interconnection network and each processor has it’s own private memories.

    -   **Advantage**

        -   Since each processor has it’s own memory , the memory bus is not bottleneck.

        -   #### Fault Tolerance

            -   High degree of fault tolerance in case of a processor fails the it’s easy for other processor to take over it’s task since the database is resident on the disk which is shared by all.

    -   **Disadvantage**
        -   **Scalability issues**
            -   Now the bottle neck issues arises due to **interconnection** ,  multiple access to the shared disk as each disk needs to copy data from disk to it’s own memory which unlike in shared memory might be already present in the shared memory.
            -   The **interconnection** result’s in bottleneck unlike memory bus.

    3.  **Shared Nothing**

        -   Each node of the machine consists of a processor, memory, and one or more disks. 

        -   The processors at one node may communicate with another processor at another node by a high-speed interconnection network.

        -   A node functions as the server for the data on the disk or disks that the node owns.

        -   Since local disk reference are serviced by the local disk at the processor the shared nothing model overcome bottlenecks as the traffic now not has to go through a single disk.

        -   All the queries which require access to non local disk is done via interconnection network.

        -   #### Advantage

            -   More scalable and more no of processor can be attached without worrying about bottlenecks.  

        -   #### Disadvantage

            -   Cost of communication for non local disk access is very high as compared to shared memory or disk  since sending the data requires software interaction from both the ends.

    4.  **Hierarchical **
        -   It is the combination of shared nothing , memory , disks .
        -   At the top level the system consists of nodes that are interconnected and do not share anything (**share nothing**) .
        -   Each node in the system could either be shared disk or memory .

### Distributed Database System

-   The database is stored on several computers which communicate with each other via private network or Internet .
-   The computers in  the distributed database can be different from one another i.e workstation or mainframe and they **do not share memory or disk**.
-   The computers in distributed database is called as **nodes** or **sites** where sites refer to system separated geographically from one another. 
-   The main difference **between** share nothing parallel database and distributed database is that the computers can be located geographically with sometimes slower interconnection.
-   Types of transaction
    1.  A **local transaction** is one that accesses data only from sites where the transaction was initiated.
    2.   A **global transaction**, on the other hand, is one that either accesses data in a site different from the one at which the transaction was initiated, or accesses data in several different sites.
        -   Each site has it’s **own local transaction manager** whose function is to ensure the ACID properties of those transactions that execute at that site.
        -   The **transaction coordinator** coordinates the execution of the various transactions (both local and global) initiated at that site.

-   #### Advantage

    -   **Sharing Data**
        -   Different campus of a college can access each other data without copying the data from other campus server to their local server. 

    -   **Autonomy**
        -   Certain restriction might be imposed to keep the data at the origin or country such as financial data ..etc

    -   **Availability**
        -   Data can be replicated and distributed nature allows to recover system if one of the site fails.

-   **Disadvantage**

    -   #### Implementation issues

        -   If a transaction runs across two sites , then  unless the system designers is careful , it may **commit** at one site while **abort** at other leaving the database in inconsistent state. 
        -   To prevent this **transaction commit protocol** are implemented in distributed database system.
        -   The 2 phase commit protocol (2 PC) is most widely used.

    -   **Concurrency control**
    
-   Since transaction may need to access data which can be present on different sites , transaction manager may need to co-ordinate several sites.
        
    -   **Deadlock**
        
        -   Deadlock can occur so deadlock detection has to be implemented on several sites.

### Parallel Database

-   **I/O parallelism**
    -   It refers to reducing the time required to retrieve the relation by partitioning the relations over multiple disks.
    -   The Most common form of partitioning is called as **horizontal partitioning**
        -   **Horizontal Partitioning**
            -   The tuples of the relations are divided among many disk so that each tuple reside on different disk.

### Types of Distributed System 

1.  **Homogeneous Distributed System **
    -   All the sites have **identical** database management software , are aware of one another and agree to co-operate in processing user request.
    -   In such system the  local system surrender the portion of their **autonomy** in terms of **right** to change the database schema or DBMS software. 

2.  **Heterogeneous Distributed System **
    -   Different sites may use **different** schemas, and different database-management system software. 
    -   The sites may not be aware of one another, and they may provide only limited facilities for cooperation in transaction processing. 
    -   The differences in schemas are often a major problem for query processing, while the divergence in software becomes a hindrance for processing transactions that access multiple sites.

### Distributed Data Storage

-   There are two ways in storing a **relation r** in a distributed database

    1.  **Replication**

        -    The system stores several copies of the relation and stores each copies in a different site.

        -   In extreme case all the sites in a database contain the replication of data.

        -   Advantage 

            -   **Availability**
                -   If one site containing the relation fails then the relation can be found on other sites . 

            -   **Increased Parallelism**
                -   As majority of transaction involve relation *r* are read only thus several site can run parallel transaction involving relation r .
                -   The more replicas are present , the greater chance that the needed data can be found in the site where transaction is executing.

        -   **Disadvantage**
            -   **Increased Overhead on update**
                -   The system must ensure that all the replicas of the relations r are consistent whenever r is updated i.e the update must be propagated to all the sites containing the replica. 

    2.  **Fragmentation**

        -   The system partition the relation into several fragments and store each fragment on different sites .
        -   If relation r is fragmented, r is divided into a number of fragments r 1 , r 2 , . . . , r n .
        -   These fragments contain sufficient information to allow reconstruction of the original relation r.
        -   There are two different schemes for fragmenting a relation:
            -   **horizontal** fragmentation 
                -   splits the relation by assigning each tuple of r to one or more fragments.
            -   **vertical** fragmentation.
                -   fragmentation splits the relation by decomposing the scheme R of relation r
            -   **Mixed** fragmentation
                -   Uses both horizontal and vertical fragmentation further the data can replicated and the replicas of fragments can be fragmented further.

### Commit Protocols

-   In order to ensure atomicity all the sites where the transaction T is executing should be committed or aborted i.e all or none.
-   To ensure this property  the transaction coordinator **of T **must execute commit protocol.  

Consider a transaction **T** initiated at site S , where the **transaction** **coordinator** is **C** .

#### Two Phase Commit Protocol (2PC )

-   When all the sites have completed the execution of transaction T informs the transaction coordinator C to start 2PC protocol.
-   Phase 1
    -   C adds **\<prepare T\>** record into the log and also send this message to all the sites where transaction T was executed.
    -   On receiving such a message, the transaction manager at that site determines whether it is willing to commit its portion of T. If the answer is **no**, it adds a record **\<no T\>** to the log,and then responds by sending an  **\<abort T\>** message to C . 
    -   If the answer is **yes**, it adds a record **\<ready T\>** to the log,and forces the log onto stable storage. The transaction manager then replies with a  \<**ready T**\> message to C  .

-   Phase 2 
    -   When the transaction coordinator C receives  **\<ready T\>** from all the sites that are involved in the transaction then it will write  **\<commit T \>** message to the log and also sends this message to all the participating sites.
    -   If at least one of the participating device does sends **abort** message then the transaction is aborted by writing  **\<abort T \>**  message into log and sending it to all participating sites.
-   Since the coordinator site is also a participating it itself can **unilaterally** decide to abort the transaction. 
    
-   At the end of the second phase the sites send  **\<acknowledge \>**  message to the coordinator , on receiving all the acknowledgements  the coordinator then adds  **\<complete T \>** record to the log. 

-   In Two phase commit you have **consistency** but at the **risk** of the most recent data not being available for a certain period of time . While the two phase commit is executing other queries to **the data are blocked** . The updated data is unavailable until the two phase commit complete .
-   **This favours consistency over availability . **



#### Failure of Coordinator - BLOCKING PROBLEM

-   When the coordinating sites fails in the midst of the execution of **commit** protocol for transaction T the it’s up to the participating sites to decide the fate of  T. 
-   Three Cases
    1.  If the active sites contain **\<commit T\>** record in it’s log then the T must  be committed.
    2.  If the active sites contain **\<abort T\>** record in it’s log then the T must  be aborted.
    3.  If all the sites contains only  **\<ready T\>**  and no additional control records ( i.e commit , abort ..) . 
        -   Since the coordinator has failed there is no way to decide whether a decision have been made or not until the coordinator recovers ( **as T can be also aborted unilaterally by the coordinator **) .
        -   Thus the active sites must have to hold the system resources i.e locking on data . Such a situation is undesirable, because it may be hours or days before C is again active. 
        -   During this time, other transactions may be forced to wait for T. As a result, data items may be unavailable not only on the failed site (C ), but on active sites as well. 
        -   This situation is called the **blocking problem**, because T is blocked pending the recovery of site C .	

### Three Phase Commit

-   It is an extension of two phase protocol and is used to overcome the blocking problem.
-   Under these assumptions, the protocol avoids blocking by introducing an extra third phase where **multiple sites are involved in the decision** to commit.
-   Instead of directly noting the commit decision in its persistent storage, the coordinator first ensures that at least **k other sites** know that it intended to commit the transaction.
-    If the coordinator fails, the remaining sites first **select a new coordinator**. This new coordinator checks the status of the protocol from the remaining sites; if the coordinator had decided to commit, at least one of the other k sites that it informed will be up and will ensure that the commit decision is respected. 
-   The new coordinator **restarts** the third phase of the protocol if some site knew that the old coordinator intended to commit the transaction. Otherwise the new coordinator aborts the transaction.

### Concurrency Control In Distributed Database

-   To ensure that all the replicas of the data present in remote sites must be coherent and all must be updated simultaneously.

-   #### Locking Protocol

    -   The existence of the **shared** and **exclusive** lock modes.  

-   **Single Lock Manager Approach**

    -   In the single lock-manager approach, the system maintains a **single** lock manager
        that resides in a **single** chosen site —say S.
    -   **All lock and unlock requests are made at site S.**
    -   The lock manager determines whether the lock can be granted immediately. If the lock can be granted, the lock manager sends a message to that  site. Otherwise, the request is **delayed** until it can be granted. 
    -   The transaction can read the data item from any one of the sites at which a replica of the data item resides. In the case of a write, **all the sites where a replica of the data item resides must be involved in the writing.**

    -   **Advantage**
        -   **Simple Implementation**
        -   **Simple Deadlock Handling**
            -   As lock and unlock request are send to one site the algorithm can be implemented easily.

    -   **Disadvantage**

        -   **Bottleneck**
            -   Since all the request are send to a single site which may overwhelm by multiple request. 

        -   **Vulnerability**
            -   If the Lock manager site fails then the concurrency control is lost.

-   **Distributed Lock Manager**

    -   Each site maintains a **local lock manager** whose function is to administer the lock and unlock requests for those data items that are stored in that site. 
    -   When a transaction wishes to lock a data item Q that is **not replicated** and resides at site S , a message is sent to the lock manager at site S requesting a lock (in a particular lock mode). 
    -   If data item Q is locked in an incompatible mode, then the request is delayed until it can be granted. 
    -   Once it has determined that the lock request can be granted, the lock manager sends a message back to the initiator indicating that it has granted the lock request.
    -   **Advantage**
        -   Reduces Bottleneck

    -   **Disadvantage**
        -   Complex deadlock handling
        -   