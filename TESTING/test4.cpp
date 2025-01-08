#include "JSONlang.h"

PROGRAM_BEGIN
    // Orismos JSON metabliton gia dokimes
    JSON(non_empty_object) = OBJECT({
        {KEY(name), STRING("John")},
        {KEY(age), NUMBER(25)}
    });
    JSON(non_empty_array) = ARRAY({NUMBER(10), NUMBER(20), NUMBER(30)});
    JSON(single_value_string) = STRING("Hello");
    JSON(single_value_number) = NUMBER(100);
    JSON(single_value_boolean) = BOOLEAN(true);

    // Dokimi SIZE_OF
    std::cout << "Testing SIZE_OF:" << std::endl;
    std::cout << "Size of non-empty object: " << SIZE_OF(non_empty_object) << std::endl;  // 2
    std::cout << "Size of non-empty array: " << SIZE_OF(non_empty_array) << std::endl;  // 3
    std::cout << "Size of single value (string): " << SIZE_OF(single_value_string) << std::endl;  // 1
    std::cout << "Size of single value (number): " << SIZE_OF(single_value_number) << std::endl;  // 1
    std::cout << "Size of single value (boolean): " << SIZE_OF(single_value_boolean) << std::endl;  // 1

    // Dokimi IS_EMPTY
    std::cout << "\nTesting IS_EMPTY:" << std::endl;
    std::cout << "Is non-empty object empty? " << (IS_EMPTY(non_empty_object) ? "true" : "false") << std::endl;  // false
    std::cout << "Is non-empty array empty? " << (IS_EMPTY(non_empty_array) ? "true" : "false") << std::endl;  // false
    std::cout << "Is single value (string) empty? " << (IS_EMPTY(single_value_string) ? "true" : "false") << std::endl;  // false
    std::cout << "Is single value (number) empty? " << (IS_EMPTY(single_value_number) ? "true" : "false") << std::endl;  // false
    std::cout << "Is single value (boolean) empty? " << (IS_EMPTY(single_value_boolean) ? "true" : "false") << std::endl;  // false

    // Dokimi HAS_KEY
    std::cout << "\nTesting HAS_KEY:" << std::endl;
    std::cout << "Does non-empty object have key 'name'? " << (HAS_KEY(non_empty_object, "name") ? "true" : "false") << std::endl;  // true
    std::cout << "Does single value (string) have key 'name'? " << (HAS_KEY(single_value_string, "name") ? "true" : "false") << std::endl;  // false

    // Dokimi TYPE_OF
    std::cout << "\nTesting TYPE_OF:" << std::endl;
    std::cout << "Type of non-empty object: " << TYPE_OF(non_empty_object) << std::endl;  // object
    std::cout << "Type of non-empty array: " << TYPE_OF(non_empty_array) << std::endl;  // array
    std::cout << "Type of single value (string): " << TYPE_OF(single_value_string) << std::endl;  // string
    std::cout << "Type of single value (number): " << TYPE_OF(single_value_number) << std::endl;  // number
    std::cout << "Type of single value (boolean): " << TYPE_OF(single_value_boolean) << std::endl;  // boolean

PROGRAM_END