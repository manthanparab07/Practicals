---
title: MySQL Notes
---

> ## -- MySQL --
>
> IMP : You can’t modify a table while you’re reading from it at the same time.

1.  select database() ; Display's Current Database in Use

2.  DESCRIBE table ; DESC table ; Display's Structure Of table SHOW COLUMNS from table ;

    SHOW CREATE TABLE table_name ; Advanced QUERY shows engine_type + structure

3.  SHOW DATABASES ; SHOW TABLES;

4.  DATABASE_NAME.table_name ; Removes Ambiguity

5.  ##### Regular Expression

    ... column_name like "exp" ;

    *   `%exp` :- ends with
    *   `exp%` :- starts with
    *   `%exp%` :- sub string
    *   exp is matched `without` checking the case
    *   _ in exp is for matching character length

6. ##### ORDER BY CLAUSE

   ```mysql
   select * from tables_name
   ORDER BY [ BINARY ]column_name_1 , column_name_2 ASC | DESC ;
   ```

   *   The default sort is case `insensitive` and `alphabetically`.
   *   Incase of collision the column_name_2 value is checked and so on.
   *   Each column can have it's own order type .. ASC DESC ..
       
       *   Ex . col1 ASC , col2 DESC , ...
   *   To do ASCII Sort i.e Uppercase comes before lowercase add BINARY .

       ```mysql
         Select * from table_name
         ORDER BY BINARY column_name , ... , [ ASC | DESC ] ;
       ```

7. ##### Type Casting

   CAST( column_name AS new_datatype )

   *   can be used to force a column to be treated as different type make sort behave differently.
   *   -- new_datatype --

       ```sql
         AS BINARY
         AS SIGNED
         AS UNSIGNED
         AS CHAR
         AS DATE
         AS TIME
         AS DATETIME
       ```

3.  ##### LIMIT

    ```sql
    select ... LIMIT a , b        used to control no of rows displayed
select ... LIMIT a OFFSET b   use for speed up .
    ```
    
    *   if only `a` is specified the first `a` records are displayed.
    *   else the next `b` records after first `a` records are displayed .
4.  ##### INSERT

    ```SQL
    insert into table_name values
    (...data...),
    (...data...),
    ...
(...data...);
    ```
    
    *   To insert multiply tracks in a table.
*   This is useful to add multiple rows to a table in one statement ;
    *   This helps to optimize the insertion process unlike the several repeated inserted statements.
    
    *   if any record is duplicate then insertion stops as soon as it is encountered and `all records` of insert are discarded .

*   Add `IGNORE` to add non duplicate values and all duplicate keys are ignored .

          insert IGNORE table_name values ......

* Its an order independent , readable and flexible .

  ```mysql
    insert into table_name( .. column_names .. )
    values ( ..data.. ) , .. ;
  
    insert into table_name() values () , () , () .... ;
  ```

*   All columns in a MySQL table have a default value of `NULL` unless another default value is explicitly assigned when the table is created or modified.

*   The `()` in syntax is used to represent that all columns and values are set to their defaults.

* Another way to insert into a table

  ```mysql
    insert into table_name
    set column_name_1 = value , column_name_2 = value ..... ;
  ```

*   insert data from one column into another.

    ```mysql
      Insert into table_name_1 ( column_name_1 , column_name_2 .... )
      Select column_names ... from table_name_2 
  [ where ... ];
  ```
  
    *   The SIZE and the data_type of the corresponding column must be same.
*   ##### REPLACE Keyword

    *   The `REPLACE` statement is just like `INSERT` , but with one difference.
    *   You can’t INSERT a new row if there is an existing row in the table with the same primary key,
    *   You can get around this problem with a REPLACE query, which first removes any existing row with the same primary key and then inserts the new one.
    *   If there is not matching row then it acts as a normal insert statement.

Syntax

```mysql
REPLACE artist VALUES (2, "Nick Cave and The Bad Seeds");
```

*   The old row is deleted, and, second, the new row is inserted.
*   All insert variant listed above can be used with replace.

> ##### The difference between `INSERT IGNORE` and `REPLACE` in case of duplicatie entry:
>
> *   The first keeps the existing data not the one with duplicate key and does not insert the new row, while the second deletes the existing row and replaces it with the new one.

1. ##### DELETE

   ```mysql
   delete from table_name
   where [condition]...
   ```

2.  if where clause not present then all columns are deleted.

3. Similar to TRUNCATE

   ```mysql
   TRUNCATE TABLE table_name ;
   ```

4.  By using truncate statement MySQL first removes the table Structure and recreates it .

5.  Thus the query does not display row affected count.

6.  The TRUNCATE TABLE statement has two other limitations:

    1.  It’s actually identical to DELETE if you use InnoDB tables i.e ENGINE=InnoDB .
    2.  It does not work with locking or transactions.
7.  ##### Deleting rows from Multiple Table

8.  In multiple table deletes, you can’t use ORDER BY or LIMIT clauses.

9.  Three ways :

10. In first way after `delete` keyword is followed by table_names from which tracks are going to be deleted and after `FROM` clause is followed by table_names that should be queried .

    ```mysql
        DELETE track FROM track WHERE NOT EXISTS
        (SELECT * FROM played WHERE track.artist_id = played.artist_id AND
        track.album_id = played.album_id AND
        track.track_id = played.track_id);
    ```

11. In Second way after `FROM` keyword is followed by table_names from which tracks are going to be deleted and after `USING` clause is followed by table_names that should be queried .

    ```mysql
        -- preferred way
        DELETE FROM track, album USING artist, album, track WHERE 
        artist_name = "New Order" AND
        artist.artist_id = album.artist_id AND
        artist.artist_id = track.artist_id AND
        album.album_id = track.album_id;
    ```

12. Third Way

    ```mysql
        DELETE track, album FROM artist, album, track WHERE
        artist_name = "New Order" AND
        artist.artist_id = album.artist_id AND
        artist.artist_id = track.artist_id AND
        album.album_id = track.album_id;
    ```

