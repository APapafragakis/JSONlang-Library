#include "JSONlang.h"

int main() {
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
