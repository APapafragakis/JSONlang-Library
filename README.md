# Αδυναμίες του project

## Ορισμός json μεταβλητών

αντί  
`JSON(emptyObj) = OBJECT{}`  
το κάνουμε  
`JSON(emptyObj) = OBJECT();`

αντί  
`JSON(emptyArray) = ARRAY`  
το κάνουμε  
`JSON(emptyArray) = ARRAY();`

αντί  
`JSON(book) = OBJECT { ... }`  
το κάνουμε  
`JSON(book) = OBJECT ( ... );`

αντί  
`JSON(week_temperatures) = ARRAY[ ... ]`  
το κάνουμε  
`JSON(week_temperatures) = ARRAY( ... );`

αντί  
```
{ KEY(title) : STRING("Gone Girl"), KEY(published) : NUMBER(2012) }
```  
το κάνουμε  
```
{ KEY("title"), STRING("Gone Girl"), KEY("published"), NUMBER(2012) }
```

## Επεξεργασία json μεταβλητών και τιμών

αντί  
`SET week_temperatures[2] ASSIGN NUMBER(22)`  
το κάνουμε  
`SET(week_temperatures)[2] ASSIGN(NUMBER(22));`

αντί  
`SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20)`  
το κάνουμε  
`SET(week_temperatures) APPEND(NUMBER(23), NUMBER(22), NUMBER(20));`

ίσως τους τελεστές `==` `!=` να μην χρησιμοποιούμε σωστά, θα το ξαναδώ.

Δεν κάνουμε πράξεις μέσα στο JSON, θα το ξαναδώ.

## Εκτύπωση json μεταβλητών και τιμών

αντί  
`PRINT book["title"]`  
το κάνουμε  
`PRINT(book,"title");`

αντί  
`PRINT HAS_KEY(book, "author")`  
το κάνουμε  
`PRINT(book, HAS_KEY(book, "author"));`

αντί  
`PRINT STRING("Book has key author? "), HAS_KEY(book, "author")`  
το κάνουμε  
`PRINT(STRING("Book has key author? "), HAS_KEY(book, "author"));`