13. #### UPDATE

    ```mysql
    update table_name
    set column_name = values , ...
    where conditions ;
    ```

2.  If where clause is not splecified then all rows will get updated.

3.  #### Multi-Table Update

* In first way after `UPDATE` keyword is followed by table_names from which tracks are going to be Updated and after `SET` clause is followed by column_names that should be updated .

  ```mysql
    UPDATE album 
    INNER JOIN track USING  (artist_id, album_id)
    INNER JOIN played USING (artist_id, album_id, track_id)
    SET album_name = UPPER(album_name);
  
                -- OR -- 
  
    UPDATE artist, album, track, played    -- preferred way
    SET album_name = UPPER(album_name)
    WHERE artist.artist_id = album.artist_id AND
    album.artist_id = track.artist_id AND
    album.album_id = track.album_id AND
    track.artist_id = played.artist_id AND
    track.album_id = played.album_id AND
    track.track_id = played.track_id;
  ```

*   You can’t use ORDER BY .

*   You can’t use LIMIT .
*   You can’t update a table that’s read from in a nested subquery.

* #### CREATE DATABASE

  ```mysql
  create DATABASE database_name ;
  create DATABASE IF NOT EXISTS database_name ;
  ```

*   Database name defines a physical directory (folder) on disk after a create statement.

*   On some OS , name of system directory is case `sensitive` for ex. in linux , Mac OSX directory name are case sensitive while in Windows its `insensitive` so DB and db as database_name name is same in Windows while different in linux.
*   MAX length of DATABASE_NAME name can be 64 character length. Same for COLUMN_NAME

1. ##### CREATE TABLE

   ```mysql
   CREATE [ TEMPORARY ] TABLE table_name ( column_name data_type , .. , );
   ```

2.  TEMPORARY allows us to create a table which gets deleted after the window is closed so no cleanup .

3. ##### Create duplicate table from another table

   ```mysql
     create table new_table_name LIKE old_table_name; -- only structure is copied
   ```

4. ##### To copy entire table including data rows.

   ```mysql
     create table new_table_name [AS] Select column_names from table_name
     [where | using ....] ;
   ```

5.  ##### Useful to combine data from two table into one ;

    ```mysql
      Create table emp [AS] Select artist_name , album_name 
      From artist INNER JOIN album USING (artist_id);
    ```

> ### DATA-TYPES

```mysql
1. INT[(width)] [UNSIGNED] [ZEROFILL]

   SIZE OF INT - 4 BYTES .

   width and ZEROFILL can be use for left padding of values.
   Using UNSIGNED the range of allowable value doubles 2^32 - 1 .

   if you use ZEROFILL , MySQL automatically adds UNSIGNED to the
   declaration (since zero filling makes sense only in the context
   of positive numbers).

2. DECIMAL[(width[,decimals])] [UNSIGNED] [ZEROFILL]

   DECIMAL(a,b) :- stores total a digits of which b digits are after
   decimal . a >= b ( DEFAULT b is 0 )

   SIZE : A binary format was introduced that uses four bytes for every
   nine digits.

3. DATE
  Possible Ways to insert a date value :
      YYYY-MM-DD
      YYYY/MM/DD
      YYYYMMDD

4. TIME
  format HHH:MM:SS :- 24 hour clock
    for large value of time i.e in days we can use DD HH:MM:SS
    D is for days, and while displaying DD is converted into hrs.

5. TIMESTAMP
    YYY-MM-DD HH:MM:SS

    if you assign null then is specifies current date and time.

    Deciding column implement which behaviour such as :
      1. TIMESTAMP should be updated only during insert statement
         add DEFAULT CURRENT_TIMESTAMP at the end of declaration.

      2. Updated on both insert and update then add statement
         add DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
         at the end of column declaration.

6. CHAR[ (width) ]
   if width is now specified then default 1 is taken.
   Fixed memory allocation and equal to width BYTES and if characters
   inserted are less than the width space is inserted.

7. BOOLEAN
8. ENUM('value1'[,'value2'[, ...]]   Single Values can be choosen at a time
9. TEXT	-- data of any length 
10.SET('value1'[,'value2'[, ...]])   Multiple Values can be choosen at a time 
   Ex .'val_1,val_2,..'
```

1.  #### Keys and Indexes

2.  A Primary key `uniquely` identifies each row in a table.

3. When declared, MySQL it creates a new file on the disk which stores the information about where the data from each row in the table is stored.This information is called as index and is sole purpose is to speed up the search which includes that Primary key.

   ```mysql
     SHOW INDEXES from table_name ;
   ```

4.  Gives Description of keys described in the tables;

5.  Cardinality is the no of unique value ; for an index of a Primary key i.e same as no of rows in a table.

6.  Index is used for improving performance declared using KEY keyword.

7.  But the performance increase is at the cost of disk space and it need to update whenever the table data change.

8. Syntax

   ```mysql
   create table table_name (
   column_names data_type PRIMARY KEY ,
   ..
   column_name_2 data_type ,
   PRIMARY KEY( column_names ),
   KEY KEY_NAME ( column_names )
   );
   ```

9.  PRIMARY KEY creates a primary key and an index for you, KEY creates an `index` only.

> #### Foreign key Syntax

```mysql
[CONSTRAINT [symbol]] FOREIGN KEY
[index_name] (col_name, ...)
REFERENCES tbl_name (col_name,...)
[ON DELETE reference_option]
[ON UPDATE reference_option]

reference_option:
    RESTRICT | CASCADE | SET NULL | NO ACTION | SET DEFAULT
```

1.  ##### AUTO_INCREMENT

    The AUTO_INCREMENT feature has the following requirements:

    1.  The column it is used on must be indexed ( i.e Primary Key , KEY ).
    
    2.  The column that is it used on cannot have a DEFAULT value.
    
    3.  There can be only one AUTO_INCREMENT column per table.
    
    4.  Starts from 1,2,3,4....
    
    5.  Changing AUTO_INCREMENT starting value 
    
    	```mysql
    	alter table table_name
    	AUTO_INCREMENT new_values ;	
    	```
    
