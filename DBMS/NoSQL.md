>   ### NoSQL 

-   Four characteristics	of data management systems that are particularly important for large-scale data management tasks are
    -   **Scalability**
    -   **Cost**
    -   **Flexibility**
    -   **Availability**

-   **Scalability**
    -   It is the ability to meet the varying workloads.
    -   Ex. if there is a spike in the website traffic additional servers can be brought online to handle the additional load. Similarly when the traffic reduces , additional servers can be shut down . ( **Scale out** )
    -   It is often difficult to scale a relational database system as adding additional server need to install database management software . Additional database software can be quite expensive and complexity increases as more servers are added.
    -   Additional way is to **Scale up** i.e replacing the server with a more powerful server .

### CAP Theorem ( Consistency Availability Partitioning )

-   It states that **distributed** database cannot have consistency (C) , availability(A) and partition protection  (P) **all at the same time** .
-   **Consistency** means that the copies of data on different servers are consistent (i.e synchronous/same).
-   **Availability** means that providing the response to any query.
-   **Partition Protection **means if a network connecting different database fails , the server will still be available with the consistent data.
-   Ex.
    -    In Two phase commit you have **consistency** but at the **risk** of the most recent data not being available for a certain period of time . 
    -   While the two phase commit is executing other queries to **the data are blocked** . The updated data is unavailable until the two phase commit complete .
    -   **This favours consistency over availability . **

-   Ex. 
    -   In case of a e-commerce website , it is possible to have a backup copy of the shopping cart data that is out of sync with the primary copy.
        -   The data would be still available if the primary server failed but the data on the backup server would be **inconsistent** with the data on the primary server if the primary server failed prior to updating the backup server.  

-   #### Partition protection

    -   It deals with  situation where the servers cannot communicate with one another in the event  of a **network failure**.   
    -   **Partitioning refers to splitting of the network into group of devices that can communicate with each other from those that cannot .**
    -   If a database server running the same distributed database is partitioned by network failure then the database can still continue to respond query but at the risk of them **being inconsistent** . 
    -   Alternatively you can disable one so that only one server respond to the query i.e( **Partition Protection** ).  This would **avoid** returning inconsistent value but at the cost of **availability** to some users. 

    

### BASE Theorem - *B*asically *A*vailable , *S*oft State , *E*ventually Consistent

-   **Basically Available** means that there can be a partial failure in some parts of the distributed database system but the rest of the system could continue to function i.e out of 10 server in distributed system 2 failed then the rest 8 still works and respond to query. 
-   NoSQL database keep copies of data in the event of failure other server respond.

-   Soft state means that the data(state) of the system may change overtime even without user input.
-   Eventually Consistent 
    -   This means that there may be times when the database is in inconsistent state .
    -   For ex. 
        -   When an NoSQL database keeps multiple copies of database and the copies may not be consistent for a short period of time .
        -   This occurs when the user updates one copy of data but continue to keep older version of data.
        -   Eventually the NoSQL replication mechanism updates all the copies of data to the updated value but at the mean time the database remains inconsistent. 