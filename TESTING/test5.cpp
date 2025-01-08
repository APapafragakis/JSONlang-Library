#include "JSONlang.h"
#include <iostream>

int main() {
    // Orismos aparaititon JSON antikeimenon
    JSON(book) = OBJECT({
        {KEY(title), STRING("Gone Girl")},
        {KEY(published), NUMBER(2012)},
        {KEY(type), STRING("Thriller")},
        {KEY(author), OBJECT({
            {KEY(first_name), STRING("Gillian")},
            {KEY(surname), STRING("Flynn")},
            {KEY(age), NUMBER(45)}
        })}
    });

    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(22), NUMBER(20), 
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

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

    // Ektypwsi JSON gia vivlio
    std::cout << "Book object: ";
    PRINT(book);

    // Ektypwsi thermokrasion ebdomadas
    std::cout << "Week temperatures: ";
    PRINT(week_temperatures);

    // Ektypwsi stoixeion fititon
    std::cout << "Students data: ";
    PRINT(students);

    // Aplos tropos ektypwsis gia mones times
    PRINT(ACCESS(book)["title"]);  // ektypwnei: "Gone Girl"
    PRINT(ACCESS(book)["author"]); // ektypwnei to antikeimeno tou suggrafea
    PRINT(book);                   // ektypwnei olo to antikeimeno book

    // Epipleon leitourgies PRINT
    PRINT(ACCESS(book)["title"]);  // ektypwnei: Gone Girl
    PRINT(ACCESS(book)["author"]); // ektypwnei: {first_name: "Gillian", surname: "Flynn", age: 45}
    PRINT(book);                   // ektypwnei olo to JSON tou vivliou

    // Ektypwsi pollaplon ekfraseon
    PRINT(STRING("Book has key author? "), HAS_KEY(book, "author")); // ektypwnei: Book has key author? true

    return 0;
}
