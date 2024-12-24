#include "JSONlang.h"

int main() {
    // Orismos enos JSON pinaka
    JSON(week_temperatures) = ARRAY(NUMBER(20), NUMBER(19.5), NUMBER(19));

    // Allagi tis thermokrasias tis 3is meras
    SET(week_temperatures)[2] ASSIGN(NUMBER(22));

    // Prosthesi neas thermokrasias ston pinaka
    SET(week_temperatures)[3] ASSIGN(NUMBER(21.5));

    SET(week_temperatures)[0] ASSIGN(ARRAY(OBJECT ({KEY("time"), STRING("morning")})));

    // Prosthesi pollaplon thermokrasion ston pinaka
    SET(week_temperatures) APPEND(NUMBER(23), NUMBER(22), NUMBER(20));

    SET(week_temperatures)[0] APPEND(OBJECT ({KEY("time"), STRING("night")}));

    // Ektypwsi tou ananeomenou pinaka thermokrasion
    std::cout << "Updated Week Temperatures: ";
    week_temperatures->print();
    std::cout << std::endl;

    // Orismos enos JSON antikeimenou
    JSON(student) = OBJECT(
        {KEY("name"), STRING("Alex")},
        {KEY("id"), NUMBER(1234)}
    );

    // Prosthesi enos neou zevgous kleidi-axia
    SET(student)["email"] ASSIGN(STRING("alex@example.com"));

    // Ananewsi tis timis enos idiou kleidiou
    SET(student)["name"] ASSIGN(STRING("Alexandros"));

    // Ektypwsi tou ananeomenou JSON antikeimenou
    std::cout << std::endl;
    std::cout << "Updated Student: ";
    student->print();
    std::cout << std::endl;

    // Orismos enos enthesimenou JSON pinaka
    JSON(students) = ARRAY(
        OBJECT({KEY("name"), STRING("Nikos")}, {KEY("grade"), NUMBER(8.5)}),
        OBJECT({KEY("name"), STRING("Maria")}, {KEY("grade"), NUMBER(9.0)})
    );

    // Ananewsi timis gia ena kleidi mesa se antikeimeno
    SET(students)[1]["grade"] ASSIGN(NUMBER(9.5));

    // Prosthesi neou zevgous kleidi-axia sto proto antikeimeno
    SET(students)[0]["email"] ASSIGN(STRING("nikos@example.com"));

    // Prosthesi pinakon mathimatwn sto proto antikeimeno
    SET(students)[0]["grades"] ASSIGN(ARRAY()); // Dimiourgia pinaka
    SET(students)[0]["grades"] APPEND(
        OBJECT({KEY("hy255"), NUMBER(9)}),
        OBJECT({KEY("hy200"), NUMBER(8)})
    );

    // Ektypwsi tou ananeomenou JSON pinaka
    std::cout << std::endl;
    std::cout << "Updated Students: ";
    students->print();
    std::cout << std::endl;

    // Orismos enos JSON antikeimenou vivliou
    JSON(book) = OBJECT(
        {KEY("title"), STRING("Gone Girl")},
        {KEY("type"), STRING("Thriller")},
        {KEY("author"), OBJECT(
            {KEY("firstname"), STRING("GILLIAN")},
            {KEY("sirname"), STRING("FLYNN")},
            {KEY("age"), NUMBER(45)}
        )}
    );

    // Ektypwsi arxikou vivliou
    std::cout << "Original Book: ";
    book->print();
    std::cout << std::endl;

    // Diagrafi kleidiou "age" apo to antikeimeno "author" tou vivliou
    ERASE(book,"author","age");

    // Diagrafi tou kleidiou "type" apo to vivlio
    ERASE(book,"type");

    // Diagrafi olwn ton dedomenon tou vivliou
    ERASE(book);

    // Ektypwsi tou vivliou meta tis diagrafes
    std::cout << "Book after ERASE operations: ";
    book->print(); // Tha prepei na emfanistei adio antikeimeno
    std::cout << std::endl;

    return 0;
}
