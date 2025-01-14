#include "JSONlang.h"
#include <iostream>

int main() {
    
// Define emptyObj json with empty object
    JSON(emptyObj) = OBJECT({});
// Define book json with an object containing data for a book
    JSON(book) = OBJECT({
        {KEY(title), STRING("Gone Girl")},
        {KEY(published), NUMBER(2012)},
        {KEY(type), STRING("Thriller")},
        {KEY(author), OBJECT({
            {KEY(first_name), STRING("GILLIAN")},
            {KEY(surname), STRING("FLYNN")},
            {KEY(age), NUMBER(45)}
        })}
    });

// Define week_temperatures json with an array of numbers
    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

// Define students json with an array of objects representing students
    JSON(students) = ARRAY({
        OBJECT({
            {KEY(name), STRING("Nikos Nikolaou")},
            {KEY(id), NUMBER(4444)},
            {KEY(grades), ARRAY({
                OBJECT({ {KEY(hy100), NUMBER(7.5)} }),
                OBJECT({ {KEY(hy150), NUMBER(8)} })
            })}
        })
    });

// Change 3rd day temperature from 19 to 22
    SET(week_temperatures)[2] ASSIGN NUMBER(22);

// Add email address for 1st student
    SET(students)[0]["e-mail"] ASSIGN STRING("csd444@csd.uoc.gr");

// Assign new object in emptyObj json
    SET(emptyObj) ASSIGN OBJECT({ std::make_pair(std::string("a"), STRING("alpha")) });
    
    // Test APPEND functionality
    try {
        std::cout << "Appending to week_temperatures" << std::endl;
        SET(week_temperatures).APPEND(NUMBER(23), NUMBER(22), NUMBER(200)); // appends values to week_temperatures
        std::cout << "Appending to students[0][\"grades\"]" << std::endl;
        std::cout << "Type of students[0][\"grades\"]: " << TYPE_OF(ACCESS(students)[0]["grades"]) << std::endl;
        SET(students)[0]["grades"].APPEND(OBJECT({KEY(hy255), NUMBER(99)})); // appends a grade for course hy255
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Week temperatures after appending: ";
    PRINT(week_temperatures);

    std::cout << "Students after appending grade: ";
    PRINT(students);

    // Test ERASE functionality
    try {
        ERASE(ACCESS(book)["author"]["age"]); // removes age from author object of book
        ERASE(ACCESS(book)["type"]);          // removes type of book
        ERASE(book);                          // removes all book data, now book is an empty object
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Book after erasing: ";
    PRINT(book);

    return 0;
}