2.  #### Adding, Removing, and Changing Columns

3.  ##### Changing name of the column.

	```mysql
	alter table table_name
	CHANGE old_column_name new_column_name new_data_type [ CONSTRAINTS ] ;
	
	-- change and modify have the same meaning
	```

4.  `CHANGE` OR `MODIFY` have same meaning.

5.  Both name and data type can be changed using single alter command.

	```mysql
	  new_column_name = old_column_name 
	  -- if we only want to change data_type or update CONSTRAINTS .
	```

6.  #### ADD a column to a table

	```mysql
	alter table table_name
	ADD column_name data_type [ CONSTRAINTS ] [ FIRST | AFTER column_name ] ;
	```

7.  use keyword `FIRST` to make the inserted column first column in table.

8.  use keyword `AFTER` to specify the position of column.

9.  #### DROP a column in a table

	```mysql
	alter table table_name
	DROP [COLUMN] column_name ;
	```

10.  #### Multiple Alterations can be done using a single alter command.

	```mysql
	 alter table table_name
	 ADD   ...
	 DROP  ...
	 CHANGE...
	 ;
	```

11.  #### ADD Primary Key

	   

	```mysql
	alter table table_name
	ADD PRIMARY KEY( column_names );	-- index + NOT NULL + UNIQUE
	
	ALTER TABLE artist
	ADD INDEX by_name ( column_names ); -- index
	```

	

12.  #### DROP Primary Key

	  

	```mysql
	 ALTER TABLE table_name
	 DROP PRIMARY KEY;
	
	 ALTER TABLE table_name
	 DROP INDEX by_name;
	```

13.  #### Drop Foreign Key

	```mysql
	ALTER TABLE table_name
	DROP Foreign Key constaint_name ; -- specify constraint while declaring foreign key 
	```

	

14.  INDEX are synonym of KEY and they can be used interchangebly.

15.  #### CHANGING table name

	 

	```mysql
	alter table table_name
	RENAME TO new_table_name ;
	```

	

16.  #### Column `ALIASES`

17.  Syntax

	```mysql
	  Select column_name_1 AS alias_name , .... from table_name ;
	```

18.  A column or a group of columns into a single column output we form an ALIAS using AS keywords.

19.  Cannot Use the alias name in WHERE , USING , ON clauses; i.e

	```mysql
	  Select column_name as alias_name from table_name
	  where alias_name conditions ;
	```

20.  AS keyword is optional and the above queries yield the same result with or without AS.

	1.  #### Table ALIASES

	    ```mysql
	      Select alias_name.column_names from table_name [AS] alias_name
	      where conditions;
	    ```

21.  Unlike Column aliases table aliases can be used in WHERE,USING,ON clauses.

22.  We can use refer the table even before defining the alias.

23.  `AS` keyword is optional but required to make code more concise.

	#### CONCAT()

24.  MySQL Function which concatenates together the strings that are parameters

	```mysql
	   Select CONCAT( column_names , "Hello" , column_names .... )
	   from table_name ; 
	```

	1.  #### AGGREGATING DATA

25.  #### DISTINCT Clause

26.  It is a post processing filter that allows us to remove duplicate entries from the output.

	```mysql
	  Select DISTINCT column_name , column_names from table_name
	  where ...
	```

27.  #### GROUP BY Clause 

28.  It is used to organize data before other clause such as WHERE clause and in contrast ORDER BY is acted once GROUP BY is used.

	```mysql
	  Select column_names from table_name
	  where conditions
	  GROUP BY ( column_names .. )
	  ORDER BY ( column_names .. );
	```

	1.  ##### COUNT() , AVG() , SUM() , MIN() , MAX()

	    MySQL function which is used to count no of records in the output.

	2.  ##### HAVING Clause

29.  AS WHERE clause can only contain expression, HAVING clause can contain both expressions , functions ..

30.  The HAVING clause is only for deciding how to form each group or cluster, not for choosing rows in the output.

	```mysql
	Select column_names from table_name
	where conditions
	GROUP BY column_name  
	HAVING count(*) > 10 ; -- conditions
	```

	

	1.  ##### INNER JOIN

	    ```mysql
	    Select column_names from table_name_1
	    INNER JOIN table_name_2 USING ( column_names , ...) ;  
	    ```
	    
	    The `USING` clause defines one or more columns that are in both tables or results, and used to join or match rows.

*   If the two tables have different column_names which are used in join the they can be joined using `ON` keyword.

	```mysql
	   Select column_names from table_name_1
	   INNER JOIN table_name_2 
	   ON table_name_1.column_name_1 = table_name_2.column_name_2 ;
	```

*   where clause can be also used instead of ON same result.

*   To get `Cartesian` Prodct of two tables :

	```mysql
	   Select * from table_name_1,table_name_2 ;
	   Select * from table_name_1 INNER JOIN table_name_2
	```
	
1.  ##### UNION
	
    ```mysql
	      (
	          Select column_names from table_name 
	          UNION
	          Select column_names from table_name
	          UNION
	      ...
	          Select column_name from table_name
	      )    [ ORDER BY column_name ] ;
	```
	
*   It allows us to combine the output of more than one `SELECT` statement and display it without considering any logical relation between the output of each SELECT statement as long as no of `COLUMNS` of each `SELECT` statement is same `IRRESPECTIVE` OF data_type of the columns in select query.

*   The output is labeled with the names of the column_names of the first query.

*   Use column aliases to change it.

*   All the matching should have same type and same column count of each select query output.

*   `UNION` alone removes all duplicates in the result.

*   Use `UNION ALL` to display duplicates in the results.

