---
title: Database Concepts
---

1. A `DATABASE` is a collection of logically related data.

2. A `DATABASE MANAGEMENT SYSTEM` (DBMS) enables users to define, create,  maintain, and control access to the database.

3. A `DATABASE APPLICATION` is a program that interacts with the DBMS using SQL statements during its execution.

4. ##### Traditional File based System

- Each Application defines and manages its own data.
- It is a decentralized approach.

- ##### Drawbacks

	1. `Separation and isolation of data`

		- When data is isolated in different files then it becomes difficult to access data to be available.
		- Such processing with file based is difficult which may involve synchronization of different files.

	2. `Data Redundancy`

		- As it is diificult to relate data in two files thus file base system have a lot of data redundancy.
		- Increases storage cost and increases processing time.

	3. `Incompatible file formats`

		- A program written in C generated a diiferent file format than a program written in COBOL thus it results in incompatibility.
		- Thus additional file conversion may be required when using two applcation data which is time consuming.

	4. `No provision for security and integrity.`
		
	5. `Access to file is limited to one user a time.`

	6. `Recovery`, in the event of a hardware or software failure, was limited or nonexistent.

5. > ##### DATABASE MANAGEMENT SYSTEM

	-  It provides `controlled access` to the database. 
	
	- A `security` system, which prevents unauthorized users accessing the database;
	
	- An `integrity` system, which maintains the consistency of stored data;
	
	- A `concurrency` control system, which allows shared access of the  database;
	
	- A `recovery` control system, which restores the database to a previous  consistent state following a hardware or software failure;
	
	- A Control of data `redundancy`

6. > #### Structure of Database Systems
	
- A system view called the schema and user views called subschemas.
	
- It involve three level :

	1. External Level
	 - In which DBMS interacts with the user to percieve the data.
		
	2. Internal Level
	 - In which DBMS interacts with the OS to percieve the data.
	 - In involves how the data is actually stored using data structure and file organisation.

	3. Conceptual Level
	- Provides mapping and independence from exernal and internal level.

 ![da93f4b4.png](attachments/da93f4b4.png)

- Major Objective is to provide DATA INDEPENDENCE i.e the upper levels are unaffected by changes to lower levels. 

> #### Objective of 3 level architecture.

1. Each user should be able to change the way he or she views the data, and this change should not affect other users.

2. A user’s interaction with the database should be independent of storage considerations involves hashing,indexing.. etc. 

3. The DBA should be able to change the database storage structures without affecting the users’ views.
		
4. The internal structure of the database should be unaffected by changes to the physical aspects of storage, such as the changeover to a new storage device.

> #### External Level

- The users’ view of the database. This level describes the part of the database that is relevant to each user.
 
- The external level consists of a number of different external views of the database for each user.
	  
- The external view includes only those entities, attributes, and     relationships in the “real world” that the user is interested in.
	 
- Different views may have different representations of the same data.
	  
- Ex. Same date can be represented as YYYY-MM-DD or DD Month Year for different user.

> #### Conceptual Level

- The complete view of the database. This level describes what data is stored in the database and the relationships among the data.

- This level contains the logical structure of the entire database as  seen by the DBA. 

- The conceptual level represents:
		
	+ all entities, their attributes, and their relationships;
	+ the constraints on the data;
	+ semantic information about the data;
	+ security and integrity information.
	  
- The conceptual level supports each external view, in that any data  available to a user must be contained in, or derivable from, the conceptual level.

> #### Internal Level

- The physical representation of the database on the computer. 
- This level describes how the data is stored in the database.

- The internal level covers the physical implementation of the database to achieve optimal runtime performance and storage space utilization.
	  
- It covers the data structures and file organizations used to store data on storage devices.

- It involves interaction with the OS.
- Also involves data compression and data encryption techniques.

> #### Physical Level

- Physical level that may be managed by the operating system under the  direction of the DBMS.

> ##### Physical Data Independence

1. Using a new storage device like Hard Drive or Magnetic Tapes
2. Modifying the file organization technique in the Database
3. Switching to different data structures.
4. Changing the access method.
5. Modifying indexes.
6. Changes to compression techniques or hashing algorithms.
7. Change of Location of Database from say C drive to D Drive

7. Schema Mapping and Instances

- A overall description of the database is called as database schema.
- Three types

		External 	Schema
		Conceptual 	Schema
		Internal 	Schema 

- At the `highest` level, we have multiple external schemas (also called  subschemas) that correspond to different views of the data.
	
- At the `conceptual` level describes all the entities, attributes, and  relationships together with integrity constraints.
	
- At the `lowest` level of abstraction , the internal schema, which is a complete description of the internal model, containing the definitions
	of stored records, the methods of representation, the data fields,
	and the indexes and storage structures used.

- There is only one conceptual schema and one internal schema per database.

- The DBMS is responsible for mapping between these three types of schema.
- > ### `Mapping implies consistency of data.`
	
> #### Types of Mapping By DBMS

	- conceptual/internal mapping.
	- external/conceptual mapping.

