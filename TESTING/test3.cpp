#include "JSONlang.h"

PROGRAM_BEGIN
    
    // Arithmetic operations
    JSON(sum1) = NUMBER(11) + NUMBER(5);
    JSON(diff) = NUMBER(10) - NUMBER(5);
    JSON(prod) = NUMBER(10) * NUMBER(5);
    JSON(quot1) = NUMBER(10) / NUMBER(5);
    JSON(mod) = *NUMBER(10) % *NUMBER(3);

    std::cout << "Arithmetic operations:\n";
    std::cout << "10 + 5 = ";
    PRINT(sum1);
    std::cout << "10 - 5 = ";
    PRINT(diff);
    std::cout << "10 * 5 = ";
    PRINT(prod);
    std::cout << "10 / 5 = ";
    PRINT(quot1);
    std::cout << "10 % 3 = ";
    PRINT(mod);
    std::cout << std::endl;

    // JSON for weekly temperatures
    JSON(week_temperatures) = ARRAY({
        NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
        NUMBER(19), NUMBER(18.5), NUMBER(19)
    });

    // JSON for students and grades
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

    // JSON for HY352 with exam and project grades
    JSON(hy352_nik) = OBJECT({
        {KEY(examination), NUMBER(7)},
        {KEY(project), NUMBER(8)}
    });

    // String concatenation
    JSON(fullName) = STRING("Nikos") + STRING(" Nikolaou");
    std::cout << "Concatenated string: ";
    PRINT(fullName);

    // Array concatenation
    JSON(array1) = ARRAY({NUMBER(1), NUMBER(2)});
    JSON(array2) = ARRAY({NUMBER(3), NUMBER(4)});
    JSON(combinedArray) = array1 + array2;
    std::cout << "Concatenated array: ";
    PRINT(combinedArray);

    // Arithmetic operations with new variables
    JSON(num1) = NUMBER(15);
    JSON(num2) = NUMBER(4);

    JSON(sum2) = num1 + num2;  // New variable for sum
    JSON(difference) = num1 - num2;
    JSON(product) = num1 * num2;
    JSON(quot2) = num1 / num2;  // New variable for quotient

    std::cout << "Arithmetic Operations:" << std::endl;
    PRINT(sum2);
    PRINT(difference);
    PRINT(product);
    PRINT(quot2);

    // Logical operations
    JSON(bool1) = BOOLEAN(true);
    JSON(bool2) = BOOLEAN(false);
    JSON(andResult) = bool1 && bool2;
    JSON(orResult) = bool1 || bool2;

    std::cout << "Logical Operations:" << std::endl;
    PRINT(andResult); 
    PRINT(orResult);  

    // Comparisons
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

    // Final grade calculation for HY352
    auto obj = std::dynamic_pointer_cast<JsonObject>(hy352_nik);
    JSON(final_grade) = 
        std::dynamic_pointer_cast<JsonNumber>(obj->get("examination")) * NUMBER(0.75) + 
        std::dynamic_pointer_cast<JsonNumber>(obj->get("project")) * NUMBER(0.25);
    
    std::cout << "Final grade: ";
    PRINT(final_grade);

    // Add student with calculated grade
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

PROGRAM_END