* If a sub-query contains ORDER BY clause without LIMIT clause then the sub-query result is not sorted as the it will makes no point but with LIMIT clause it is sorted.

	```mysql
	(Select column_names from table_name order by column_name [ ASC | DESC ] )  
	UNION
	(Select column_names from table_name order by column_name [ ASC | DESC ] ) 
	...
	```


​	

*   The output of the UNION operations is not guarenteed to be ordered even if the sub-query are ordered so add ORDER BY clause at the end of whole query,

	1.  ##### LEFT JOIN

	    ```mysql
	      Select column_names from table_name_1
	      LEFT JOIN table_name_2 USING ( column_names , ...) ;
	    ```

*   Gives Emphasis on the first table.

* Ex. You want to list all tracks, and next to each track you want to show when it was played. If a track has been never been played, you want to see that. If it’s been played many times, you want to see that too.

	1.  ##### NATURAL JOIN
	
	    ```mysql
	      Select column_names from table_name_1
	      NATURAL JOIN table_name_2 ;
	    ```

*   MySQL look for columns with the same names and, behind the scenes, adds these silently into an inner join with a USING clause.

*   May yield unpredictable result if column names are not same or undesired column have same name.

    1.  ##### NESTED QUERIES

*   Nested query is the one which is inside another.

*   The inner query is called nested query which is written in parenthesis.

*   ##### Ex.

* Normal Query

	```mysql
	    Select artist_name  from artist 
	    INNER JOIN album USING (artist_id)  
	    where album_name = "In a Silent Way";
	```

* Identical to Nested Counterpart.

	```mysql
	Select artist_name from artist 
	where artist_id = ( Select artist_id from albumwhere
	                	where album_name = "In a Silent Way"  );
	```

*   #### Performance of Nested vs Unnested

*   Performance wise nested queries are hard to optimize and the are always slower than their Unnested counterpart.

* But it is favourable in situation where large and long table data is to be compared from multiple table at the same time.

	```mysql
	   SELECT track_name FROM track INNER JOIN played
	  USING (artist_id, album_id, track_id)
	  WHERE played = (SELECT MAX(played) FROM played);
	```

* Rather than using a constant value we used a scalar instead.

	```mysql
	  The Sub query in above cases will only work fine if 
	  the output OF the subquery return 1 row ONLY.
	```

*   ##### ANY, SOME , ALL, IN , NOT IN

*   ANY and SOME are equivalent just SOME gives more closer to ENGLISH literal meaning of what they action they perform.

*   They are used for handling multiple subquery row ouptut and then using them to evaluate the outer query.

* For Ex.

 * To find out all engineer whose experience is more than the least experienced producer.

	    ```mysql
	     SELECT engineer_name, years
	     FROM engineer WHERE years > ANY
	     (SELECT years FROM producer);
	    
	     SELECT producer_name FROM producer WHERE
	     producer_name = ANY
	 (SELECT engineer_name FROM engineer);  
	    ```


	    = ANY keyphrase of alias IN

*   ##### ALL

*   Suppose you want to find engineers who are more experienced than all of the producers that is, more experienced than the most experienced producer.

* You can do this with the ALL keyword in place of ANY :

	```mysql
	  SELECT engineer_name, years FROM engineer
	  WHERE years > ALL (SELECT years FROM producer);
	  Empty set (0.00 sec)
	```

*   While the ANY keyword returns values that satisfy at least one condition (Boolean OR), the ALL keyword returns values when all the conditions are satisfied (Boolean AND).

*   > If the table in the subquery is empty, the result is always true.

*   Multipe Columns can be compared using IN and sub-query

    ```mysql
      SELECT producer_name, years FROM producer WHERE
      (producer_name, years) IN
      (SELECT engineer_name, years FROM engineer);
    
      -- IN will result in TRUE Matching Pair is found 
    ```

1.  ###### EXISTS and NOT EXISTS

* Extremely useful for using first column_name inside the nested query.

* The query resulted is called as correlated query.

	```mysql
	SELECT artist_name FROM artist WHERE EXISTS
	(
	    SELECT * FROM album 
	    WHERE album_name = artist_name
	);
	```

* It allows the column of `outer_table` to be compared with `inner_table` column.

*   If the subquery does not any relation with the outer query then the output row count is equal to no of rows generated by the subquery.

* The outer query should produce the artist name whenever the inner query is true.

	```mysql
	  SELECT artist_name FROM artist WHERE EXISTS
	  (   SELECT album.artist_id FROM album 
	      WHERE artist.artist_id = album.artist_id
	      GROUP BY artist.artist_id HAVING COUNT(*) >= 2
	  );
	```

* Same can be done using joins

	```mysql
	  select artist_name  from artist 
	  INNER JOIN album  USING (artist_id) 
	  GROUP BY (artist_name) HAVING count(*) >= 2 ;
	```

*   #### Nested Queries in the FROM Clause

*   Every derived table must have an alias even if not used.

* If we want to display a certain columns from subquery using from clause.

* Useful in cases when you want to apply more than one aggregate function at the same time.

	```mysql
	  SELECT producer_name, months FROM
	  (
	      SELECT producer_name, years*12 AS months FROM producer
	  ) AS prod 
	  where    ...
	  order by ...
	  group by ... ;
	```
	
	> where prod is alias_name for the derived table.
	
	```mysql
	  select avg(album_count) from
	  (
	      Select count(*) as album_count from album
	      GROUP BY (artist_id) 
	  ) as al ;
	```
	
	1.  ##### Types of MySQL tables

*   ##### 1\. Transaction-safe tables(TSTs)

    *   These include the InnoDB table types.
    *   TSTs support transactions and have advanced features that allow you safely restore and recover from database failures.
    
