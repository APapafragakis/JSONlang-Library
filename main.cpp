#include "JSONlang.h"

int main() {
    // Test with JsonArray
    auto array_result = ARRAY(NUMBER(1), NUMBER(2)) + ARRAY(NUMBER(3), NUMBER(4));
    std::cout << "JsonArray Tests:\n";
    array_result->print(); // Should print [1, 2, 3, 4]
    std::cout << "\n";

    // Test with JsonObject
    auto object_result = OBJECT({"key1", NUMBER(1)}, {"key2", STRING("value2")}) +
                         OBJECT({"key3", NUMBER(3)}, {"key4", STRING("value4")});
    std::cout << "\nJsonObject Tests:\n";
    object_result->print(); // Should print {"key1": 1, "key2": "value2", "key3": 3, "key4": "value4"}
    std::cout << "\n";

    return 0;
}