- The data in the database at any particular point in time is called a database instance.

![d00a1c91.png](attachments/d00a1c91.png)

8. #### Data Definition Language ( DDL )
	
- It allows the DBA or the user to describe and name the entities,attributes along with integrity and other security constraints.

- These commands are used to define and alter the structure of database and associated tables ...etc. `It is not used to manipulate data`.

- When a DDL command is executed a set of tables is created and it is stored in a special file collectively know as system catalog.

- The `system catalog` integrates with the `metadata` which is describes the  objects in the database and contains the definition of records , data items and other objects .

- The DBMS consults with the system catalog before actual data is accessed from the database.- `Data dictionary` is used to describe the system catalog.

9.  Data Manipulation Language ( DML )
	
- A language that provides a set of operations to support the basic data manipulation operations on the data held in the database.

		> `Insertion , Modification , Deletion , Retrieval.`

- Data manipulation applies to the external, conceptual, and internal levels.

> #### Two types of DML: procedural and nonprocedural.

- The prime difference between these two data manipulation languages is that procedural languages specify HOW the output of a DML statement is to be obtained, while nonprocedural DMLs describe only WHAT output is to be obtained.

- Procedural languages treat records individually, whereas nonprocedural languages operate on sets of records.

	
10. > ##### Data Model

- Data Model are` collection of concepts` describing and manipulating data, relationship between data and constraints of data.

- It is a representation of real world object events and their associations.
- The purpose of the data model is to represent data and make data   understandable. 

- Three parts

		1. Structural 	: defines the structure of database.
		2. Manipulative : types of operations allowed on data 
		3. Set Of integrity constraints : to check if data is accurate. 

1. Object Based Data Model

	- Use concept of entity , attributes , relationship.
		
	- An entity is distinct object(person,place..) to be representated in the database. 

	- Attributes are the properties of the object.
	- Relationship is between entities.

	- Types of Models -- (SOFE)

		1. Entity Relationship Model
		2. Semantic
		3. Functional
		4. Object Oriented Model

2. Record Based Model

- The database contains a fixed format records of different types.
		
	Types 

	1. Relational			-- tables 
	2. Network 				-- records and sets multiple parent node
	3. Hierarchical			-- records and sets one parent node

- > ##### Network and Hierarchical were developed a decade before Relational and thus they are linked to traditional file base system. 
		
- In the network model, data is represented as collections of records, and  relationships are represented by sets.



11. Keys 

	
1. > #### Super Key

- Super key is a set of one or more than one KEYS that can be used to  identify a record uniquely in a table. 
- Example: Primary key, Unique key, Alternate key are a subset of Super Keys.
    
1. ##### Candidate Key

	- A Candidate Key is a set of one or more COLUMNS that can identify a record uniquely in a table. 
	- There can be multiple Candidate Keys in one table. 
	- Each Candidate Key can work as Primary Key.

    
1. ##### Primary Key

    - Primary key is a set of one or more columns of a table that uniquely identify a record in a database table.
    -  It can not accept `null, duplicate` values. 
    -  Only one Candidate Key can be Primary Key.
     
1. ##### Alternate key

    - An Alternate key is a key that can be work as a primary key.
	- Basically, it is a candidate key that currently is not a primary key.

1. ##### Composite/Compound Key
    
     - Composite Key is a combination of more than one columns of a table. 
     - It can be a Candidate key, Primary key.
     - Necessary when a single column is not identified as unique but a combination can.
    
1. ##### Unique Key

	- A unique key is a set of one or more columns of a table that uniquely identify a record in a database table. 
	- It is like Primary key but it can `accept only one null` value and it can not have duplicate values.
    
1. ##### Foreign Key

	- Foreign Key is a field in a database table that is Primary key in another table. 
	- It can accept `multiple` null, duplicate values.
	- There can be multiple Foreign keys in a table.


12. > ##### Entity 

- > #### Strong Entity
	- An entity type is referred to as being strong if its existence does not depend upon the existence of another entity type.

- > #### Weak Entity 
	- An Entity which does not have any sufficient attributes to form a primary key.


![b1d75517.png](attachments/b1d75517.png)

- Although each payment entity is distinct but payment for different loans may  share the same payment number. Thus Payment entity set does not have a primary key and it is an entity set.

- A weak entity can be converted into a strong entity by adding appropriate attributes but this appoach may lead to redundant storage of primary  key.

- It will result in redundancy in ER diagram and we lose the concept of dependency.



 13. > #### Extended ER diagram 
		1. Specialization
			- The process of maximizing the differences between members of an entity by identifying their distinguishing characteristics. 
			- Specialization is a top-down approach to defining a set of superclasses and their related subclasses.
			- We identify relation between subclass and superclass by defining their attributes.
		1. Generalization
			- The process of minimizing the differences between members of an entity by identifying their common characteristics. 
			- The process of generalization is a bottom-up approach, that results in the identification of a generalized superclass from the original entity types.
