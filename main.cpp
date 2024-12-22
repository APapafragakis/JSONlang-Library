#include <iostream>
#include "JSONlang.h"

int main() {
    // Define a JSON array
    JSON(week_temperatures) = ARRAY(NUMBER(20), NUMBER(19.5), NUMBER(19));

    // Use ASSIGN directly
    SET(week_temperatures)[2] ASSIGN(NUMBER(22)); // Change the 3rd day temperature

    // Print the updated array
    std::cout << "Updated Week Temperatures: ";
    week_temperatures->print();
    std::cout << std::endl;

    return 0;
}
