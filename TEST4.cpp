#include "JSONlang.h"
#include <iostream>

int main() {
    JSON(myArray) = ARRAY(NUMBER(1), NUMBER(2), STRING("Hello"));
    JSON(myObject) = OBJECT({"key1", STRING("value1")}, {"key2", NUMBER(42)});
    JSON(myString) = STRING("Hello");

    std::cout << "Array size: " << myArray->size() << std::endl; // Output: 3
    std::cout << "Object size: " << myObject->size() << std::endl; // Output: 2
    std::cout << "String size: " << myString->size() << std::endl; // Output: 1

    JSON(emptyArray) = ARRAY();
    JSON(nonEmptyArray) = ARRAY(NUMBER(1), STRING("Test"));
    JSON(emptyObject) = OBJECT();
    JSON(nonEmptyObject) = OBJECT({"key1", STRING("value")});
    JSON(myString) = STRING("Hello");

    std::cout << "emptyArray is empty: " << (IS_EMPTY(emptyArray) ? "true" : "false") << std::endl;  // Output: true
    std::cout << "nonEmptyArray is empty: " << (IS_EMPTY(nonEmptyArray) ? "true" : "false") << std::endl; // Output: false
    std::cout << "emptyObject is empty: " << (IS_EMPTY(emptyObject) ? "true" : "false") << std::endl; // Output: true
    std::cout << "nonEmptyObject is empty: " << (IS_EMPTY(nonEmptyObject) ? "true" : "false") << std::endl; // Output: false
    std::cout << "myString is empty: " << (IS_EMPTY(myString) ? "true" : "false") << std::endl; // Output: false

    JSON(myObject) = OBJECT({"key1", STRING("value1")}, {"key2", NUMBER(42)});
    JSON(emptyObject) = OBJECT();
    JSON(myArray) = ARRAY(NUMBER(1), STRING("Test"));
    JSON(myString) = STRING("Hello");

    // Test HAS_KEY macro and output results directly
    std::cout << "myObject has key 'key1': " << (HAS_KEY(myObject, "key1") ? "true" : "false") << std::endl;
    std::cout << "myObject has key 'key3': " << (HAS_KEY(myObject, "key3") ? "true" : "false") << std::endl;
    std::cout << "emptyObject has key 'key1': " << (HAS_KEY(emptyObject, "key1") ? "true" : "false") << std::endl;
    std::cout << "myArray has key 'key1': " << (HAS_KEY(myArray, "key1") ? "true" : "false") << std::endl;
    std::cout << "myString has key 'key1': " << (HAS_KEY(myString, "key1") ? "true" : "false") << std::endl;

    JSON(myString) = STRING("Hello");
    JSON(myNumber) = NUMBER(42);
    JSON(myBoolean) = BOOLEAN(true);
    JSON(myObject) = OBJECT({"key1", STRING("value1")});
    JSON(myArray) = ARRAY(NUMBER(1), STRING("Test"));

    // Test TYPE_OF macro
    std::cout << "Type of myString: " << TYPE_OF(myString) << std::endl; // Output: string
    std::cout << "Type of myNumber: " << TYPE_OF(myNumber) << std::endl; // Output: number
    std::cout << "Type of myBoolean: " << TYPE_OF(myBoolean) << std::endl; // Output: boolean
    std::cout << "Type of myObject: " << TYPE_OF(myObject) << std::endl; // Output: object
    std::cout << "Type of myArray: " << TYPE_OF(myArray) << std::endl; // Output: array

    return 0;
}
