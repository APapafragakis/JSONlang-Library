#include "JSONlang.h"

JsonBoolean::JsonBoolean(bool val) : value(val) {}

void JsonBoolean::print() const {
    std::cout << (value ? "true" : "false");
}

bool JsonBoolean::getValue() const {
    return value;
}

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


std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    // Handle JsonNumber addition
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() + num_rhs->getValue());
    }

    // Handle JsonString concatenation
    auto str_lhs = std::dynamic_pointer_cast<JsonString>(lhs);
    auto str_rhs = std::dynamic_pointer_cast<JsonString>(rhs);
    if (str_lhs && str_rhs) {
        return std::make_shared<JsonString>(str_lhs->getValue() + str_rhs->getValue());
    }

    // Handle JsonArray concatenation
    auto arr_lhs = std::dynamic_pointer_cast<JsonArray>(lhs);
    auto arr_rhs = std::dynamic_pointer_cast<JsonArray>(rhs);
    if (arr_lhs && arr_rhs) {
        auto result = std::make_shared<JsonArray>();
        for (const auto& val : arr_lhs->getValues()) {
            result->append(val);
        }
        for (const auto& val : arr_rhs->getValues()) {
            result->append(val);
        }
        return result;
    }

    // Handle JsonObject merging
    auto obj_lhs = std::dynamic_pointer_cast<JsonObject>(lhs);
    auto obj_rhs = std::dynamic_pointer_cast<JsonObject>(rhs);
    if (obj_lhs && obj_rhs) {
        auto result = std::make_shared<JsonObject>();
        for (const auto& pair : obj_lhs->getKeyValues()) {
            result->set(pair.first, pair.second);
        }
        for (const auto& pair : obj_rhs->getKeyValues()) {
            result->set(pair.first, pair.second);
        }
        return result;
    }

    // If types don't match, throw an error
    throw std::runtime_error("Unsupported types for operator+");
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

std::shared_ptr<JsonValue> operator%(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        if (static_cast<int>(num_lhs->getValue()) != num_lhs->getValue() || 
            static_cast<int>(num_rhs->getValue()) != num_rhs->getValue()) {
            throw std::runtime_error("Modulus operator requires integer values.");
        }
        return std::make_shared<JsonNumber>(static_cast<int>(num_lhs->getValue()) % static_cast<int>(num_rhs->getValue()));
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

#include "JSONlang.h"

// Greater than operator '>'
std::shared_ptr<JsonValue> operator>(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() > num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Less than operator '<'
std::shared_ptr<JsonValue> operator<(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() < num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Greater than or equal to operator '>='
std::shared_ptr<JsonValue> operator>=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() >= num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Less than or equal to operator '<='
std::shared_ptr<JsonValue> operator<=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() <= num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
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

// Implement logical AND (&&) for JsonBoolean
std::shared_ptr<JsonValue> JsonBoolean::operator&&(const JsonValue& other) const {
    // Try to cast 'other' to JsonBoolean (as a shared pointer)
    auto otherBool = std::dynamic_pointer_cast<JsonBoolean>(std::shared_ptr<JsonValue>(const_cast<JsonValue*>(&other)));
    if (otherBool) {
        return std::make_shared<JsonBoolean>(this->value && otherBool->getValue());
    }
    throw std::runtime_error("Logical AND (&&) can only be applied between JsonBoolean values.");
}

// Implement logical OR (||) for JsonBoolean
std::shared_ptr<JsonValue> JsonBoolean::operator||(const JsonValue& other) const {
    // Try to cast 'other' to JsonBoolean (as a shared pointer)
    auto otherBool = std::dynamic_pointer_cast<JsonBoolean>(std::shared_ptr<JsonValue>(const_cast<JsonValue*>(&other)));
    if (otherBool) {
        return std::make_shared<JsonBoolean>(this->value || otherBool->getValue());
    }
    throw std::runtime_error("Logical OR (||) can only be applied between JsonBoolean values.");
}

// Implement logical NOT (!) for JsonBoolean
std::shared_ptr<JsonValue> JsonBoolean::operator!() const {
    return std::make_shared<JsonBoolean>(!this->value);
}

bool JsonBoolean::operator==(const JsonValue& other) const {
    auto otherBool = dynamic_cast<const JsonBoolean*>(&other);
    return otherBool && (this->value == otherBool->getValue());
}

bool JsonNumber::operator==(const JsonValue& other) const {
    auto otherNum = dynamic_cast<const JsonNumber*>(&other);
    return otherNum && (this->value == otherNum->getValue());
}

bool JsonString::operator==(const JsonValue& other) const {
    auto otherStr = dynamic_cast<const JsonString*>(&other);
    return otherStr && (this->value == otherStr->getValue());
}

bool JsonArray::operator==(const JsonValue& other) const {
    auto otherArr = dynamic_cast<const JsonArray*>(&other);
    if (otherArr && this->size() == otherArr->size()) {
        for (size_t i = 0; i < this->size(); ++i) {
            if (!(*this->getValues()[i] == *otherArr->getValues()[i])) {
                return false;  // If any element doesn't match, return false
            }
        }
        return true;  // All elements match
    }
    return false;
}

bool JsonObject::operator==(const JsonValue& other) const {
    auto otherObj = dynamic_cast<const JsonObject*>(&other);
    if (otherObj && this->getKeyValues().size() == otherObj->getKeyValues().size()) {
        for (const auto& pair : this->getKeyValues()) {
            auto rhsVal = otherObj->get(pair.first);
            if (*pair.second != *rhsVal) {
                return false;  // If any key-value pair doesn't match, return false
            }
        }
        return true;  // All key-value pairs match
    }
    return false;
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

const std::shared_ptr<JsonValue>& JsonObject::get(const std::string& key) const {
    for (const auto& pair : keyValues) {
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

size_t JsonValue::size() const {
    return 1; // Default size for single-value JSON types
}

size_t JsonObject::size() const {
    return keyValues.size(); // Return the number of key-value pairs
}

bool JsonValue::isEmpty() const {
    return false; // Non-array and non-object types are never empty
}

bool JsonObject::isEmpty() const {
    return keyValues.empty() ? true : false;
}

bool JsonArray::isEmpty() const {
    return values.empty() ? true : false;
}

bool JsonValue::hasKey(const std::string& key) const {
    return false; // Non-object types do not have keys
}

bool JsonObject::hasKey(const std::string& key) const {
    for (const auto& pair : keyValues) {
        if (pair.first == key) {
            return true;
        }
    }
    return false;
}

std::string JsonValue::typeOf() const {
    return "null"; // Default type for null or unsupported types
}

std::string JsonBoolean::typeOf() const {
    return "boolean";
}

std::string JsonString::typeOf() const {
    return "string";
}

std::string JsonNumber::typeOf() const {
    return "number";
}

std::string JsonObject::typeOf() const {
    return "object";
}

std::string JsonArray::typeOf() const {
    return "array";
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