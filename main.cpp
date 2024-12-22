#include <iostream>
#include "JSONlang.h"

int main() {
    // Define empty object
    JSON(emptyObj) = OBJECT();
    emptyObj->print();
    std::cout << std::endl;

    // Define empty array
    JSON(emptyArray) = ARRAY();
    emptyArray->print();
    std::cout << std::endl;

    // Define book object
    JSON(book) = OBJECT(
        {KEY("title"), STRING("Gone Girl")},
        {KEY("published"), NUMBER(2012)},
        {KEY("type"), STRING("Thriller")},
        {KEY("author"), OBJECT(
            {KEY("firstname"), STRING("GILLIAN")},
            {KEY("sirname"), STRING("FLYNN")},
            {KEY("age"), NUMBER(45)}
        )}
    );
    book->print();
    std::cout << std::endl;

    // Define week temperatures
    JSON(week_temperatures) = ARRAY(
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    );
    week_temperatures->print();
    std::cout << std::endl;

    // Define students array
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
    students->print();
    std::cout << std::endl;

    return 0;
}
