# Weaknesses of the Project

## JSON Variable Definition

Instead of  
JSON(emptyObj) = OBJECT{}  
We do it as  
JSON(emptyObj) = OBJECT();

Instead of  
JSON(emptyArray) = ARRAY  
We do it as  
JSON(emptyArray) = ARRAY();

Instead of  
JSON(book) = OBJECT { ... }  
We do it as  
JSON(book) = OBJECT ( ... );

Instead of  
JSON(week_temperatures) = ARRAY[ ... ]  
We do it as  
JSON(week_temperatures) = ARRAY( ... );

Instead of  
{ KEY(title) : STRING("Gone Girl"), KEY(published) : NUMBER(2012) }
  
We do it as  
{ KEY("title"), STRING("Gone Girl"), KEY("published"), NUMBER(2012) }

## Editing JSON Variables and Values

Instead of  
SET week_temperatures[2] ASSIGN NUMBER(22)  
We do it as  
SET(week_temperatures)[2] ASSIGN(NUMBER(22));

Instead of  
SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20)  
We do it as  
SET(week_temperatures) APPEND(NUMBER(23), NUMBER(22), NUMBER(20));

Perhaps we are not using the operators == != correctly, I will review it.

We do not perform calculations inside the JSON, I will review this too.

## Printing JSON Variables and Values

Instead of  
PRINT book["title"]  
We do it as  
PRINT(book,"title");

Instead of  
PRINT HAS_KEY(book, "author")  
We do it as  
PRINT(book, HAS_KEY(book, "author"));

Instead of  
PRINT STRING("Book has key author? "), HAS_KEY(book, "author")  
We do it as  
PRINT(STRING("Book has key author? "), HAS_KEY(book, "author"));
