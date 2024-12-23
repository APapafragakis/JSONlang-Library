#ifndef JSONLANG_H
#define JSONLANG_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

// Base class for all JSON values
class JsonValue {
public:
    virtual void print() const = 0;
    virtual void erase() {};                      // Clear all
    virtual void erase(const std::string& key) {}; // Remove by key (for objects)
    virtual void erase(size_t index) {};          // Remove by index (for arrays)
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
    void erase(const std::string& key) override;
    void erase() override;
    void print() const override;
};

// JsonArray
class JsonArray : public JsonValue {
    std::vector<std::shared_ptr<JsonValue>> values;
public:
    JsonArray();
    JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init);
    void append(std::shared_ptr<JsonValue> value);
    void erase(size_t index) override;
    void erase() override;
    void print() const override;

    size_t size() const;
};

// Helper functions for ERASE
void ERASE(std::shared_ptr<JsonValue> target);
void ERASE(std::shared_ptr<JsonValue> target, const std::string& key);

template <typename... Args>
void ERASE(std::shared_ptr<JsonValue> target, const std::string& firstKey, Args... rest) {
    auto obj = std::dynamic_pointer_cast<JsonObject>(target);
    if (!obj) {
        throw std::runtime_error("Target is not a JSON object.");
    }

    std::shared_ptr<JsonValue> next = obj->get(firstKey);

    if constexpr (sizeof...(rest) == 0) {
        next->erase();
    } else {
        ERASE(next, rest...);
    }
}

// Macros for JSON syntax
#define JSON(name) std::shared_ptr<JsonValue> name
#define OBJECT(...) std::make_shared<JsonObject>(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>>{__VA_ARGS__})
#define ARRAY(...) std::make_shared<JsonArray>(std::initializer_list<std::shared_ptr<JsonValue>>{__VA_ARGS__})
#define STRING(value) std::make_shared<JsonString>(value)
#define NUMBER(value) std::make_shared<JsonNumber>(value)
#define KEY(key) key

#endif // JSONLANG_H
