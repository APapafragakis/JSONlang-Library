#include <iostream>
#include "JSONlang.h"

int main() {
    // Define a JSON array
    JSON(week_temperatures) = ARRAY(NUMBER(20), NUMBER(19.5), NUMBER(19));

    // Change the 3rd day's temperature
    SET(week_temperatures)[2] ASSIGN(NUMBER(22));

    // Append a new temperature to the array
    SET(week_temperatures)[3] ASSIGN(NUMBER(21.5));

    // Append multiple temperatures to the array
    SET(week_temperatures) APPEND(NUMBER(23), NUMBER(22), NUMBER(20));

    // Print the updated week_temperatures array
    std::cout << "Updated Week Temperatures: ";
    week_temperatures->print();
    std::cout << std::endl;

    // Define a JSON object
    JSON(student) = OBJECT(
        {KEY("name"), STRING("Alex")},
        {KEY("id"), NUMBER(1234)}
    );

    // Add a new key-value pair
    SET(student)["email"] ASSIGN(STRING("alex@example.com"));

    // Update an existing key's value
    SET(student)["name"] ASSIGN(STRING("Alexandros"));

    // Print the updated student object
    std::cout << "Updated Student: ";
    student->print();
    std::cout << std::endl;

    // Define a nested JSON structure
    JSON(students) = ARRAY(
        OBJECT({KEY("name"), STRING("Nikos")}, {KEY("grade"), NUMBER(8.5)}),
        OBJECT({KEY("name"), STRING("Maria")}, {KEY("grade"), NUMBER(9.0)})
    );

    // Modify a nested object's key
    SET(students)[1]["grade"] ASSIGN(NUMBER(9.5));

    // Add a new key-value pair to the first student
    SET(students)[0]["email"] ASSIGN(STRING("nikos@example.com"));

    // Append grades to a student's grades array
    SET(students)[0]["grades"] ASSIGN(ARRAY()); // Create grades array
    SET(students)[0]["grades"] APPEND(
        OBJECT({KEY("hy255"), NUMBER(9)}),
        OBJECT({KEY("hy200"), NUMBER(8)})
    );

    // Print the updated students array
    std::cout << "Updated Students: ";
    students->print();
    std::cout << std::endl;

    return 0;
}
