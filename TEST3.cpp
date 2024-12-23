#include "JSONlang.h"

int main() {
    // Arithmetic operations
    auto sum = NUMBER(10) + NUMBER(5);         // 10 + 5 = 15
    auto diff = NUMBER(10) - NUMBER(5);        // 10 - 5 = 5
    auto prod = NUMBER(10) * NUMBER(5);        // 10 * 5 = 50
    auto quotient = NUMBER(10) / NUMBER(5);    // 10 / 5 = 2
    auto mod = NUMBER(10) % NUMBER(3);         // 10 % 3 = 1

    // Relational operations
    auto result1 = NUMBER(10) > NUMBER(5);     // true
    auto result2 = NUMBER(10) < NUMBER(5);     // false
    auto result3 = NUMBER(10) >= NUMBER(10);   // true
    auto result4 = NUMBER(10) <= NUMBER(5);    // false

    // Array concatenation (special case for +)
    auto array1 = ARRAY(NUMBER(1), NUMBER(2));
    auto array2 = ARRAY(NUMBER(3), NUMBER(4));
    auto arrayConcat = ARRAY(NUMBER(1), NUMBER(2)) + ARRAY(NUMBER(3), NUMBER(4));  // [1, 2] + [3, 4] = [1, 2, 3, 4]

    // String concatenation (special case for +)
    auto str1 = STRING("hello");
    auto str2 = STRING(" world");
    auto strConcat =  STRING("hello") + STRING(" world");      // "hello" + " world" = "hello world"

    // Object concatenation (special case for +)
    auto obj1 = OBJECT({"key1", NUMBER(1)});
    auto obj2 = OBJECT({"key2", NUMBER(2)});
    auto objConcat = OBJECT({"key1", NUMBER(1)}) + OBJECT({"key2", NUMBER(2)});     // Merging two objects

    // Print arithmetic results
    std::cout << "Arithmetic operations:\n";
    std::cout << "10 + 5 = "; 
    sum->print();  // Output: 15
    std::cout << "\n10 - 5 = "; 
    diff->print(); // Output: 5
    std::cout << "\n10 * 5 = "; 
    prod->print(); // Output: 50
    std::cout << "\n10 / 5 = "; 
    quotient->print(); // Output: 2
    std::cout << "\n10 % 3 = "; 
    mod->print(); // Output: 1

    // Print relational results
    std::cout << "\nRelational operations:\n";
    std::cout << "10 > 5: ";
    std::cout << std::boolalpha << result1;  // Output: true
    std::cout << "\n10 < 5: ";
    std::cout << std::boolalpha << result2;  // Output: false
    std::cout << "\n10 >= 10: ";
    std::cout << std::boolalpha << result3;  // Output: true
    std::cout << "\n10 <= 5: ";
    std::cout << std::boolalpha << result4;  // Output: false

    // Print array concatenation result
    std::cout << "Array concatenation (ARRAY[NUMBER(1), NUMBER(2)] + ARRAY[NUMBER(3), NUMBER(4)]) = ";
    arrayConcat->print();  // Expected Output: [1, 2, 3, 4]

    // Print string concatenation result
    std::cout << "\nString concatenation (STRING(\"hello\") + STRING(\" world\")) = ";
    strConcat->print();  // Expected Output: "hello world"

    // Print object concatenation result
    std::cout << "\nObject concatenation (OBJECT({\"key1\", NUMBER(1)}) + OBJECT({\"key2\", NUMBER(2)})) = ";
    objConcat->print();  // Expected Output: {"key1": 1, "key2": 2}

    return 0;
}
