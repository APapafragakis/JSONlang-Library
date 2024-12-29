#include "JSONlang.h"

JsonBoolean::JsonBoolean(bool val) : value(val) {}

void JsonBoolean::print() const {
    std::cout << (value ? "true" : "false");
}

bool JsonBoolean::getValue() const {
    return value;
}

JsonString::JsonString(const std::string& val) : value(val) {}

void JsonString::print() const {
    std::cout << "\"" << value << "\"";
}

JsonNumber::JsonNumber(double val) : value(val) {}

void JsonNumber::print() const {
    std::cout << value;
}

// Syntelesth+ gia JsonNumber, JsonString, JsonArray, JsonObject
std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() + num_rhs->getValue());
    }

    auto str_lhs = std::dynamic_pointer_cast<JsonString>(lhs);
    auto str_rhs = std::dynamic_pointer_cast<JsonString>(rhs);
    if (str_lhs && str_rhs) {
        return std::make_shared<JsonString>(str_lhs->getValue() + str_rhs->getValue());
    }

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

    throw std::runtime_error("Unsupported types for operator+");
}

// Syntelesths-
std::shared_ptr<JsonValue> operator-(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() - num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

// Syntelesths*
std::shared_ptr<JsonValue> operator*(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonNumber>(num_lhs->getValue() * num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber.");
}

// Syntelesths %
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

// Syntelesths /
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

// Sygkrish me >
std::shared_ptr<JsonValue> operator>(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() > num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Sygkrish me <
std::shared_ptr<JsonValue> operator<(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() < num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Sygkrish me >=
std::shared_ptr<JsonValue> operator>=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() >= num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
}

// Sygkrish me <=
std::shared_ptr<JsonValue> operator<=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    auto num_lhs = std::dynamic_pointer_cast<JsonNumber>(lhs);
    auto num_rhs = std::dynamic_pointer_cast<JsonNumber>(rhs);
    if (num_lhs && num_rhs) {
        return std::make_shared<JsonBoolean>(num_lhs->getValue() <= num_rhs->getValue());
    }
    throw std::runtime_error("Both operands must be JsonNumber for comparison.");
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
                return false;
            }
        }
        return true;
    }
    return false;
}

bool JsonObject::operator==(const JsonValue& other) const {
    auto otherObj = dynamic_cast<const JsonObject*>(&other);
    if (otherObj && this->getKeyValues().size() == otherObj->getKeyValues().size()) {
        for (const auto& pair : this->getKeyValues()) {
            auto rhsVal = otherObj->get(pair.first);
            if (*pair.second != *rhsVal) {
                return false;
            }
        }
        return true;
    }
    return false;
}

JsonObject::JsonObject() = default;

JsonObject::JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init) : keyValues(init) {}

// Eisagogh klhdiou-kai timhs
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

// Ektypwsh JsonObject
void JsonObject::print() const {
    std::cout << "{";
    for (size_t i = 0; i < keyValues.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "\"" << keyValues[i].first << "\": ";
        keyValues[i].second->print();
    }
    std::cout << "}";
}

JsonArray::JsonArray() = default;

JsonArray::JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init) : values(init) {}

// Orismos timhs se sygkekrimeno index
void JsonArray::set(size_t index, std::shared_ptr<JsonValue> value) {
    if (index >= values.size()) {
        values.resize(index + 1, nullptr);
    }
    values[index] = value;
}

// Eisagwgh timhs se index
std::shared_ptr<JsonValue>& JsonArray::get(size_t index) {
    if (index >= values.size()) {
        throw std::runtime_error("Index out of range");
    }
    return values[index];
}

void JsonArray::append(std::shared_ptr<JsonValue> value) {
    values.push_back(value);
}

// Diagrafh se sygkekrimeno index
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

// Ektypwsh JsonArray
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

// Allagh megethous JsonArray
void JsonArray::resize(size_t newSize, std::shared_ptr<JsonValue> defaultValue) {
    values.resize(newSize, defaultValue);
}

JsonSetter::JsonSetter(std::shared_ptr<JsonValue>& target) : target(target) {}

JsonSetter JsonSetter::operator[](const std::string& key) {
    auto obj = std::dynamic_pointer_cast<JsonObject>(target);
    if (!obj) {
        target = std::make_shared<JsonObject>();
        obj = std::dynamic_pointer_cast<JsonObject>(target);
    }

    try {
        auto& value = const_cast<std::shared_ptr<JsonValue>&>(obj->get(key));
        return JsonSetter(value);
    } catch (const std::runtime_error&) {
        obj->set(key, std::make_shared<JsonString>(""));
        auto& value = const_cast<std::shared_ptr<JsonValue>&>(obj->get(key));
        return JsonSetter(value);
    }
}

JsonSetter JsonSetter::operator[](size_t index) {
    auto arr = std::dynamic_pointer_cast<JsonArray>(target);
    if (!arr) {
        target = std::make_shared<JsonArray>();
        arr = std::dynamic_pointer_cast<JsonArray>(target);
    }
    if (!arr) {
        throw std::runtime_error("Failed to initialize JsonArray.");
    }

    if (index >= arr->size()) {
        arr->resize(index + 1, std::make_shared<JsonString>(""));
    }
    return JsonSetter(arr->get(index));
}

void JsonSetter::assign(std::shared_ptr<JsonValue> value) {
    target = value;
}

// Prosthikh se JsonArray
void JsonSetter::append(std::initializer_list<std::shared_ptr<JsonValue>> values) {
    auto arr = std::dynamic_pointer_cast<JsonArray>(target);
    if (!arr) {
        throw std::runtime_error("Target is not a JSON array; cannot append values.");
    }
    for (auto& value : values) {
        arr->append(value);
    }
}

size_t JsonValue::size() const {
    return 1;
}

size_t JsonObject::size() const {
    return keyValues.size();
}

bool JsonValue::isEmpty() const {
    return false;
}

bool JsonObject::isEmpty() const {
    return keyValues.empty() ? true : false;
}

bool JsonArray::isEmpty() const {
    return values.empty() ? true : false;
}

bool JsonValue::hasKey(const std::string& key) const {
    return false;
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
    return "null";
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

// Sunarthseis ERASE gia JsonValues
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

// Ektypwsh JSON symfwna me KeyPath
void printJson(const std::shared_ptr<JsonValue>& jsonValue, const std::string& keyPath) {
    size_t pos = 0;
    std::shared_ptr<JsonValue> currentValue = jsonValue;
    std::string path = keyPath;

    while ((pos = path.find(".")) != std::string::npos) {
        std::string key = path.substr(0, pos);
        path.erase(0, pos + 1);

        auto obj = std::dynamic_pointer_cast<JsonObject>(currentValue);
        if (!obj || !obj->hasKey(key)) {
            std::cerr << "Key not found: " << key << std::endl;
            return;
        }
        currentValue = obj->get(key);
    }

    if (!path.empty()) {
        auto obj = std::dynamic_pointer_cast<JsonObject>(currentValue);
        if (!obj || !obj->hasKey(path)) {
            std::cerr << "Key not found: " << path << std::endl;
            return;
        }
        currentValue = obj->get(path);
    }

    currentValue->print();
    std::cout << std::endl;
}
