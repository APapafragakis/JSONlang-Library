#include "JSONlang.h"

int main() {
    // Declare JSON variables with unique names
    JSON(array1) = ARRAY(NUMBER(1), NUMBER(2), STRING("Hello"));
    JSON(object1) = OBJECT({"key1", STRING("value1")}, {"key2", NUMBER(42)});
    JSON(string1) = STRING("Hello");

    std::cout << "Array size: " << array1->size() << std::endl; // Output: 3
    std::cout << "Object size: " << object1->size() << std::endl; // Output: 2
    std::cout << "String size: " << string1->size() << std::endl; // Output: 1

    JSON(emptyArray1) = ARRAY();
    JSON(nonEmptyArray1) = ARRAY(NUMBER(1), STRING("Test"));
    JSON(emptyObject1) = OBJECT();
    JSON(nonEmptyObject1) = OBJECT({"key1", STRING("value")});
    JSON(string2) = STRING("World");

    std::cout << "emptyArray1 is empty: " << (IS_EMPTY(emptyArray1) ? "true" : "false") << std::endl;  // Output: true
    std::cout << "nonEmptyArray1 is empty: " << (IS_EMPTY(nonEmptyArray1) ? "true" : "false") << std::endl; // Output: false
    std::cout << "emptyObject1 is empty: " << (IS_EMPTY(emptyObject1) ? "true" : "false") << std::endl; // Output: true
    std::cout << "nonEmptyObject1 is empty: " << (IS_EMPTY(nonEmptyObject1) ? "true" : "false") << std::endl; // Output: false
    std::cout << "string2 is empty: " << (IS_EMPTY(string2) ? "true" : "false") << std::endl; // Output: false

    JSON(object2) = OBJECT({"key1", STRING("value1")}, {"key2", NUMBER(42)});
    JSON(emptyObject2) = OBJECT();
    JSON(array2) = ARRAY(NUMBER(1), STRING("Test"));
    JSON(string3) = STRING("Hello again");

    // Test HAS_KEY macro and output results directly
    std::cout << "object2 has key 'key1': " << (HAS_KEY(object2, "key1") ? "true" : "false") << std::endl;
    std::cout << "object2 has key 'key3': " << (HAS_KEY(object2, "key3") ? "true" : "false") << std::endl;
    std::cout << "emptyObject2 has key 'key1': " << (HAS_KEY(emptyObject2, "key1") ? "true" : "false") << std::endl;
    std::cout << "array2 has key 'key1': " << (HAS_KEY(array2, "key1") ? "true" : "false") << std::endl;
    std::cout << "string3 has key 'key1': " << (HAS_KEY(string3, "key1") ? "true" : "false") << std::endl;

    JSON(string4) = STRING("Final String");
    JSON(number1) = NUMBER(42);
    JSON(boolean1) = BOOLEAN(true);
    JSON(object3) = OBJECT({"key1", STRING("value1")});
    JSON(array3) = ARRAY(NUMBER(1), STRING("Test"));

    // Test TYPE_OF macro
    std::cout << "Type of string4: " << TYPE_OF(string4) << std::endl; // Output: string
    std::cout << "Type of number1: " << TYPE_OF(number1) << std::endl; // Output: number
    std::cout << "Type of boolean1: " << TYPE_OF(boolean1) << std::endl; // Output: boolean
    std::cout << "Type of object3: " << TYPE_OF(object3) << std::endl; // Output: object
    std::cout << "Type of array3: " << TYPE_OF(array3) << std::endl; // Output: array

    return 0;
}
