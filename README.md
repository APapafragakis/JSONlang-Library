# Weaknesses of the project

## JSON variable definition

Instead of  
`JSON(emptyObj) = OBJECT{}`  
we do  
`JSON(emptyObj) = OBJECT();`

Instead of  
`JSON(emptyArray) = ARRAY`  
we do  
`JSON(emptyArray) = ARRAY();`

Instead of  
`JSON(book) = OBJECT { ... }`  
we do  
`JSON(book) = OBJECT ( ... );`

Instead of  
`JSON(week_temperatures) = ARRAY[ ... ]`  
we do  
`JSON(week_temperatures) = ARRAY( ... );`

Instead of  
