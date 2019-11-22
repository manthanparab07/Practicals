>   #### Transactions

-   Collections of operations that form a single logical unit of work are called **transactions**.
-   It is the responsibility of the DBMS to ensure that even in case of Failure either the entire transaction executes or none of it does.
-   The transaction consists of all operations executed between the **begin** transaction and **end** transaction.
-   This collection of steps must appear to the user as a single, indivisible unit.
-   Since a transaction is indivisible, it either executes in its entirety or not at all.



 **ACID**  Properties of DATABASE

-   **Atomicity** 
    -   Since a transaction is indivisible, it either executes in its entirety or not at all.
    -   Even if the transaction fails due to logical or other reasons the system must be able to undo all the changes made by the transaction to return the database in original state.
    -   This '**all or none**'   property is referred as atomicity.
-   **Isolation**
    -   As transactions are also group of SQL statements thus its actions cannot be separated by other executing SQL statements that may or may not be part of other transaction.
    -   Thus to ensure that the other SQL statement do not affect the execution of the transaction. 
    -   The database system must take special actions to ensure that transactions operate properly without interference from concurrently executing database statements.
-   **Durability**
    -   Even if the system ensures correct execution of a transaction, this serves little purpose if the system subsequently crashes and, as a result, the system “**forgets**” about the transaction. 
    -   Thus, a transaction’s actions must persist across crashes.
    -   This property is referred to as **durability**.
-   **Consistency**
    -   If a transaction is run atomically in isolation starting from a consistent database, the database must again be consistent at the end of the transaction.
    -   The consistency requirement goes beyond the data integrity constraints like (Primary Key ... ) but also ensures consistency across application level integrity.

Ex. Transfer of Money From A to B

-   Consistency is maintained only when the sum of money before and after transaction is same.
-   Atomicity sum (A+B) must be preserved.
-   Care Should be taken so that Money should not be created or destroyed in transaction . 



**Terms**

-   **Aborted** transaction : When a transaction does not completes its execution due to failure.

-   **Rollback** : All the changes made by aborted transaction must be undone to bring the database in consistent state.

-   **Committed**   transaction is the transaction which has successfully completed it's execution.

-   **Compensating** transaction 

    -   Once a transaction is successfully completed it cannot be undone.
    -   The only way to undo changes made by transaction is by executing another transaction known as **compensating** transaction.
    -   It's not always possible to create compensating transaction.

    

**Transaction Model**

-   **Active**, the initial state; the transaction stays in this state while it is executing.
-   **Partially committed**, after the final statement has been executed.
-   **Failed**, after the discovery that normal execution can no longer proceed.
-   **Aborted**, after the transaction has been rolled back and the database has been restored to its state prior to the start of the transaction.
-   **Committed**, after successful completion. 

#### A Transaction is said to be terminated if it either entered into committed or aborted state.

 

-   After the system enters into **aborted** state either due to hardware or logical error it has two option :
    1.  **restart** the transaction in case of hardware or software failure but not due to internal logic error of transaction . New Transaction is created i.e restarted.
    2.  **kill** the transaction in case error occurred due to internal logic of transaction.



#### **Transaction Isolation**

-   Allowing multiple transaction to execute simultaneously results in :
    1.  **Improved Throughput and Resource Utilisation ** 
        -   As Some transaction require I/O activity while other CPU or disk . 
        -   Allowing transaction to run concurrent result in the CPU , disk to spend less time idle and increasing throughput of the system.
    2.  **Reduce Wait Times**
        -   As concurrent transaction complete faster than their **serial** counterpart 
        -   Due to shared CPU cycles and disk utilisation ,  the **average response time ** reduces resulting in faster performance.

**When several transaction are executed concurrently then their isolation property may be violated resulting in database consistency being destroyed despite the correctness of each individual transaction.    **

-   This happens when two or more transaction operate on same data item.
-   To prevent this there are several **concurrency control schemes ** .

### Concurrency Control Component of DBMS

-   Without concurrent execution , the order in which the transaction happens is called as **serial sequence**.
-   In concurrent execution some transaction might get executed before other depending on the **schedule sequence** as CPU is **time shared ** with different transaction known as **context switching**.
-   Instructions from transaction are said to be **interleaved** when the CPU executes in concurrently.
-   The **schedule sequence** can be **n!** possible ways to schedule different transaction.
-   Not all sequence results the database to enter into **consistent states**.
-   If control of concurrent execution is left entirely to the operating system, many possible schedules, including ones that leave the database in an inconsistent state.
-    It is the job of the database system to ensure that any schedule that is  executed will leave the database in a consistent state. The **concurrency-control component** of  the database system carries out this task.

