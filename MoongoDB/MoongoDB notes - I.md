---
title:MongoDB
---

> ## MongoDB

> Intro
> -

- MongoDB is a document-oriented database, not a relational one. The primary reason for moving away from the relational model is to make scaling out easier.
- A document-oriented database replaces the concept of a “row” with a more flexible model, the “document.” 
- By allowing embedded documents and arrays, the document-oriented approach makes it possible to represent complex hierarchical relationships with a single record.
- There is no predefined schema i.e document keys and values are not fixed type or sizes thus making insertion and deletion easier.

> Key Features
> -----------

>  Scaling
>  --------

- Scaling a database comes down to the choice between scaling up (getting a bigger machine) or scaling out (partitioning data across more machines).
- Scaling up is often the path of least resistance, but it has drawbacks: large machines are often very expensive, and eventually a physical limit is reached where a more powerful machine cannot be purchased at any cost. 
- The alternative is to scale out: to add storage space or increase performance, buy another commodity server and add it to your cluster. This is both cheaper and more scalable; however, it is more difficult to administer a thousand machines than it is to care for one.

> - MongoDB was designed to scale out. Its document-oriented data model makes it easier for it to split up data across multiple servers.
- MongoDB automatically takes care of balancing data and load across a cluster, redistributing documents automatically and routing user requests to the correct machines.
- This allows developers to focus on programming the application, not scaling it. When a cluster need more capacity, new machines can be added and MongoDB will figure out how the existing data should be spread to them.

> Indexing
> -

MongoDB supports generic secondary indexes, allowing a variety of fast queries, and provides unique, compound, geospatial, and full-text indexing capabilities as well.

> Aggregation
> -

MongoDB supports an “aggregation pipeline” that allows you to build complex aggregations from simple pieces and allow the database to optimize it.

> Special collection types
> -

MongoDB supports time-to-live collections for data that should expire at a certain time, such as sessions. It also supports fixed-size collections, which are useful for holding recent data, such as logs.

> File storage
> -

MongoDB supports an easy-to-use protocol for storing large files and file metadata.

- Some Features such as joins and complex multirow transaction are not present due to architectural decision to allow greater scalability and efficient working in distributed system.

> Without Sacrificing Speed
> -

- MongoDB was designed to maintain high performance.
- MongoDB adds dynamic padding to documents and preallocates data files to trade extra space usage for consistent performance.
- It uses as much of RAM as it can as its cache and attempts to automatically choose the correct indexes for queries.
- Whenever possible, the database server offloads processing and logic to the client side (handled either by the drivers or by a user’s application code).

> Basic concepts of MongoDB
> -------------------------

- A *document* is the basic unit of data for MongoDB and is roughly equivalent to a row in a relational database management system (but much more expressive).
- A *collection* can be thought of as a table with a dynamic schema.
- A single instance of MongoDB can host multiple independent databases, each of which can have its own collections.
- Every document has a special key, "_id" , that is unique within a collection.
- MongoDB comes with a simple but powerful JavaScript shell, which is useful for the administration of MongoDB instances and data manipulation.

> Documents
> --------

- Documents are an ordered set of keys with associated values similar to map , hashes, dictonaries in other languages.
	- Single Key/Value Pair : { "greetings" : "Hello World!" }
	- Multi  Key/Value Pair : { "greetings" : "Hello World!" , "date" : 13 }
- The key in the documents are string and the values can be of any datatypes such as int , string , blobs.
- The Keys are string of UTF-8 type.
> - The key/Value pair in MongoDB is case sensitive and type sensitive.
- Keys cannot be duplicate and the key/value pair inside a document is ordered i.e.
	- {"x" : 1, "y" : 2} is not same as {"y" : 2, "x" : 1}

> Collections
> -----------

- A Collection is a group of documents.
- Collections have dynamic schemas i.e. the documents stored in it can have different fields and format ( variable )
	-{"greeting" : "Hello, world!"} 
	-{"foo" : 5}
	- Can be Stored in same Collection

> Why should we use more than one collection?
> -------------------------------------------

- It is much faster to get a list of collections than to extract a list of the types in a collection.
- Grouping documents of the same kind together in the same collection allows for data locality.
- We begin to impose some structure on our documents when we create indexes.
	- By putting only documents of a single type into the same collection, we can index our collections more efficiently.

> Naming
> ------

- A collection is identified by its name
- Collection name should not start with *system.*  as it is a internal prefix used for internal collections.
	> - system.users - collections contains all database's users 
	> - system.namespaces - contains all of the database's collections.
- SubCollections used for organizing collection by using . character
	> Ex : blog collection can have blog.posts and blog.authors subcollection


> Databases
> --------

- In addition of grouping documents by collection , MongoDB groups collection into databases.
- A database has its own permissions, and each database is stored in separate files on disk.
- Each application should have its own collection and MongoDB is capable of handling multiple databases in a single instance.
- Database reserved names
	> - admin - It is the "root" database in terms of authentication and the users that are added into it automatically inherit permission for all databases.
	> - local - This database is never replicated and can be used to store any collections that should be local to any given server.
	> - config - contains MongoDB setup and configuration files. 