* ##### 2\. Non transaction-safe tables(NTSTs)

	*   These include the MyISAM, Merge, and Memory (also called Heap).
	*   They’re less advanced than the TSTs, but that isn’t always bad.
	*   They’re typically much faster to query because there’s less overhead,and they use much less disk and memory space.

	    ```mysql
	      SHOW TABLE STATUS ;
	      SHOW ENGINES; 
	    
	      ALTER TABLE table_name type = InnoDB; -- change table engine
	    ```

	1.  ##### Transaction

	    ```mysql
	       START TRANSACTION ;       -- TO START 
	       ...
	       ROLLBACK ;                -- TO UNDO CHANGES 
	       ...
	       COMMIT ;                  -- TO MAKE CHANGES PERMANENT
	    ```

*   COMMIT ends the transaction and make the changes to the database.

1.  ##### Managing user privileges

*   ##### Creating and Using New Users

    ```mysql
        GRANT ALL ON database_name.* TO 'user_name'@'localhost' -- user must exists
   -- deprciated --- IDENTIFIED BY 'the_password';
   ```
   
    *   The GRANT statement gives privileges to the user.
    *   ALL - all simple privileges - All Columns of the table.
    *   Above we are granting privileges for all tables inside database_name.
    *   -- If user_name does not exists MySQL will automatically create one with the above privileges. -- depreciated
* ##### To Create user

	```mysql
	   CREATE USER 'user_name'@'host_name' IDENTIFIED BY 'the_password' ;
	```

* ##### To Drop user

	```mysql
	   DROP user 'user_name'@'host_name' ;
	
	    -- OR --  
	
	   delete form mysql.user where user = 'user_name' and Host = 'host_name' ;
	```

*   > user has the name user_name and can connect to the server only from the localhost, the machine on which the database server is installed.

* We can specify a specific table , column names which can be accessed by the user.

	```mysql
	   GRANT ALL ON database_name.table_name TO 'user_name'@'localhost'; 
	```

* ##### Specify columns to be accessed by the user

	```mysql
	   GRANT Select ( column_names ) ON database_name.table_name 
	   TO 'user_name'@'host_name' ;
	```

*   ONLY `SELECT` will make database **read** only.

*   ##### MySQL privilege hierarchy.

* There are four levelsreading from highest to lowest,

	```mysql
	  global, database, table, and column.
	```

* The privileges can be configured:

	```mysql
	  Global       (G)        *.* 
	  Database     (D)        database_name.*
	  Table        (T)        database_name.table_names
	  Column       (C)        Select ( column_names ) on database_name.table_name 
	  							-- makes table read only
	
	  Privilege                  G D T C
	  ALL                     	 ✓ ✓ ✓ ✗
	  ALTER                      ✓ ✓ ✓ ✗
	  CREATE                  	 ✓ ✓ ✗ ✗
	  CREATE TEMPORARY TABLES    ✓ ✓ ✗ ✗
	  DELETE                  	 ✓ ✓ ✓ ✗
	  DROP                       ✓ ✓ ✓ ✗
	  GRANT                      ✓ ✓ ✓ ✗
	  INDEX                      ✓ ✓ ✓ ✗
	  INSERT                     ✓ ✓ ✓ ✓
	  SELECT                     ✓ ✓ ✓ ✓
	  SHOW DATABASES             ✓ ✗ ✗ ✗
	  SHUTDOWN                   ✓ ✗ ✗ ✗
	  UPDATE                     ✓ ✓ ✓ ✓
	
	GRANT SELECT, UPDATE .. [OPTION] ON database_name.* TO 'user_name'@'localhost';
	```

*   #### Ability to `grant` own privileges to others.

* For most applications,there is generally no need for this, because the root user decides on access privileges.

	```mysql
	  GRANT GRANT [OPTION] ON database_name.* TO 'user_name'@'localhost';
	```

*   `SHUTDOWN` Controls whether the server can be shut down with the mysqladmin shutdown command.

    1.  ##### USERS and HOSTS

*   MySQL actually treats local connections differently; if the client is local,the connection is made internally through a Unix socket (for Linux ) or through a named pipe (for Windows).

*   This is generally much faster than the TCP/IP network connection used for remote access.
*   For remote access to the server replace localhost to IP address of machine where the database is installed in GRANT statement.

* #### To login into the server

	```mysql
	      mysql -h ip_address_of_machine -u user_name -p  
	```

*   ip_address_of_machine = localhost [ generally ] .

* ip_address_of_machine can be website name www.hades.com

	```mysql
	  GRANT ALL ON .*. TO 'hades'@'%.hades.com' IDENTIFIED BY 'the_password';
	```

*   The wildcard approach typically removes the need to create multiple users, as a given user can connect from more than one machine.

*   Connections are allowed from any machine in the hades.com domain.

*   ### Anonymous Users

* We can specify wildcard caracters for the host_name to i.e

	```mysql
	 'hades%'@'localhost'.
	
	SELECT CURRENT_USER();
	SHOW GRANTS;                            -- current priviledges
	SHOW GRANTS FOR 'selina'@'localhost';
	```

*   #### Revoking privileges

* To remove priviledges from user of access to column , tables.

	```mysql
	  REVOKE SELECT (time) ON music.track FROM 'partmusic'@'localhost';
	```

*   syntax same as grant except works opposite.

*   #### FLUSH PRIVILEGES;

* Whenever you update the grant tables in the mysql database directly, you have to use the FLUSH PRIVILEGES instruction to tell the server to read in the updated data:

	```mysql
	  FLUSH PRIVILEGES;
	```

*   ##### Set Password

    ```mysql
      SET PASSWORD FOR 'user_name'@'localhost' = 'new_password';
    ```

1.  ##### Stored Object

*   Stored database objects that are defined in terms of SQL code that is stored on the server for later execution.

*   ##### Types of stored Objects

    1.  Stored procedure:

        *   An object created with CREATE PROCEDURE and invoked using the CALL statement.
            *   A procedure does not have a return value but can modify its parameters for later inspection by the caller.
   1.  Stored function:
        2.  An object created with CREATE FUNCTION and used much like a built-in function.
        3.  You invoke it in an expression and it returns a value during expression evaluation.

  4.  Trigger:

        5.  An object created with CREATE TRIGGER that is associated with a table.
        6.  A trigger is activated when a particular event occurs for the table, such as an insert or update.

  7.  Event:

        8.  An object created with CREATE EVENT and invoked by the server according to schedule.

  9.  View:

        10.  An object created with CREATE VIEW that when referenced produces a result set.
        11.  A view acts as a virtual table.

