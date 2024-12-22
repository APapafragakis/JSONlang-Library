#ifndef JSONLANG_H
#define JSONLANG_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Base class for all JSON values
class JsonValue {
public:
    virtual void print() const = 0; // Pure virtual method for printing
    virtual ~JsonValue() = default; // Virtual destructor
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

// JsonBoolean
class JsonBoolean : public JsonValue {
    bool value;
public:
    explicit JsonBoolean(bool val);
    void print() const override;
};

// JsonNull
class JsonNull : public JsonValue {
public:
    void print() const override;
};

// JsonObject
class JsonObject : public JsonValue {
    std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> keyValues; // Maintains insertion order
public:
    JsonObject(); // Default constructor
    JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init); // Constructor with initializer list
    void add(const std::string& key, std::shared_ptr<JsonValue> value);
    void print() const override;
};

// JsonArray
class JsonArray : public JsonValue {
    std::vector<std::shared_ptr<JsonValue>> values; // Stores values of the array
public:
    JsonArray();
    JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init);
    void add(std::shared_ptr<JsonValue> value);
    void print() const override;
};

// Macros for JSON syntax
#define JSON(name) std::shared_ptr<JsonValue> name
#define OBJECT(...) std::make_shared<JsonObject>(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>>{__VA_ARGS__})
#define ARRAY(...) std::make_shared<JsonArray>(std::initializer_list<std::shared_ptr<JsonValue>>{__VA_ARGS__})
#define STRING(value) std::make_shared<JsonString>(value)
#define NUMBER(value) std::make_shared<JsonNumber>(value)
#define TRUE std::make_shared<JsonBoolean>(true)
#define FALSE std::make_shared<JsonBoolean>(false)
#define JSON_NULL std::make_shared<JsonNull>()
#define KEY(key) key

#endif // JSONLANG_H