> MongoDB Shell
> ----

- It is a JavaScript Shell used for interacting MongoDB database using command line.
- We can also use all JavaScript libraries and features.

- to connect to remote mongoDB 
Syntax

	mongo some-host:30000/myDB

This will connect to myDB present in some-host using port 30000

- Sometimes it is handy to not connect to a mongod at all when starting the mongo shell. 
- 
If you start the shell with --nodb , it will start up without attempting to connect to
anything:

	mongo --nodb

Then you can manually connect to different database or servers at same time.
	
	> conn = new Mongo("some-host:30000")
	  connection to some-host:30000
	> db = conn.getDB("myDB")
	  myDB

> Commands 
> ----

- To see the database db is currently assigned to :
- As the shell is a JavaScript engine the db is an variable and all its collections and documents are accessed through it. 
	> \> db 			-- local | emp .. etc
- Selecting database to use
 	> \> use database_name

> Basic Operations with the Shell
> ----
> 
There four basic operation Create, Read, Update, Delete ( CRUD ) to manipulate and view the data in shell.

> Create
- The insert function adds a document to a collection.
	> \> usr_data = post = {"title" : "My Blog Post", "date" : new Date() }
	> \> db.collection_name.insert( usr_data )
- The Object Stored in variable is inserted into collection using insert method.

> Read
- To read all the document in a collection we use find method
- Syntax : 
	> \> db.collection_name.find()
	> \> db.collection_name.findOne() 	//fetches only one document from the collection

> Update

To modify the document we use update method which takes two argument :

	- the first is the criteria to find which document to update,
	- the second is the new document.

Ex

	- change the variable to suite to updated document
		> usr_data.address = []		
		> // adds address array in the document
		> db.collection_name.update({"name":"Saurabh"},usr_data)

 - Adds an address field to document where name = "Saurabh"
 
 > Delete
 
- "remove" permanently deletes documents from the database. Called with no parameters, it removes all documents from a collection. It can also take a document specifying criteria for removal.

	- \> db.collection_name.remove() 		
	- // remove all documents from the collection
	- \> db.collection_name.remove({}) 		
	- // remove all documents from the collection
	- \> db.collection_name.remove( { "name" : "Saurabh"} )


> Datatypes in MongoDB
> ---

- They can be considered as JSON like as they are conceptually similarly to JavaScript.
- JSON - null, boolean, string, numeric , array and objects.
- Additional Datatypes are added such as date , regular expressions.


> null

Null can be used to represent both a null value and a nonexistent field:

	{"x" : null}
	

> boolean

There is a boolean type, which can be used for the values true and false :

	{"x" : true}

> number

The shell defaults to using 64-bit floating point numbers. Thus, these numbers look

“normal” in the shell:

	{"x" : 3.14}
	or:
	{"x" : 3}
	
For integers, use the NumberInt or NumberLong classes, which represent 4-byte or 8-byte signed integers, respectively.

	{"x" : NumberInt("3")}
	{"x" : NumberLong("3")}

> string

Any string of UTF-8 characters can be represented using the string type:

	{"x" : "foobar"}

> date

Dates are stored as milliseconds since the epoch. The time zone is not stored:

	{"x" : new Date()}

> regular expression

Queries can use regular expressions using JavaScript’s regular expression syntax:

	{"x" : /foobar/i}

> array

Sets or lists of values can be represented as arrays:

	{"x" : ["a", "b", "c" , "Hello World" , 10 , 3.14 ]}

> embedded document

- Documents can contain entire documents embedded as values in a parent.

Ex

	document: {"x" : {"foo" : "bar"}}

> object id 

An object id is a 12-byte ID for documents.

> binary data

Binary data is a string of arbitrary bytes. It cannot be manipulated from the shell.
Binary data is the only way to save non-UTF-8 strings to the database.

> code

Queries and documents can also contain arbitrary JavaScript code:

	{"x" : function() { /* ... */ }}

> _id and ObjectIds
> -------

The "\_id" key’s value can be any type, but it defaults to an ObjectId . In a single collection, every document must have a unique value for "\_id" , which ensures that every document in a collection can be uniquely identified.

> ObjectIds
> ----

- MongoDB’s distributed nature is the main reason why it uses ObjectId s as opposed to something more traditional, like an autoincrementing primary key: it is difficult and time-consuming to synchronize autoincrementing primary keys across multiple servers.
- ObjectId s use 12 bytes of storage, which gives them a string representation that is 24 hexadecimal digits: 2 digits for each byte.

- If you create multiple new ObjectId s in rapid succession, you can see that only the last few digits change each time.
- In addition, a couple of digits in the middle of the Objec tId will change (if you space the creations out by a couple of seconds). This is because of the manner in which ObjectId s are created.
- Format of ObjectId
>  Byte Sequence : 0 1 2 3 4 5 6 7 8 9 10 11 
	> - Timestamp (0-3)
	> - Machine(4-6)
	> - PID(7-8)
	> - Increment(9-11)

