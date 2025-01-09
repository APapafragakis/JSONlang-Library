#include "JSONlang.h"

PROGRAM_BEGIN
    try {
        // Dimiourgia arxikon dedomenon JSON
        JSON(week_temperatures) = ARRAY({
            NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
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

        JSON(book) = OBJECT({
            {KEY(title), STRING("Gone Girl")},
            {KEY(published), NUMBER(2012)},
            {KEY(type), STRING("Thriller")},
            {KEY(author), OBJECT({
                {KEY(first_name), STRING("GILLIAN")},
                {KEY(last_name), STRING("FLYNN")},
                {KEY(age), NUMBER(45)}
            })}
        });

        // --- SET kai ASSIGN ---
        std::cout << "Testing SET and ASSIGN..." << std::endl;
        // Allagi timis stis week_temperatures
        SET(week_temperatures)[2] ASSIGN NUMBER(22);  // Allagi thermokrasias 3is meras se 22
        // Prostiki email ston proto fititi
        SET(students)[0]["email"] ASSIGN STRING("nikos@university.edu");
        // Allagi titlou vivliou
        SET(book)["title"] ASSIGN STRING("Gone Girl: Revised Edition");
        std::cout << "After SET and ASSIGN:" << std::endl;
        PRINT(week_temperatures);
        PRINT(students);
        PRINT(book);

        // --- APPEND ---
        try {
            std::cout << "Appending to week_temperatures" << std::endl;
            SET(week_temperatures).APPEND(NUMBER(23), NUMBER(22), NUMBER(20)); // appends values to week_temperatures
            std::cout << "Appending to students[0][\"grades\"]" << std::endl;
            std::cout << "Type of students[0][\"grades\"]: " << TYPE_OF(ACCESS(students)[0]["grades"]) << std::endl;
            SET(students)[0]["grades"].APPEND(OBJECT({KEY(hy255), NUMBER(9)})); // appends a grade for course hy255
        } catch (const std::runtime_error& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        // --- ERASE ---
        std::cout << "Testing ERASE..." << std::endl;
        // Diagrafi tou pediou "type" apo to vivlio
        ERASE(ACCESS(book)["type"]);
        // Diagrafi tis telefteas thermokrasias ston pinaka
        ERASE(ACCESS(week_temperatures)[SIZE_OF(week_temperatures) - 1]);
        // Diagrafi oloklirou tou pinaka grades gia ton proto fititi
        ERASE(ACCESS(students)[0]["grades"]);
        std::cout << "After ERASE:" << std::endl;
        PRINT(week_temperatures);
        PRINT(students);
        PRINT(book);


    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

PROGRAM_END
