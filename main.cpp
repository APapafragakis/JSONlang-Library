#include "JSONlang.h"

int main() {
    // Test with JsonString
    auto str_result = STRING("hello") + STRING(" world"); // Concatenate strings
    std::cout << "String Concatenation: ";
    str_result->print(); // Should print "hello world"
    std::cout << "\n";

    return 0;
}
