#include "JSONlang.h"

PROGRAM_BEGIN

    // Orismos JSON gia ena vivlio
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

    // Orismos JSON gia thermokrasies ebdomadas
    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

    // Orismos JSON gia fitites kai bathmous
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

    // Orismos JSON gia to hy352 me eksetasi kai project
    JSON(hy352_nik) = OBJECT({
        {KEY(examination), NUMBER(7)},
        {KEY(project), NUMBER(8)}
    });

    // Dokimi sunenosis string
    JSON(fullName) = STRING("Nikos") + STRING(" Nikolaou");
    std::cout << "Concatenated string: ";
    PRINT(fullName);

    // Dokimi sunenosis pinaka
    JSON(array1) = ARRAY({NUMBER(1), NUMBER(2)});
    JSON(array2) = ARRAY({NUMBER(3), NUMBER(4)});
    JSON(combinedArray) = array1 + array2;
    std::cout << "Concatenated array: ";
    PRINT(combinedArray);

    // Dokimi arithmitikon praxewn (+, -, *, /)
    JSON(num1) = NUMBER(15);
    JSON(num2) = NUMBER(4);

    JSON(sum) = num1 + num2;
    JSON(difference) = num1 - num2;
    JSON(product) = num1 * num2;
    JSON(quotient) = num1 / num2;

    std::cout << "Arithmetic Operations:" << std::endl;
    PRINT(sum);
    PRINT(difference);
    PRINT(product);
    PRINT(quotient);

    // Logikes praxeis (&&, ||)
    JSON(bool1) = BOOLEAN(true);
    JSON(bool2) = BOOLEAN(false);
    JSON(andResult) = bool1 && bool2;
    JSON(orResult) = bool1 || bool2;

    std::cout << "Logical Operations:" << std::endl;
    PRINT(andResult); 
    PRINT(orResult);  

    // Sugkriseis (> < >= <=)
    if (*num1 > *num2) {
        std::cout << "15 is greater than 4" << std::endl;
    }
    if (*num1 >= *num2) {
        std::cout << "15 is greater than or equal to 4" << std::endl;
    }
    if (*num2 < *num1) {
        std::cout << "4 is less than 15" << std::endl;
    }
    if (*num2 <= *num1) {
        std::cout << "4 is less than or equal to 15" << std::endl;
    }

    // Ypologismos telikou bathmou gia to hy352
    auto obj = std::dynamic_pointer_cast<JsonObject>(hy352_nik);
    JSON(final_grade) = 
        std::dynamic_pointer_cast<JsonNumber>(obj->get("examination")) * NUMBER(0.75) + 
        std::dynamic_pointer_cast<JsonNumber>(obj->get("project")) * NUMBER(0.25);
    
    std::cout << "Final grade: ";
    PRINT(final_grade);

    // Prosthiki fititi me ypologismeno bathmo
    JSON(student_with_grade) = ARRAY({
        OBJECT({
            {KEY(name), STRING("Nikos") + STRING(" Nikolaou")},
            {KEY(id), NUMBER(4444)},
            {KEY(grades), ARRAY({
                OBJECT({
                    {KEY(hy352), 
                        std::dynamic_pointer_cast<JsonNumber>(obj->get("examination")) * NUMBER(0.75) + 
                        std::dynamic_pointer_cast<JsonNumber>(obj->get("project")) * NUMBER(0.25)
                    }
                })
            })}
        })
    });

    std::cout << "Student with calculated grade: ";
    PRINT(student_with_grade);

    // Ektypwsi JSON gia to vivlio
    PRINT(book);

PROGRAM_END