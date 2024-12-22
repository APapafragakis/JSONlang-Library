// JSONlang.h
#ifndef JSONLANG_H
#define JSONLANG_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>

// Base class for all JSON values
class JsonValue {
public:
    virtual void print() const = 0;
    virtual ~JsonValue() = default;
};

// JsonString
class JsonString : public JsonValue {
    std::string value;
public:
    explicit JsonString(const std::string& val);
    void print() const override;
};

// JsonNumber
class JsonNumber : public JsonValue {
    double value;
public:
    explicit JsonNumber(double val);
    void print() const override;
};

// JsonObject
class JsonObject : public JsonValue {
    std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> keyValues;
public:
    JsonObject();
    JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init);
    void set(const std::string& key, std::shared_ptr<JsonValue> value);
    std::shared_ptr<JsonValue>& get(const std::string& key);
    void print() const override;
};

// JsonArray
class JsonArray : public JsonValue {
    std::vector<std::shared_ptr<JsonValue>> values;
public:
    JsonArray();
    JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init);
    void set(size_t index, std::shared_ptr<JsonValue> value);
    std::shared_ptr<JsonValue>& get(size_t index);
    void append(std::shared_ptr<JsonValue> value);
    void print() const override;

    // Accessor for JsonSetter
    size_t size() const;  // Get the size of the array
    void resize(size_t newSize, std::shared_ptr<JsonValue> defaultValue); // Resize array
};

// Helper class for editing JSON values
class JsonSetter {
    std::shared_ptr<JsonValue>& target;
public:
    explicit JsonSetter(std::shared_ptr<JsonValue>& target);
    JsonSetter operator[](const std::string& key);
    JsonSetter operator[](size_t index);
    void assign(std::shared_ptr<JsonValue> value);
};

// Macros for JSON syntax
#define JSON(name) std::shared_ptr<JsonValue> name
#define OBJECT(...) std::make_shared<JsonObject>(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>>{__VA_ARGS__})
#define ARRAY(...) std::make_shared<JsonArray>(std::initializer_list<std::shared_ptr<JsonValue>>{__VA_ARGS__})
#define STRING(value) std::make_shared<JsonString>(value)
#define NUMBER(value) std::make_shared<JsonNumber>(value)
#define SET(target) JsonSetter(target)
#define KEY(key) key

#endif // JSONLANG_H
