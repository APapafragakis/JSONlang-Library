#include "JSONlang.h"

// JsonString
JsonString::JsonString(const std::string& val) : value(val) {}

void JsonString::print() const {
    std::cout << "\"" << value << "\"";
}

// JsonNumber
JsonNumber::JsonNumber(double val) : value(val) {}

void JsonNumber::print() const {
    std::cout << value;
}

// JsonBoolean
JsonBoolean::JsonBoolean(bool val) : value(val) {}

void JsonBoolean::print() const {
    std::cout << (value ? "true" : "false");
}

// JsonNull
void JsonNull::print() const {
    std::cout << "null";
}

// JsonObject
JsonObject::JsonObject() = default;

JsonObject::JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init) : keyValues(init) {}

void JsonObject::add(const std::string& key, std::shared_ptr<JsonValue> value) {
    for (auto& pair : keyValues) {
        if (pair.first == key) {
            pair.second = value; // Replace the value if the key exists
            return;
        }
    }
    keyValues.emplace_back(key, value); // Add a new key-value pair
}

void JsonObject::print() const {
    std::cout << "{";
    for (size_t i = 0; i < keyValues.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "\"" << keyValues[i].first << "\": ";
        keyValues[i].second->print();
    }
    std::cout << "}";
}

// JsonArray
JsonArray::JsonArray() = default;

JsonArray::JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init) : values(init) {}

void JsonArray::add(std::shared_ptr<JsonValue> value) {
    values.push_back(value);
}

void JsonArray::print() const {
    std::cout << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) std::cout << ", ";
        values[i]->print();
    }
    std::cout << "]";
}
