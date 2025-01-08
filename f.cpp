#include "JSONlang.h"
#include <iostream>

int main() {
// Define emptyObj json with empty object
    JSON(emptyObj) = OBJECT({});

// Define emptyArray json with empty array
    JSON(emptyArray) = ARRAY({});

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
    SET(emptyObj) ASSIGN OBJECT({ {KEY(a), STRING("alpha")} });

// Define hy352_nik and students with arithmetic operations
    JSON(hy352_nik) = OBJECT({
        {KEY(examination), NUMBER(7)},
        {KEY(project), NUMBER(8)}
    });

    // Test string concatenation
    JSON(fullName) = STRING("Nikos") + STRING(" Nikolaou");
    std::cout << "Concatenated string: ";
    PRINT(fullName);

    // Test array concatenation
    JSON(array1) = ARRAY({NUMBER(1), NUMBER(2)});
    JSON(array2) = ARRAY({NUMBER(3), NUMBER(4)});
    JSON(combinedArray) = array1 + array2;
    std::cout << "Concatenated array: ";
    PRINT(combinedArray);

    // Test arithmetic operations
    JSON(exam_weight) = NUMBER(0.75);
    JSON(project_weight) = NUMBER(0.25);
    
    // Modified calculation
    auto obj = std::dynamic_pointer_cast<JsonObject>(hy352_nik);
    JSON(final_grade) = 
        std::dynamic_pointer_cast<JsonNumber>(obj->get("examination")) * exam_weight +
        std::dynamic_pointer_cast<JsonNumber>(obj->get("project")) * project_weight;
    
    std::cout << "Final grade: ";
    PRINT(final_grade);

    // Test boolean operations
    JSON(bool1) = BOOLEAN(true);
    JSON(bool2) = BOOLEAN(false);
    JSON(bool_result) = bool1 && bool2;
    std::cout << "Boolean AND result: ";
    PRINT(bool_result);

    // Test comparison operations
    JSON(num1) = NUMBER(5);
    JSON(num2) = NUMBER(3);
    if (*num1 > *num2) {
        std::cout << "5 is greater than 3" << std::endl;
    }

    // Complex example from the requirement
    JSON(student_with_grade) = ARRAY({
        OBJECT({
            {KEY(name), STRING("Nikos") + STRING(" Nikolaou")},
            {KEY(id), NUMBER(4444)},
            {KEY(grades), ARRAY({
                OBJECT({
                    {KEY(hy352), 
                        std::dynamic_pointer_cast<JsonNumber>(obj->get("examination")) * NUMBER(0.75) + 
                        std::dynamic_pointer_cast<JsonNumber>(obj->get("project")) * NUMBER(0.25)
                    }
                })
            })}
        })
    });

    std::cout << "Student with calculated grade: ";
    PRINT(student_with_grade);

    // Test the new operators
    std::cout << "Size of array: " << SIZE_OF(week_temperatures) << std::endl;
    std::cout << "Is array empty? " << (IS_EMPTY(week_temperatures) ? "true" : "false") << std::endl;
    std::cout << "Has key 'title'? " << (HAS_KEY(book, "title") ? "true" : "false") << std::endl;
    std::cout << "Type of book: " << TYPE_OF(book) << std::endl;

    // Test with different types
    std::cout << "Size of number: " << SIZE_OF(num1) << std::endl;
    std::cout << "Is string empty? " << (IS_EMPTY(fullName) ? "true" : "false") << std::endl;
    std::cout << "Has key in array? " << (HAS_KEY(array1, "key") ? "true" : "false") << std::endl;
    std::cout << "Type of boolean: " << TYPE_OF(bool1) << std::endl;

    std::cout << "Students with arithmetic operations: ";
    PRINT(students);

    std::cout << "Empty object: ";
    PRINT(emptyObj);

    std::cout << "Empty array: ";
    PRINT(emptyArray);

    std::cout << "Book object: ";
    PRINT(book);

    std::cout << "Week temperatures: ";
    PRINT(week_temperatures);

    std::cout << "Students data: ";
    PRINT(students);


    // Use the simpler PRINT for single values
    PRINT(ACCESS(book)["title"]);  // prints: "Gone Girl"
    PRINT(ACCESS(book)["author"]); // prints the author object
    PRINT(book);          // prints the whole book object

    // Use ACCESS for all direct [] operations
    // PRINT(TYPE_OF(ACCESS(book)["author"]), SIZE_OF(book), IS_EMPTY(book));

    
    // Test new PRINT functionality
    PRINT(ACCESS(book)["title"]);  // prints: Gone Girl
    PRINT(ACCESS(book)["author"]); // prints: {firstname:"Gillian",sirname:"Flynn",age: 45}
    PRINT(book);          // prints: the whole json for book
    
    // Print multiple expressions
    PRINT(STRING("Book has key author? "), HAS_KEY(book, "author")); // prints: Book has key author? true
    
    // Test APPEND functionality
    try {
        std::cout << "Appending to week_temperatures" << std::endl;
        SET(week_temperatures).APPEND(NUMBER(23), NUMBER(22), NUMBER(20)); // appends values to week_temperatures
        std::cout << "Appending to students[0][\"grades\"]" << std::endl;
        std::cout << "Type of students[0][\"grades\"]: " << TYPE_OF(ACCESS(students)[0]["grades"]) << std::endl;
        SET(students)[0]["grades"].APPEND(OBJECT({KEY(hy255), NUMBER(9)})); // appends a grade for course hy255
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
