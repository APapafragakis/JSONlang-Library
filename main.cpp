#include <iostream>
#include "JSONlang.h"

int main() {
    // Define JSON variables
    JSON(week_temperatures) = ARRAY(
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    );

    JSON(students) = ARRAY(
        OBJECT(
            {KEY("name"), STRING("Nikos Nikolaou")},
            {KEY("id"), NUMBER(4444)},
            {KEY("grades"), ARRAY(
                OBJECT({KEY("hy100"), NUMBER(7.5)}),
                OBJECT({KEY("hy150"), NUMBER(8)})
            )}
        )
    );

    JSON(emptyObj) = OBJECT();

    // Modify JSON variables
    SET(week_temperatures)[2].assign(NUMBER(22)); // Change 3rd day temperature
    SET(students)[0]["email"].assign(STRING("csd444@csd.uoc.gr")); // Add email address to 1st student
    SET(emptyObj).assign(OBJECT({KEY("a"), STRING("alpha")})); // Assign new object to emptyObj

    // Print updated JSON structures
    std::cout << "Updated Week Temperatures: ";
    week_temperatures->print();
    std::cout << std::endl;

    std::cout << "Updated Students: ";
    students->print();
    std::cout << std::endl;

    std::cout << "Updated Empty Object: ";
    emptyObj->print();
    std::cout << std::endl;

    return 0;
}
