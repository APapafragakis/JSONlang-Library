#include <iostream>
#include "JSONlang.h"

int main() {
    // Define a JSON object
    JSON(book) = OBJECT(
        {KEY("title"), STRING("C++")},
        {KEY("author"), OBJECT(
            {KEY("name"), STRING("Bjarne")},
            {KEY("age"), NUMBER(70)}
        )},
        {KEY("type"), STRING("Programming")}
    );

    // Print the original JSON object
    std::cout << "Original JSON object:\n";
    book->print();
    std::cout << "\n\n";

    // Test 1: Remove nested key "author.age"
    ERASE(book, "author", "age"); // Removes the "age" key from the "author" object
    std::cout << "After ERASE(book, \"author\", \"age\"):\n";
    book->print();
    std::cout << "\n\n";

    // Test 2: Remove top-level key "type"
    ERASE(book, "type"); // Removes the "type" key
    std::cout << "After ERASE(book, \"type\"):\n";
    book->print();
    std::cout << "\n\n";

    // Test 3: Clear the entire object
    ERASE(book); // Clears all data in the "book" object
    std::cout << "After ERASE(book):\n";
    book->print();
    std::cout << "\n";

    return 0;
}
