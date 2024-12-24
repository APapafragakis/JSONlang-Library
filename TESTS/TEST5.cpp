#include <iostream>
#include "JSONlang.h"

int main() {
    // Define a book object with nested objects and arrays
    JSON(book) = OBJECT(
        {KEY("title"), STRING("Gone Girl")},
        {KEY("published"), NUMBER(2012)},
        {KEY("type"), STRING("Thriller")},
        {KEY("author"), OBJECT(
            {KEY("firstname"), STRING("GILLIAN")},
            {KEY("sirname"), STRING("FLYNN")},
            {KEY("age"), NUMBER(45)},
            {KEY("books_written"), ARRAY(
                STRING("Sharp Objects"),
                STRING("Dark Places")
            )}
        )},
        {KEY("genres"), ARRAY(
            STRING("Fiction"),
            STRING("Thriller"),
            STRING("Crime")
        )}
    );

    PRINT(book,"title");  // prints: Gone Girl 
    PRINT(book,"author"); // prints: {firstname:"GILLIAN", sirname:"FLYNN", age:45} 
    PRINT(book, HAS_KEY(book, "author"));  // prints: true
    PRINT(STRING("Book has key author? "), HAS_KEY(book, "author"));  // prints: Book has key 'author'? true
    return 0;
}