*   Stored `routines` include stored procedures and functions.
*   Stored `programs` include stored routines, triggers, and events.
*   Stored `objects` include stored programs and views.

1. ##### Variables in MySQL

```mysql
 SELECT @artist:=artist_name 
 FROM artist WHERE artist_id = 1;
```

2.  artist is variable and is assigned using := operator.

3.  ##### To display the variable content we use

    ```mysql
   Select @artist ;
   ```

    *   To explicitly setting the variable we use SET command

        ```mysql
      SET @var = 'value' , @var1 = 'value1' ... ;
      ```
      
        1.  Variables are unique to a connection.
        2.  Case sensitive default null value.
        3.  Destroyed when then connection closes.
        4.  Try avoiding using same variable to define and display in the same query.
4. To declare LOCAL variable inside a procedure/function.

	```mysql
	   DECLARE variable_names[,] datatype(size)  [ DEFAULT default_value ] ;
	```
	
	these local variables are displayed without @ prefix
	
	```mysql
	   Select variable_names , variable_names ;
	```
	
	*   DECLARE is permitted only inside a BEGIN ... END compound statement and must be at its start, before any other statements.
	    *   Scope till END statement.
	    *   Declarations must follow a certain order.
	        *   Cursor declarations must appear before handler declarations.
	        *   Variable and condition declarations must appear before cursor or handler declarations.

1.  ##### Procedures and Functions ( Routines )

2.  Any variable defined inside or changed persist even after the function call ends.

7. First change default delimiter(;) to another one as the procedure body will have a delimiter seperated queries which should not hinder the outside body.

	```mysql
	  delimiter new_delim    ;        -- changed curr_delim to new delim
	
	  CREATE PROCEDURE procedure_name( parameter_name data_type )
	  BEGIN
	  -- query1 ;
	  -- query2 ;
	  END
	  new_delim         -- acts as an exit for procedure definition
	
	  delimiter ;     -- restores original delimiter.
	```

8. ##### CALL

	```mysql
	  CALL procedure_name( parameters );
	```

9. ##### To remove a procedure

	```mysql
	  DROP PROCEDURE procedure_name ;
	```

10. ##### To get all the user_defined function of database.

	```mysql
	  select specific_name, routine_type , definer 
	  from information_schema.routines 
	  where definer not like '%mysql%';
	```

11. ##### Types of modes

	```mysql
	  IN        : Read Only Variable inside routine block
	  OUT       : Write Only Variable inside routine block
	  INOUT     : both
	```

	1. IN PARAMETER

		*   Used for variables which are passed as argument and are needed inside the procedure body.
		*   Can be read inside the procedure body.
		*   As it is call by value any changes made into the variable is not reflected into the original variable.
	
		    ```mysql
		      CREATE  PROCEDURE  GetOfficeByCountry(
		          IN  countryName  VARCHAR(255) )
		    ```

	2. OUT PARAMETER

		*   Used as a variable to return a value after a procedure call.
		*   The Variable cannot be read inside the procedure and it is only for write purposes.
		*   Syntax
	
		    ```mysql
		      CREATE  PROCEDURE  GetOrderCountByStatus  (
		      IN orderStatus  VARCHAR(25),
		      OUT  total  INT )
		      select count(*) INTO OUT .....
		    ```

	3.  INOUT PARAMETER

	    *   The Variable can be read as well as changed inside the procedure.
	    *   Changes are returned after calling.
	    *   Syntax

	        ```mysql
	          CREATE  PROCEDURE  Counter  (
	          INOUT counter INT )
	          select counter ;
	          select counter + 1 INTO counter ;
	        ```

12. ##### Functions

	```mysql
	  CREATE FUNCTION function_name( arg_list ) 
	  RETURNS data_type
	  [ NOT ] DETERMINISTIC
	  BEGIN
	  -- qeury 1	-- cannot be a select query
	  -- query 2	-- cannot be a select query
	  RETURN value
	  END
	```

9.  A function can be called inside any statement just like any other mysql function i.e Select function_name( arg_list ).

10.  When returning a value of char or varchar data type use @value instead of value as it would return default VALUE instead of changed value.

11.  ##### DETERMINISTIC

12.  for a particular input it produces same output always.
13.  Useful for optimization.

*   > Stored routines does improve performance of the system as less information is to be sent from database to the server but additional load is on the server as more work is done by the server and less by the client.

* ##### Procedures and functions can be dropped using

	```mysql
	  DROP PROCEDURE procedure_name 
	  DROP FUNCTION  function_name
	```

*   ##### As routines are associated with a particular database several implications:

    1.  USE statements are not permitted as routines are associated with a particular database but other database can be used and called using `database.routine` or any other format.

    2.  When database is dropped routines associated are also dropped.

    3.  Functions cannot be recursive .

1.  ##### Triggers

*   A trigger is a named database object that is associated with a table, and that activates when a particular event occurs for the table.

*   A trigger is defined to activate when a statement inserts, updates, or deletes rows in the associated table BEFORE or AFTER the query execution.

    ```mysql
       CREATE TRIGGER trigger_name ( BEFORE | AFTER )( INSERT| UPDATE | DELETE )
       ON table_name
       FOR EACH ROW 
       BEGIN
       --query - 1
       --query - 2
       END;
   new_delim 
   ```
   
    *   FOR EACH ROW : defines the trigger body;
* Within the trigger body, the OLD and NEW keywords enable you to access columns in the rows affected by a trigger.

	```mysql
	 In INSERT only NEW can be used.
	 In DELETE only OLD can be used.
	 In UPDATE both OLD and NEW can be used.
	```

