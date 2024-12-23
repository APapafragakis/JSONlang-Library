#include <iostream>  // Ensure this is included for std::cout
#include "JSONlang.h"

int main() {
    // Define an empty object
    JSON(emptyObj) = OBJECT();

    // Define an empty array
    JSON(emptyArray) = ARRAY();

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

    // Define an array of temperatures for a week
    JSON(week_temperatures) = ARRAY(
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    );

    // Define a complex object with nested objects and arrays for students
    JSON(students) = ARRAY(
        OBJECT(
            {KEY("name"), STRING("Nikos Nikolaou")},
            {KEY("id"), NUMBER(4444)},
            {KEY("grades"), ARRAY(
                OBJECT(
                    {KEY("subject"), STRING("hy100")},
                    {KEY("grade"), NUMBER(7.5)}
                ),
                OBJECT(
                    {KEY("subject"), STRING("hy150")},
                    {KEY("grade"), NUMBER(8)}
                )
            )},
            {KEY("courses"), ARRAY(
                STRING("CS101"),
                STRING("CS102")
            )}
        ),
        OBJECT(
            {KEY("name"), STRING("Maria Papadopoulou")},
            {KEY("id"), NUMBER(4445)},
            {KEY("grades"), ARRAY(
                OBJECT(
                    {KEY("subject"), STRING("hy100")},
                    {KEY("grade"), NUMBER(6)}
                ),
                OBJECT(
                    {KEY("subject"), STRING("hy150")},
                    {KEY("grade"), NUMBER(7.5)}
                )
            )},
            {KEY("courses"), ARRAY(
                STRING("CS101"),
                STRING("CS201")
            )}
        )
    );

    // Print all the JSON objects
    std::cout << "Empty Object: " << emptyObj << std::endl;
    std::cout << "Empty Array: " << emptyArray << std::endl;
    std::cout << "Book: " << book << std::endl;
    std::cout << "Week Temperatures: " << week_temperatures << std::endl;
    std::cout << "Students: " << students << std::endl;

    return 0;
}
