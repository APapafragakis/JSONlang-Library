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

void JsonArray::set(size_t index, std::shared_ptr<JsonValue> value) {
    if (index >= values.size()) {
        values.resize(index + 1, nullptr);
    }
    values[index] = value;
}

std::shared_ptr<JsonValue>& JsonArray::get(size_t index) {
    if (index >= values.size()) {
        throw std::runtime_error("Index out of range");
    }
    return values[index];
}

void JsonArray::append(std::shared_ptr<JsonValue> value) {
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

size_t JsonArray::size() const {
    return values.size();
}

void JsonArray::resize(size_t newSize, std::shared_ptr<JsonValue> defaultValue) {
    values.resize(newSize, defaultValue);
}

// JsonSetter Implementation
JsonSetter::JsonSetter(std::shared_ptr<JsonValue>& target) : target(target) {}

JsonSetter JsonSetter::operator[](const std::string& key) {
    auto obj = std::dynamic_pointer_cast<JsonObject>(target);
    if (!obj) {
        target = std::make_shared<JsonObject>();
        obj = std::dynamic_pointer_cast<JsonObject>(target);
    }
    try {
        return JsonSetter(obj->get(key));
    } catch (const std::runtime_error&) {
        obj->set(key, std::make_shared<JsonString>("")); // Default empty value
        return JsonSetter(obj->get(key));
    }
}

JsonSetter JsonSetter::operator[](size_t index) {
    auto arr = std::dynamic_pointer_cast<JsonArray>(target);
    if (!arr) {
        target = std::make_shared<JsonArray>();
        arr = std::dynamic_pointer_cast<JsonArray>(target);
    }
    if (index >= arr->size()) {
        arr->resize(index + 1, std::make_shared<JsonString>("")); // Default empty value
    }
    return JsonSetter(arr->get(index));
}

void JsonSetter::assign(std::shared_ptr<JsonValue> value) {
    target = value;
}

void JsonSetter::append(std::initializer_list<std::shared_ptr<JsonValue>> values) {
    auto arr = std::dynamic_pointer_cast<JsonArray>(target);
    if (!arr) {
        throw std::runtime_error("Target is not a JSON array; cannot append values.");
    }
    for (auto& value : values) {
        arr->append(value);
    }
}
