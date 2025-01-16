#include "JSONlang.h"
#include <iostream>

int main() {
    
// Orismos keno antikeimeno json me keno antikeimeno
    JSON(emptyObj) = OBJECT({});
// Orismos vivliou json me ena antikeimeno pou periexei dedomena gia ena vivlio
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

// Orismos week_temperatures json me ena pinaka apo arithmous
    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

// Orismos students json me ena pinaka apo antikeimena pou antiprosopeuoun mathites
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

// Allagi thermokrasias 3is meras apo 19 se 22
    SET(week_temperatures)[2] ASSIGN NUMBER(22);

// Prosthesi dieuthynsis email gia ton 1o mathiti
    SET(students)[0]["e-mail"] ASSIGN STRING("csd444@csd.uoc.gr");

// Anathesi neou antikeimenou sto emptyObj json
    SET(emptyObj) ASSIGN OBJECT({ std::make_pair(std::string("a"), STRING("alpha")) });
    
    // Dokimi leitourgikotitas APPEND
    try {
        std::cout << "Appending to week_temperatures" << std::endl;
        SET(week_temperatures).APPEND(NUMBER(23), NUMBER(22), NUMBER(200)); // prosthetei times sto week_temperatures
        std::cout << "Appending to students[0][\"grades\"]" << std::endl;
        std::cout << "Type of students[0][\"grades\"]: " << TYPE_OF(ACCESS(students)[0]["grades"]) << std::endl;
        SET(students)[0]["grades"].APPEND(OBJECT({KEY(hy255), NUMBER(99)})); // prosthetei vathmo gia to mathima hy255
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Week temperatures after appending: ";
    PRINT(week_temperatures);

    std::cout << "Students after appending grade: ";
    PRINT(students);

    // Dokimi leitourgikotitas ERASE
    try {
        ERASE(ACCESS(book)["author"]["age"]); // afairei tin ilikia apo to antikeimeno author tou vivliou
        ERASE(ACCESS(book)["type"]);          // afairei to eidos tou vivliou
        ERASE(book);                          // afairei ola ta dedomena tou vivliou, tora to vivlio einai keno antikeimeno
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Book after erasing: ";
    PRINT(book);

    return 0;
}
