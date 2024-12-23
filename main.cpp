#include "JSONlang.h"

int main() {
    // Arithmetic operations
    auto sum = NUMBER(10) + NUMBER(5);         // 10 + 5 = 15
    auto diff = NUMBER(10) - NUMBER(5);        // 10 - 5 = 5
    auto prod = NUMBER(10) * NUMBER(5);        // 10 * 5 = 50
    auto quotient = NUMBER(10) / NUMBER(5);    // 10 / 5 = 2
    auto mod = NUMBER(10) % NUMBER(3);         // 10 % 3 = 1

    // Print arithmetic results
    std::cout << "Arithmetic operations:\n";
    std::cout << "10 + 5 = "; 
    sum->print();  // Expected Output: 15
    std::cout << "\n10 - 5 = "; 
    diff->print(); // Expected Output: 5
    std::cout << "\n10 * 5 = "; 
    prod->print(); // Expected Output: 50
    std::cout << "\n10 / 5 = "; 
    quotient->print(); // Expected Output: 2
    std::cout << "\n10 % 3 = "; 
    mod->print(); // Expected Output: 1
    std::cout << std::endl;  // Adding an extra line break for clarity

    // Relational operations
    auto result1 = NUMBER(10) > NUMBER(5);     // true
    auto result2 = NUMBER(10) < NUMBER(5);     // false
    auto result3 = NUMBER(10) >= NUMBER(10);   // true
    auto result4 = NUMBER(10) <= NUMBER(5);    // false

    // Print relational results
    std::cout << "Relational operations:\n";
    std::cout << "10 > 5: ";
    std::cout << std::boolalpha << result1;  // Expected Output: true
    std::cout << "\n10 < 5: ";
    std::cout << std::boolalpha << result2;  // Expected Output: false
    std::cout << "\n10 >= 10: ";
    std::cout << std::boolalpha << result3;  // Expected Output: true
    std::cout << "\n10 <= 5: ";
    std::cout << std::boolalpha << result4;  // Expected Output: false
    std::cout << std::endl;

    // Logical operations
    auto andResult = BOOLEAN(true) && BOOLEAN(false);  // true && false = false
    auto orResult = BOOLEAN(true) || BOOLEAN(false);   // true || false = true
    auto notResult = !BOOLEAN(true);                    // !true = false

    // Print logical results
    std::cout << "Logical operations:\n";
    std::cout << "true && false: ";
    std::cout << std::boolalpha << andResult << std::endl;  // Expected Output: false
    std::cout << "true || false: ";
    std::cout << std::boolalpha << orResult << std::endl;   // Expected Output: true
    std::cout << "!true: ";
    std::cout << std::boolalpha << notResult << std::endl;  // Expected Output: false
    std::cout << std::endl;

    // Array concatenation
    auto array1 = ARRAY(NUMBER(1), NUMBER(2));
    auto array2 = ARRAY(NUMBER(3), NUMBER(4));
    auto arrayConcat = ARRAY(NUMBER(1), NUMBER(2)) + ARRAY(NUMBER(3), NUMBER(4));  // [1, 2] + [3, 4] = [1, 2, 3, 4]

    // Print array concatenation result
    std::cout << "Array concatenation (ARRAY[NUMBER(1), NUMBER(2)] + ARRAY[NUMBER(3), NUMBER(4)]) = ";
    arrayConcat->print();  // Expected Output: [1, 2, 3, 4]
    std::cout << std::endl;

    // String concatenation
    auto str1 = STRING("hello");
    auto str2 = STRING(" world");
    auto strConcat = STRING("hello") + STRING(" world");  // "hello" + " world" = "hello world"

    // Print string concatenation result
    std::cout << "String concatenation (STRING(\"hello\") + STRING(\" world\")) = ";
    strConcat->print();  // Expected Output: "hello world"
    std::cout << std::endl;

    // Object concatenation
    auto obj1_1 = OBJECT({ "key1", NUMBER(1) });
    auto obj2_1 = OBJECT({ "key2", NUMBER(2) });
    auto objConcat = OBJECT({ "key1", NUMBER(1) }) + OBJECT({ "key2", NUMBER(2) });  // Merging two objects

    // Print object concatenation result
    std::cout << "Object concatenation (OBJECT({\"key1\", NUMBER(1)}) + OBJECT({\"key2\", NUMBER(2)})) = ";
    objConcat->print();  // Expected Output: {"key1": 1, "key2": 2}
    std::cout << std::endl;

    // Create JSON Arrays
    JSON(arr1) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr2) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr3) = ARRAY(NUMBER(42), STRING("World"));

    // Create JSON Objects with a simpler syntax like the array way
    JSON(obj1_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj2_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj3_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("World") });

    // Print results of array comparisons
    std::cout << "Array comparisons:\n";
    std::cout << "arr1 == arr2: " << (*arr1 == *arr2 ? "true" : "false") << std::endl;  // Expected output: true
    std::cout << "arr1 != arr3: " << (*arr1 != *arr3 ? "true" : "false") << std::endl;  // Expected output: true

    // Print results of object comparisons
    std::cout << "Object comparisons:\n";
    std::cout << "obj1_2 == obj2_2: " << (*obj1_2 == *obj2_2 ? "true" : "false") << std::endl;  // Expected output: true
    std::cout << "obj1_2 != obj3_2: " << (*obj1_2 != *obj3_2 ? "true" : "false") << std::endl;  // Expected output: true

    return 0;
}