### Serializable Schedule

-   The schedule sequence that is equivalent to serial schedule ( i.e without concurrent execution ) and leaves the database in consistent state after execution.
-   When two or more transaction operate on different data item then the instructions of them can be swapped without worrying about the inconsistency.

#### Conflict Serializability

-   When two transactions operate on same data then four cases are possible :
    1.  Both perform **read** operation on data , then sequence does not matter and thus they can be swapped.
    2.  But in other cases the sequence does matter . ( i.e RW , WR  , WW )

-   Two transaction is said to be in **conflict** if 
    1.  They both operate on **same** data item.
    2.  At-least one of them is a **write** operation.

-   If two instruction from different transaction do not **conflict** then we can swap these instructions  for concurrency and these instructions are known as **non-conflicting** instructions.

#### Conflict Equivalent

-    If a schedule **S** can be converted into another schedule **S'** by swapping **non-conflicting** instructions then **S - S'** are said to be **Conflict Equivalent**.
-   Both Schedule should give the same **final** state .

#### Conflict Serializable

-   When schedule **S** is **conflict equivalent** to **serial schedule **.

-   To find out whether an schedule is **conflict Serializable**  we use **precedence graph** .
-   If the graph does **not** form cycle/**loop** then schedule is conflict Serializable.
-   **Ti --> Tj**  edge from i to j indicating transaction **i** perform read/write **before** transaction **j** on same data item.

#### Recoverable Schedule 

-   In schedule ***S*** , if transaction-**I reads** a data for item that other transaction-***J*** has **written** in this case the  transaction ***i*** is dependent on ***j***  because if **J** is aborted then the transaction **I** must also be rolled back since it contains inconsistent value which was written by **J**. 

-   Schedule **S** is said to be **recoverable schedule**  only if transaction **J** commits before transaction **I**.
-   Because if for some reason **I commits**   before **J** , **J** aborts but  **I** cannot be rolled back since the transaction has completed and cannot be undone this results in database to enter into inconsistent state . This schedule **S**  is called as **non recoverable schedule** as the dependent transaction cannot be undone.

#### Cascading rollback

-   In **Recoverable Schedule**, when more than one transaction depends upon the first transaction ( i.e ***written data***) in chain format i.e **A <- B <- C <- ..** then in case when **A** fails several transactions must be rolled back. 
-   This phenomenon, in which a single transaction failure leads to a series of transaction
    rollbacks, is called **cascading rollback**. 

#### Cascadless Schedule

-   In **Recoverable Schedule**, when more than one transaction depends upon the first transaction ( i.e ***written data***) in chain format i.e **A <- B <- C <- ..** then in this case **B** is allowed to read data written by **A** only when A commits the transaction and so on .

#### Transaction Isolation Levels

-   Serializability ensures that transactions are executed concurrently but in order to ensure that the database remains consistent ( consistency ) after the end of transaction we add isolation levels . 
-   Different Isolation Levels :
    1.  **Serializable** ensures Serializable execution.
    2.  **Repeatable read**  Only allows committed data to be read and further requires that, between two reads of a data item by a transaction, no other transaction is allowed to update it.
    3.  **read committed** Allows read on committed data but does not require repeatable read i.e other transaction can update the data item between two reads by a transaction.
    4.  **read uncommitted** Allows read to both committed and uncommitted data. Lowest Isolation level.

-   Additionally all isolation level disallow **Dirty Writes** i.e disallow writes to the data item that has already been written by other transaction that has not yet committed or aborted.

#### Concurrency control policy

-   Ensures that the DBMS produces valid Schedule which leaves the database in consistent state.

-   Several Policy is devised to ensure consistency during executing Multiple transaction.

    1.   **Locking** 
        -   Instead of locking the entire database, a transaction could, instead, lock only those data items that it accesses. 
        -   Under such a policy, the transaction must hold locks long  enough to ensure serializability, but for a period short enough not to harm performance excessively.
        -   Ex. Two Phase Locking , Shared Lock , Exclusive Lock ..

    2.  **Timestamps**
        -   For **isolation policy **  each transaction is assigned a timestamp when it begin.
        -   For each data item the system keeps two timestamp, one for read and write.
        -   Read timestamp of a data item holds the timestamp of transaction that most recently read the data similarly for write timestamp.
        -   Timestamps are used to ensure that transactions access each data item **in order** of the  transactions’ timestamps if their accesses conflict. 
        -   When this is not possible,  offending transactions are aborted and restarted with a new timestamp.

    3.  **Multiple Version and Snapshot Isolation**
        -   In snapshot isolation, each transaction is given its own version, or snapshot, of the database when it begins.
        -   As a result it remains isolated from changes made by other transaction .
        -   If the transaction updates the database, that update appears only in its own version, not in the actual database itself.
        -   Updates are  applied to database only when the transaction commits.
        -   When a transaction T enters the partially committed state, it then proceeds to the committed state only if no other concurrent transaction has modified data that T intends to update. Transactions that, as a result, cannot commit abort instead. 

#### Lock Based Control (LOCKING)

-   The transaction operate  in a mutually exclusive manner i.e when one transaction access data no other transaction is allowed to modify that data item.

-   This is implemented using **lock** on that item.

-   Types of Locks

    -   **Shared Locks(S)** 
        -   Transaction that acquires Shared Lock to a data item can only read it.

    -   **Exclusive Locks(X)**
        -   Both read and writes.

-   The **Concurrency Control Manager** is responsible for granting locks to the transaction and **multiple** shared Locks can be granted for a **single data item**  but only one Exclusive lock is granted at a time.

-   If a transaction is currently holding a lock on data item then if other transaction request lock which is incompatible with the current lock then they have to wait till the current transaction releases the lock.

-   Moreover a transaction will not immediately release the lock after use to ensure serializability.

-   Ex. Transfer of Money from A -> B and Sum of Money Transaction executed concurrently.

-   To ensure serializability transaction releases locks at the end .

-   #### Deadlocks

    -     When two transaction request for lock on data **items** that is already been granted and neither of the transaction can proceed with its normal execution .
    -   To overcome deadlocks , the System must step in and must roll back one of the two transaction. 

-   So releasing too early or late might result in inconsistent state or deadlocks. To overcome this **locking protocols **  are used which indicate when to lock or unlock each data item.

-   Schedule **S**  is said to be **legal** under a given locking protocol if and only locking protocol ensures conflict serializability and does not form **cycles** in  associated->relation graph.

-   #### Starving 

    -   If a transaction is granted a lock on data item and another transaction request a lock which is incompatible to current lock then it must wait for the current lock to release.
    -   If another transaction request the lock which is compatible to current lock the it is granted the lock resulting in the incompatible request to wait for this new transaction to release.
    -   If this continues and many transactions request then the incompatible transaction gets starved as it has to wait indefinitely for acquiring the lock.  

### Two Phase Locking Protocol

-   In this protocol **each** transaction must issue  lock or unlock request in two phases :

    1.  **Growing Phase **
        -   A transaction may obtain new locks but cannot release any locks.

    2.  **Shrinking Phase**
        -   A transaction may release locks but cannot request/acquire any new locks.

-   Initially, a transaction is in the growing phase. The transaction acquires locks as needed.

-    Once the transaction releases a lock, it enters the shrinking phase, and it can issue no more lock requests.

-   The **Shrinking Phase** i.e releasing of lock is not necessarily to appear at the end of the transaction.

-   #### Lock Point 

    -   The Point in the schedule when the transaction acquires the last lock i.e at the end of the growing phase is termed as **lock point of the transaction**. 

-   Normal Two Phase locking does **not** remove **Deadlock , Cascading Rollback **, these condition can occur.

-   In order to avoid deadlocks and cascading rollbacks Protocol can be modified to meet the requirements

    -   #### Strict Two Phase locking

        -   This protocol requires not only that locking be two phase, but also that all **exclusive- mode** locks taken by a transaction be held until that transaction commits.
        -   This ensures that changes made by the transaction is not read by another transaction thus preventing cascading rollback and deadlocks.

    -   #### Rigorous Two Phase Locking

        -   This Protocol requires all the locks to be held until the transaction commits.
        -   This results in **serial** execution of transaction that work on same data.

-   #### Lock Conversion

    -   Since the transaction may need to write back the data only once , thus holding an exclusive lock might result in lower concurrency and reduce throughput.
    -   Lock Conversion can be employed in this case by providing shared locks to the transactions and the converting this shared locks into exclusive locks through lock conversions whenever the transaction requires to write the data back.
    -   This allows multiple transaction to access to the data item without reducing throughput and avoiding deadlocks and cascading rollback.
    -   Conversion Term
        -   Shared to Exclusive : **Upgrade**
        -   Exclusive to Shared : **Downgrade**

    -   Moreover upgrading and downgrading can happen only during growing and shrinking phase respectively.
    -   A transaction attempting to upgrade a lock on an item Q may be forced to wait if the data item is in shared mode by other transaction.

### Deadlock Handling

-   A system is said to be in deadlock if there is a set of transaction such that each transaction is waiting for another transaction in the set.

-   As a result of which none of the transaction can proceed .

-   To resolve the deadlock it can be done in two ways

    -   **Partial Rollback** 
        -   Rollback to the point where the transaction acquired the lock and release it . 

    -   **Complete Rollback**

-   Two Ways to deal Deadlock Problem

    -   #### Deadlock Prevention

    -   #### Deadlock Detection and recovery

### Deadlock Prevention

-   Two approaches

    1.  No Cyclic waits can occurs by requiring all locks to acquired together before execution.

        -   All are locked in one step or none are locked.
        -   Disadvantage
            1.  Difficult to predict what items needed to be locked before execution
            2.  Utilisation can be low as many of them may be unused for a long time during execution. 

    2.  Perform transaction rollback instead of waiting for a lock.

        -   Uses Preemption and transaction rollbacks 

        -   Timestamp is assigned to each transaction and it is used by system to determine whether the transaction should wait or roll back.

        -   Preemption is used to rollback when one transaction request data that is locked by another.

        -   Schemes

            1.  #### Wait and Die

                -   Non preemptive technique
                -   When a transaction A request a data item that is currently held by transaction B then A is allowed to **wait** if it's timestamp is **smaller** than B (i.e A is **older** than B) else it is rolled back(**die**).

            2.  #### Wound and Wait

                -   Opposite to Wait and die
                -   Newer transaction are allowed to wait while older one are rolled back.

            3.  #### Lock Timeout

                -   The above two scheme results in unnecessary rollback.
                -   When a transaction request a lock the it waits for a specific period of time .
                -   Once this time expires the it rollbacks and restarts.
                -   Starvation is possible in this scheme. 

### Deadlock Detection and Recovery

-   Employs an algorithm that regularly checks whether an deadlock has occurred .

-   #### Deadlock Detection 

    -   Uses  **Wait for graph ** which has edges based on **Ti** ---> **Tj**  i.e Ti is waiting for Tj to release a data item that it needs.
    -   The algorithm periodically searches for cycles which indicates deadlock in the system.

-   #### Deadlock Recovery

    -   Selection of a victim
        -   A transaction is choose based on several factor which will ensure the system should perform less work for restarting is chosen and rolled back.

    -   Rollback ( either Total or partial )
    -   Starvation 
        -   If the same transaction is selected for rollback multiple times the it might led to starvation.
        -   To prevent this we must ensure one is chosen finite no of times.

### VIEW SERIALIZABILITY

-   It is based on only the read and write operations of transactions.
-   Consider two schedules S and S  , where the same set of transactions participates in both schedules. The schedules S and S  are said to be view equivalent
-   if three conditions are met:
    1. For each data item Q, if transaction T i reads the initial value of Q in schedule S,then transaction T i must, in schedule S  , also read the initial value of Q.
    2. For each data item Q, if transaction T i executes read(Q) in schedule S, and if that value was produced by a write(Q) operation executed by transaction T j , then the read(Q) operation of transaction T i must, in schedule S  , also read the value of Q that was produced by the same write(Q) operation of transaction T j .
    3. For each data item Q, the transaction (if any) that performs the final write(Q) operation in schedule S must perform the final write(Q) operation in schedule S  .
-   Conditions 1 and 2 ensure that each transaction reads the same values in both schedules and, therefore, performs the same computation. 
-   Condition 3, coupled with conditions 1 and 2, ensures that both schedules result in the same final system state.
-   a schedule S is view serializable if it is view equivalent to a serial schedule.
-   Every conflict-serializable schedule is also view serializable, but there are view-serializable schedules that are not conflict serializable.

### Recovery System

-   Employed to restore the database after a failure .

-   Types of Failure

    1.  **Transaction Failure**

        -   Two ways in which a transaction fails to proceed

            1.  **Logical Error**
                -   Internal Logic of transaction results in Error 
                -   Ex Bad input , data not found , error .. etc.

            2.  **System Error**
                -   The system enters into a undesirable state after which it cannot continue its normal execution.
                -   Ex. Deadlocks 

    2.  **System Crash**
        -   Ex. Hardware or software bug , system crash ..etc

    3.  **Disk Failure**

### Log Based Recovery

-   **Log record** records all the update activities in the database. 

-   Al log record has following fields

    1.  **Transaction identifier **
        -   A unique identifier of the transaction that performed write operation.

    2.  **Data item identifier**
        -    A unique identifier of the data item written. Generally the location of the data item in memory.

    3.  **Old Value**
    4.  **New Value**

-   We represent an **update log record** as < Ti , Xi , V1 , V2 > i.e transaction Ti performed **write** operation on data item identified by Xi with new value V2 .

-   Other **log record** records significant event during transaction such as start ,  commit , abort .
    -   **\<Ti start\>**
    -   **\<Ti commit\>**
    -   **\<Ti abort\>**

-   #### Operation

    -   Whenever a transaction wants to performs a writes into the database then it must create a **write log record** first before the database is modified .
    -   The log record are stored into a stable storage which ensures that even in case of system failure , aborts we can perform write after system restores.
    -   It also allows to undo modifications by using old value from the log field.

### Deferred and Immediate modification

-   When a transaction performs write to the database it can either update it's own local copy and perform actual write to disk at the end of transaction being committed ( called **Deferred Modification ** ) or immediately when it performs write to the disk ( **Immediate Modification** ) .
-   Deferred modification has the overhead that transactions need to make local copies of all updated data items;further, if a transaction reads a data item that it has updated, it must read the value from its local copy.

### Checkpoint

-    When a system crash occurs, we must consult the log to determine those transactions that need to be **redone** and those that need to be **undone**. 
-   In principle, we need to search the entire log to determine this information which can be time consuming.
-   To reduce overheads we use checkpoint which
    -   does not allow any operation while the checkpoint operation is in progress.
    -   outputs all the modified buffer blocks to the disk when the checkpoint is performed.
    -   also adds a log record of type **< checkpoint L > ** where L is the list of transaction currently active at the time of the checkpoint. This allows to streamline the recovery procedure.

-   Transactions are not allowed to perform any update actions, such as writing to a buffer block or writing a log record, while a checkpoint is in progress.
-   So those transaction that has completed their commit or abort must appear before < checkpoint L >  in log record. Thus at recovery time there is no need to perform **redo** operation for this transactions.
-   In case of system crash the system examines the list of transactions that were still active by searching the log backwards i.e to find the last **< checkpoint L > ** in log record. Those transaction for which commit or abort log record is not found are **undone**. For those there exists are **redone** .

### Shadow coping and Shadow Paging

-   In the shadow-copy scheme, a transaction that wants to update the database first creates a complete copy of the database.

-    All updates are done on the **new** database copy, leaving the original copy, the **shadow copy**, untouched. 

-   If at any point the transaction has to be aborted, the system merely deletes the **new** copy.

    The old copy of the database has not been affected. 

-   The current copy of the database is identified by a pointer, called **db-pointer**, which is stored on disk.

-   So when a transaction partially commits then
    1.  The OS make sure that all pages of the new copy of the database have been written out to disk.
    2.  The database system updates the pointer **db-pointer** to point to the new copy of the database; the new copy then becomes the current copy of the database and deletes the older one.

-   Extensively used in text editor and for small databases.

-   #### Disadvantage For Copying a large database would be extremely expensive.

-   #### Shadow Paging

    -   A Page table is used which contains pointers to all the pages , the page table itself .
    -   All the updates pages are copied to the new locations .
    -   Those pages which are not updated are not copied .
    -   The new page table now stores the pointer to the original page.
        -   When the transaction commits  , it actually updates the pointers to the page table which act  as db-pointer to the new copy. 

### Query Processing

-   Range of activities involved during extraction of data from a database.
    1.  **Parsing and Translation**
    2.  **Optimisation**
    3.  **Evaluation**

-   #### Parsing and Translation

    -   As the query are represented in SQL statement which is suitable for human but cannot be understand by the database.
    -   The Task of Query processing is to first translate a given query into it's internal form i.e **relational algebra expression** 