* ##### Display ALL trigger

	```mysql
	  Select trigger_name , definer 
	  from information_schema.triggers 
	  where definer NOT LIKE '%mysql%' ;
	
	  -- or --
	
	  show triggers ;
	```

*   ##### limitations

    *   Cannot USE CALL to call a trigger.
    *   Cannot be used for transaction.
*   ##### Triggers handle error

    1.  If a `BEFORE` trigger fails, the operation on the corresponding row is not performed.

        1.  A `BEFORE` trigger is activated by the attempt to insert or modify the row, regardless of whether the attempt subsequently succeeds.

        2.  An `AFTER` trigger is executed only if any BEFORE triggers and the row operation execute successfully.

        3.  An error during either a `BEFORE` or `AFTER` trigger results in failure of the entire statement that caused trigger invocation.

        4.  For transactional tables, failure of a statement should cause rollback of all changes performed by the statement.

    1.  ##### Cursors

*   Cursor is a temporary work area created in system memory when a SQL statement is executed.

*   A cursor is a set of rows together with a pointer that identifies a current row.

*   It is a database object to retrieve data from a result set one row at a time.

*   A cursor can hold more than one row, but can process only one row at a time.

*   The set of rows the cursor holds is called the active set.

*   ##### Types of cursors

    1.  Implicit

        *   Generated by the system during INSERT UPDATE DELETE ( DML ).
    2.  Explicit --

        *   Generated by user using SELECT command and the cursor contains more than one rows.
            *   After fetching one row the cursor pointer moves to the next row.
* ##### Each cursor contains the followings 5 parts,

	1. Declare Cursor:
	
		```mysql
		 DECLARE cursor_name CURSOR FOR select_statement; 
		```
	
	2. Open:
	
		```mysql
		 OPEN cursor_name;
		```
	
	3. Fetch:
	
		```mysql
		 FETCH cursor_name INTO var , var1 , var2 ... ;
		```
	
	4. Close:
	
		```mysql
		 CLOSE cursor_name ;
		```
	
	5. A `NOT FOUND` handler handles the situation when the cursor could not find any row.
	
		```mysql
		 DECLARE CONTINUE HANDLER FOR NOT FOUND set var_found = 1 ;
		```
	
	6.  Must appear after cursor declaration.
	
	    Ex.
	
	    ```mysql
	DECLARE finished INTEGER DEFAULT 0; 
	    DECLARE email varchar(255) DEFAULT "";
	-- declare cursor for employee email
	    DEClARE email_cursor CURSOR FOR SELECT email FROM employees;
	-- declare NOT FOUND handler
	    DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
	OPEN email_cursor;
	    
	get_email: LOOP
	    FETCH email_cursor INTO v_email;
	IF v_finished = 1 THEN 
	    	LEAVE get_email;
	END IF;
	    -- build email list
	SET email_list = CONCAT(v_email,";",email_list); 
	    END LOOP get_email;
	CLOSE email_cursor;
	    ```


​	    

	1.  ##### Flow Control Statements
	
	    MySQL Does NoT Support `FOR` Loop

