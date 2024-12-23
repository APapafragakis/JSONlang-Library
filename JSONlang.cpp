#include "JSONlang.h"

// JsonString Implementation
JsonString::JsonString(const std::string& val) : value(val) {}

void JsonString::print() const {
    std::cout << "\"" << value << "\"";
}

// JsonNumber Implementation
JsonNumber::JsonNumber(double val) : value(val) {}

void JsonNumber::print() const {
    std::cout << value;
}

// Overload arithmetic operators for JsonNumber
std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() + num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

std::shared_ptr<JsonValue> operator-(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() - num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

std::shared_ptr<JsonValue> operator*(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() * num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

std::shared_ptr<JsonValue> operator/(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        if (num_rhs->getValue() == 0) {
            throw std::runtime_error("Division by zero.");
        }
        return std::make_shared<JsonNumber>(num_lhs->getValue() / num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

// JsonObject Implementation
JsonObject::JsonObject() = default;

JsonObject::JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init) : keyValues(init) {}

void JsonObject::set(const std::string& key, std::shared_ptr<JsonValue> value) {
    for (auto& pair : keyValues) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    keyValues.emplace_back(key, value);
}

std::shared_ptr<JsonValue>& JsonObject::get(const std::string& key) {
    for (auto& pair : keyValues) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::runtime_error("Key not found: " + key);
}

void JsonObject::erase(const std::string& key) {
    auto it = std::remove_if(keyValues.begin(), keyValues.end(),
        [&key](const std::pair<std::string, std::shared_ptr<JsonValue>>& pair) {
            return pair.first == key;
        });
    if (it != keyValues.end()) {
        keyValues.erase(it, keyValues.end());
    }
}

void JsonObject::erase() {
    keyValues.clear();
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

// JsonArray Implementation
JsonArray::JsonArray() = default;

JsonArray::JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init) : values(init) {}

void JsonArray::append(std::shared_ptr<JsonValue> value) {
    values.push_back(value);
}

void JsonArray::erase(size_t index) {
    if (index < values.size()) {
        values.erase(values.begin() + index);
    } else {
        throw std::runtime_error("Index out of range for erase operation.");
    }
}

void JsonArray::erase() {
    values.clear();
}

void JsonArray::print() const {
    std::cout << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) std::cout << ", ";
        values[i]->print();
    }
    std::cout << "]";
}

size_t JsonArray::size() const {
    return values.size();
}

// ERASE Implementation
void ERASE(std::shared_ptr<JsonValue> target) {
    target->erase();
}

void ERASE(std::shared_ptr<JsonValue> target, const std::string& key) {
    auto obj = std::dynamic_pointer_cast<JsonObject>(target);
    if (!obj) {
        throw std::runtime_error("Target is not a JSON object.");
    }
    obj->erase(key);
}