> These first nine bytes of an ObjectId guarantee its uniqueness across machines and processes for a single second.
> The last 3 byte allows for up to 256^3 (16,777,216) unique ObjectId's to be generated per process in a single second.


> JavaScript equivalents to shell helpers 

Helper Equivalent

	* use foo			- db.getSisterDB("foo")
	* show dbs 			- db.getMongo().getDBs()
	* show collections 	- db.getCollectionNames()

>  Remove Speed
>  -----

- Removing documents is usually a fairly quick operation, but if you want to clear an entire collection, it is faster to drop it (and then recreate any indexes on the empty collection).

> Syntax 

	> db.collection_name.remove({}) 
	> // time taken depends on no of documents
	> db.collection_name.drop() 	
	> // time taken is constant 

- This is obviously a vast improvement, but it comes at the expense of granularity: we cannot specify any criteria. The whole collection is dropped, and all of its metadata is deleted.

> Updating Documents
> ------

- Once a document is stored in the database, it can be changed using the update method. update takes two parameters: a query document, which locates documents to update, and a modifier document, which describes the changes to make to the documents found. 
- Updating a document is atomic: if two updates happen at the same time, whichever one reaches the server first will be applied, and then the next one will be applied.

- Thus, conflicting updates can safely be sent in rapid-fire succession without any documents being corrupted: the last update will “win.”

> Document Replacement

- The simplest type of update fully replaces a matching document with a new one.

Ex : 

	> var joe = db.users.findOne({"name" : "joe"});
	> joe.relationships={"friends":joe.friends,"enemies":joe.enemies};
	> joe.username = joe.name; "joe"
	> delete joe.friends;
	> delete joe.enemies;
	> delete joe.name;
	> db.users.update({"name" : "joe"}, joe);

> update command will only replace the first document matching the criteria specified in the command.

> ##### A common mistake is matching more than one document with the criteria and then creating a duplicate "_id" value with the second parameter. The database will throw an error for this, and no documents will be updated.

- As the list from find and all other operation is sorted based on timestamp and the search criteria in case of collision.

Ex 

	> db.people.find()
	 {"_id" : ObjectId("..."), "name" : "joe", "age" : 65},
	 {"_id" : ObjectId("..."), "name" : "joe", "age" : 20},
	 {"_id" : ObjectId("..."), "name" : "joe", "age" : 49},

	> myVar = db.people.find({"name":"joe","age":20})
	> myVar.age = 100
	> db.people.update({"name":"joe"},myVar)
	> Error : After applying the update, the (immutable) field '_id' was found 
	  to have been altered to _id

- Error arises because the myVar contains document of joe of age 20 and its document_id so when the update command runs and try to replace the first document found i.e joe with age 65 it encounters the duplicate object id and thus the operation is aborted.

> To avoid conflicting situation , we can either specify object id of document or the search criteria query must be more specific

> Using Modifiers
> ----

- Modifiers are used to update a part of document instead of replacing it with new one.
- Update modifiers are special keys that can be used to specify complex update operations, such as altering, adding, or removing keys, and even manipulating arrays and embedded documents.
	> Always use $ operators for modifying individual key/value pairs else it will act as entire document replacement.

Ex 

	> db.analytics.update({"url" : "www.example.com"} ,{"$inc" : {"pageviews" : 1}})


Above query will increment pageviews field of document with url specified by 1 
Here `$inc` is update modifier.

> When using modifiers, the value of `_id` cannot be changed. (Note that `_id` can be changed by using whole-document replacement.

> Modifiers
> -----

1. `$set` sets the value of a field. If the field does not yet exist, it will be created.

Ex

	db.pageRank.update({url:"google.com"},{"$set":{"location":"India"}})

2. `$unset` remove the key altogether

Ex 

	db.pageRank.update({"url":"google.com"},{$unset:{location:1}})

> Both `$set` and `$unset` can be used to update embeded document by using . operator.

> Incrementing and Decrementing 

- The `$inc` modifier can be used to change the value for an existing key or to create a new key if it does not already exist.Designed for incrementing (and decrementing).

Ex

	db.pageRank.update({url:"google.com"},{$inc:{visits:+10}} )
	db.pageRank.update({url:"google.com"},{$inc:{visits:-10}} )

- Can be used only on values of type integer, long, or double.

> Array modifiers
> -------

> Adding elements

- `$push` adds elements to the end of an array if the array exists and creates a new array if it does not.

Ex

	db.stock.ticker.update({"_id" : "GOOG"},{"$push" : {"price":122}})

Above query will add 122 enteries into the array reffered with key price. 

- You can push multiple values in one operation using the "$each" suboperator:

Ex
	
	> db.stock.ticker.update({"_id" : "GOOG"},
	... {"$push" : {"hourly" : {"$each" : [562.776, 562.790, 559.123]}}})