* ##### `CASE` Statement

	* Syntax

		```mysql
		   CASE [ case_value ]
		   WHEN search_condition THEN statement_list
		  [WHEN search_condition THEN statement_list] ...
		  [ELSE statement_list]
		   END CASE
		```

	*   Each _`statement_list` _consists of one or more SQL statements; an empty_ `statement_list`_ is not permitted.
	*   To handle situations where no value is matched by any `WHEN` clause, use an `ELSE` containing an empty [`BEGIN ... END`](https://dev.mysql.com/doc/refman/8.0/en/begin-end.html "13.6.1 BEGIN ... END Compound-Statement Syntax") block

	    ```mysql
	      WHEN 2 THEN Select 2 ;                 -- with    case_value
	      WHEN no = 2 THEN Select 2 ;            -- without case_value
	    ```

* ##### IF Statements

	```mysql
	  IF search_condition THEN statement_list
	  [ELSEIF search_condition THEN statement_list] ...
	  [ELSE statement_list]
	  END IF
	```

* Example

	```mysql
	  IF n > m THEN SET s = '>';
	  ELSEIF n = m THEN SET s = '=';
	  ELSE SET s = '<';
	  END IF;
	```

*   ##### LOOP

    ```mysql
      [begin_label:] LOOP
          statement_list
  END LOOP [end_label]
  ```
  
    *   Loop is terminated with one of the following Ways
        1.  `LEAVE`
        2.  `RETURN`
    *   Infinite Loop Allowed if terminating condition is not present.
*   ##### ITERATE

    ```mysql
  ITERATE label
  ```
  
    *   Similar to `continue` in FOR LOOP as in case of OOP language.
    *   Means 'Start the Loop Again' .
*   ###### LEAVE

    ```mysql
  LEAVE label
  ```
  
    *   Similar to `break` in OOP language.
* #### Sample

	```mysql
	  CREATE PROCEDURE doiterate(p1 INT)
	  BEGIN
	    label1: LOOP
	      SET p1 = p1 + 1;
	      IF p1 < 10 THEN
	        ITERATE label1;
	      END IF;
	      LEAVE label1;
	    END LOOP label1;
	    SET @x = p1;
	  END;
	```

*   ##### REPEAT

    ```mysql
      [begin_label:] REPEAT
          statement_list
      UNTIL search_condition
  END REPEAT [end_label]
  ```
  
    *   Executes Atleast Once.
*   ###### WHILE

    ```mysql
      [begin_label:] WHILE search_condition DO
      statement_list
      END WHILE [end_label]
    ```

1.  > ##### VIEWS

2. Syntax

	```mysql
	  CREATE
	  [OR REPLACE]
	  VIEW view_name [(column_list)]
	  AS select_statement ;
	```

3.  The view definition is “`frozen`” at creation time and is not affected by subsequent changes to the definitions of the underlying tables. i.e any changed made in the underlying table after view is created is not reflected in it.

4.  `column_list` allow to change the column name generated from `select_statement` and the this name is used to access the data from view .
5.  Insert , Update command is allowed on view as long as the statement satisfies the underlying table(s) schema and constraints .
6.  The Changes made are reflected back to the original table(s) they represent to.
7. `REPLACE` cannot be used without insert in view thus the query can be

	```mysql
	  CREATE OR REPLACE ....
	```

8.  > ##### DROP A VIEW

    ```mysql
      DROP VIEW [IF EXISTS]
      view_name [, view_name] ... ;
    ```

> ##### Constraints and Assertions

*   An Assertion is just a special type of integrity Constraint
*   It is not necessarily dependent on a `single Base table` as simple Constraints are.
*   An SQL `Constraint` is a named rule which helps define valid sets of values by putting limits on the results of `INSERT`, `UPDATE` or `DELETE` operations performed on a Base table, an `Assertion`, by contrast, may define valid sets of values for individual rows or for an entire Base table.
*   There are four Constraint variations
    *   `UNIQUE` Constraints,
    *   `PRIMARY KEY` Constraints,
    *   `FOREIGN KEY` Constraints
    *   `CHECK` Constraints.

> #### An Assertion is a `CHECK` Constraint that may operate on multiple Tables.
>
> #### `CHECK` are no longer supported in MySQL.

*   MySQL CONSTRAINTS can be classified into two types - column level and table level.

*   The column level constraints can apply only to one column where as table level constraints are applied to the entire table.

*   MySQL CONSTRAINT is declared at the time of creating a table.

**MySQL CONSTRAINTs are :**

* ```mysql
    
    ```
	*   NOT NULL
	*   UNIQUE
	*   PRIMARY KEY
	*   FOREIGN KEY
	*   CHECK		-- dep
	*   DEFAULT

The difference between assertions and checks is a little more murky, many databases including `MySQL` don't even support assertions.

Any attempt to insert a value in the balance column of less than 100 would throw an error.

**Assertions** - An assertion is a piece of SQL which makes sure a condition is satisfied or it stops action being taken on a **database object**. It could mean locking out the whole table or even the whole database.

```mysql
Syntax
CREATE ASSERTION assertion_name CHECK
( conditions );
```

> ##### Dynamic SQL

*   Dynamic SQL is used when then record to be searched or updated depends on user input or function or any other database objects.
*   This unknown entity in SQL Command is represented as '?'.
* In MYSQL Dynamic SQL is Supported using `PREPARE`

	```mysql
	  PREPARE stmt_name FROM 
	  'QUERY with runtime variable '?' '
	```

* EX :

	```mysql
	  PREPARE stmt from 
	  'Select * from artist                        
	  WHERE artist_name like ? ';
	```

*   NOW TO EXECUTE THE COMMAND

    ```mysql
  EXECUTE stmt_name USING @VAR , @VAR1 .... ;
  ```
  
    *   No of '?' inside the `PREPARE` statement and the variable passed must be equal.
*   DEALLOCATE AFTER USE

    *   THE `PREPARE` Statement allocates the memory for the sql query.
*   [`PREPARE`](https://dev.mysql.com/doc/refman/8.0/en/prepare.html "13.5.1 PREPARE Syntax") prepares a statement for execution

*   [`EXECUTE`](https://dev.mysql.com/doc/refman/8.0/en/execute.html "13.5.2 EXECUTE Syntax") executes a prepared statement
*   [`DEALLOCATE PREPARE`](https://dev.mysql.com/doc/refman/8.0/en/deallocate-prepare.html "13.5.3 DEALLOCATE PREPARE Syntax") releases a prepared statement.

> Using prepared statements with placeholders for parameter values has the following benefits:

*   Less overhead for parsing the statement each time it is executed. Typically, database applications process large volumes of almost-identical statements, with only changes to literal or variable values in clauses such as `WHERE` for queries and deletes, `SET` for updates, and `VALUES` for inserts.

*   Protection against SQL injection attacks. The parameter values can contain unescaped SQL quote and delimiter characters.

> FEATURES

*   A prepared statement is specific to the session in which it was created. If you terminate a session without deallocating a previously prepared statement, the server deallocates it automatically.

*   A prepared statement is also global to the session. If you create a prepared statement within a stored routine, it is not deallocated when the stored routine ends.

> ###### CANNOT BE USED INSIDE A `PROCEDURE` OR `FUNCTION` .
>
> #### DECLARE ... HANDLER Syntax

* Syntax

	```mysql
	  DECLARE handler_action HANDLER
	      FOR condition_value [, condition_value] ...
	      BEGIN
	      -- query to be executed 
	      END ;
	
	  handler_action: {
	      CONTINUE
	    | EXIT
	    | UNDO
	  }
	
	  condition_value: {
	      mysql_error_code
	    | SQLSTATE [VALUE] sqlstate_value
	    | condition_name
	    | SQLWARNING
	    | NOT FOUND
	    | SQLEXCEPTION
	  }    
	```

*   The _`handler_action`_ value indicates what action the handler takes after execution of the handler statement:

*   `CONTINUE`: Execution of the current program continues.

*   `EXIT`: Execution terminates for the [`BEGIN ... END`](https://dev.mysql.com/doc/refman/8.0/en/begin-end.html "13.6.1 BEGIN ... END Compound-Statement Syntax") compound statement in which the handler is declared. This is true even if the condition occurs in an inner block.

*   `UNDO`: Not supported.

*   The HANDLER CODE is executed when the condition is occurred and based on the handler action appropriate action is taken ;

*   Ex. We can create a handler to display warning whenever a query is executed within a procedure i.e

    ```mysql
      create procedure proc()
      BEGIN
      DECLARE CONTINUE HANDLER FOR SQLWARNING
          BEGIN
              show warnings ;
          END ; 
      insert ignore into artist values (1211,"HADES"); -- duplicate entry
      END;
      //
    ```