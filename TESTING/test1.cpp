#include "JSONlang.h"

PROGRAM_BEGIN
    // Keno antikeimeno
    JSON(emptyObj) = OBJECT({});

    // Keno pinakas
    JSON(emptyArray) = ARRAY({});

    // Arithmos
    JSON(someNumber) = NUMBER(42);

    // Timi true kai false
    JSON(isTrue) = BOOLEAN(true);
    JSON(isFalse) = BOOLEAN(false);

    // Null timi
    JSON(nothing) = NULL_VALUE;

    // Vivlio me emnestedha stoixeia
    JSON(book) = OBJECT({
        {KEY("title"), STRING("Gone Girl")},
        {KEY("published"), NUMBER(2012)},
        {KEY("type"), STRING("Thriller")},
        {KEY("author"), OBJECT({
            {KEY("firstname"), STRING("GILLIAN")},
            {KEY("sirname"), STRING("FLYNN")},
            {KEY("age"), NUMBER(45)},
            {KEY("books_written"), ARRAY({
                STRING("Sharp Objects"),
                STRING("Dark Places")
            })}
        })},
        {KEY("genres"), ARRAY({
            STRING("Fiction"),
            STRING("Thriller"),
            STRING("Crime")
        })}
    });

    // Ebdomadiaies thermokrasies
    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

    // Lista fititon
    JSON(students) = ARRAY({
        OBJECT({
            {KEY("name"), STRING("Nikos Nikolaou")},
            {KEY("id"), NUMBER(4444)},
            {KEY("grades"), ARRAY({
                OBJECT({{KEY("subject"), STRING("hy100")}, {KEY("grade"), NUMBER(7.5)}}),
                OBJECT({{KEY("subject"), STRING("hy150")}, {KEY("grade"), NUMBER(8)}})
            })},
            {KEY("courses"), ARRAY({STRING("CS101"), STRING("CS102")})}
        }),
        OBJECT({
            {KEY("name"), STRING("Maria Papadopoulou")},
            {KEY("id"), NUMBER(4445)},
            {KEY("grades"), ARRAY({
                OBJECT({{KEY("subject"), STRING("hy100")}, {KEY("grade"), NUMBER(6)}}),
                OBJECT({{KEY("subject"), STRING("hy150")}, {KEY("grade"), NUMBER(7.5)}})
            })},
            {KEY("courses"), ARRAY({STRING("CS101"), STRING("CS201")})}
        })
    });

    // Ektypwsi JSON antikeimenwn
    PRINT(emptyObj);
    PRINT(emptyArray);
    PRINT(someNumber);
    PRINT(isTrue);
    PRINT(isFalse);
    PRINT(nothing);
    PRINT(book);
    PRINT(week_temperatures);
    PRINT(students);

PROGRAM_END