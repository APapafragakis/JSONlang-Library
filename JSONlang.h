#ifndef JSONLANG_H
#define JSONLANG_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

// Dhlwsh ths JsonValue
class JsonValue; 

// Ypobohthikh synarthsh gia ektypwsh JSON
void printJson(const std::shared_ptr<JsonValue>& jsonValue, const std::string& keyPath);

// Base class gia ola ta JSON values
class JsonValue {
public:
    virtual void print() const = 0; // Ektypwsh timhs
    virtual void erase() {};                      // Katharismos olwn twn timwn
    virtual void erase(const std::string& key) {}; // Diagrafh me vash to kleidi (gia objects)
    virtual void erase(size_t index) {};          // Diagrafh me vash to index (gia arrays)
    virtual bool operator==(const JsonValue& other) const = 0;  // Sygkrish isothtas
    virtual bool operator!=(const JsonValue& other) const {
        return !(*this == other);  // Arnhtikh isothta
    }
    virtual size_t size() const; // Megethos
    virtual bool isEmpty() const; // Elegxos an einai adeio
    virtual bool hasKey(const std::string& key) const; // Elegxos gia kleidi
    virtual std::string typeOf() const; // Typos JsonValue

    virtual ~JsonValue() = default;
};

// JsonBoolean klash gia boolean timwn
class JsonBoolean : public JsonValue {
    bool value;
public:
    explicit JsonBoolean(bool val);  // Constructor
    void print() const override;     // Ektypwsh
    bool getValue() const;           // Getter gia thn timh
    std::string typeOf() const override; // Typou "boolean"
    virtual bool operator==(const JsonValue& other) const override;

    std::shared_ptr<JsonValue> operator&&(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator||(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator!() const;
};

// JsonString klash gia strings
class JsonString : public JsonValue {
    std::string value;
public:
    explicit JsonString(const std::string& val);
    void print() const override;
    virtual bool operator==(const JsonValue& other) const override;
    std::string typeOf() const override; // Typou "string"
    const std::string& getValue() const { return value; }
};

// JsonNumber klash gia arithmous
class JsonNumber : public JsonValue {
    double value;
public:
    explicit JsonNumber(double val);
    void print() const override;
    double getValue() const { return value; } // Getter gia thn timh
    std::string typeOf() const override; // Typou "number"
    virtual bool operator==(const JsonValue& other) const override;

    // Arithmeticoi syntelestes
    std::shared_ptr<JsonValue> operator+(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator-(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator*(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator/(const JsonValue& other) const;
    std::shared_ptr<JsonValue> operator%(const JsonValue& other) const;

    // Sygkritikoi syntelestes
    bool operator>(const JsonValue& other) const;
    bool operator<(const JsonValue& other) const;
    bool operator>=(const JsonValue& other) const;
    bool operator<=(const JsonValue& other) const;
};

// JsonObject klash gia objects
class JsonObject : public JsonValue {
    std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> keyValues;
public:
    JsonObject();
    JsonObject(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>> init);
    void set(const std::string& key, std::shared_ptr<JsonValue> value);
    const std::shared_ptr<JsonValue>& get(const std::string& key) const;
    void erase(const std::string& key) override;
    void erase() override;
    void print() const override;
    virtual bool operator==(const JsonValue& other) const override;
    size_t size() const override;
    bool isEmpty() const override;
    bool hasKey(const std::string& key) const override;
    std::string typeOf() const override;
    const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& getKeyValues() const { return keyValues; }
};

// JsonArray klash gia arrays
class JsonArray : public JsonValue {
    std::vector<std::shared_ptr<JsonValue>> values;
public:
    JsonArray();
    JsonArray(std::initializer_list<std::shared_ptr<JsonValue>> init);
    void set(size_t index, std::shared_ptr<JsonValue> value);
    std::shared_ptr<JsonValue>& get(size_t index);
    void append(std::shared_ptr<JsonValue> value);
    void erase(size_t index) override;
    void erase() override;
    void print() const override;
    virtual bool operator==(const JsonValue& other) const override;

    size_t size() const override;
    void resize(size_t newSize, std::shared_ptr<JsonValue> defaultValue);
    bool isEmpty() const override;
    std::string typeOf() const override;

    const std::vector<std::shared_ptr<JsonValue>>& getValues() const { return values; }
};

// JsonSetter bohthitikos gia JSON edit
class JsonSetter {
    std::shared_ptr<JsonValue>& target;
public:
    explicit JsonSetter(std::shared_ptr<JsonValue>& target);
    JsonSetter operator[](const std::string& key);
    JsonSetter operator[](size_t index);
    void assign(std::shared_ptr<JsonValue> value);
    void append(std::initializer_list<std::shared_ptr<JsonValue>> values);
};

// Synarthseis ERASE gia katharismo
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

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<JsonValue>& jsonValue) {
    if (!jsonValue) {
        os << "null";
    } else {
        jsonValue->print();
    }
    return os;
}

template <typename T>
void PRINT(const std::shared_ptr<JsonValue>& jsonValue, T&& key) {
    if constexpr (std::is_same_v<std::decay_t<T>, bool>) {
        std::cout << (key ? "true" : "false") << std::endl;
    } else if constexpr (std::is_same_v<std::decay_t<T>, const char*> || std::is_same_v<std::decay_t<T>, std::string>) {
        printJson(jsonValue, key);
    } else {
        std::cout << key << std::endl;
    }
}

template <typename T, typename... Args>
void printJsonHelper(const std::shared_ptr<JsonValue>& jsonValue, T&& first, Args&&... rest) {
    printJsonHelper(jsonValue, std::forward<T>(first));

    if constexpr (sizeof...(rest) > 0) {
        printJsonHelper(jsonValue, std::forward<Args>(rest)...);
    }
}

#define JSON(name) std::shared_ptr<JsonValue> name
#define OBJECT(...) std::make_shared<JsonObject>(std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>>{__VA_ARGS__})
#define ARRAY(...) std::make_shared<JsonArray>(std::initializer_list<std::shared_ptr<JsonValue>>{__VA_ARGS__})
#define STRING(value) std::make_shared<JsonString>(value)
#define NUMBER(value) std::make_shared<JsonNumber>(value)
#define null std::shared_ptr<JsonValue>()
#define TRUE std::make_shared<JsonBoolean>(true)
#define FALSE std::make_shared<JsonBoolean>(false)
#define KEY(key) key
#define SET(target) JsonSetter(target)
#define ASSIGN(value) .assign(value)
#define APPEND(...) .append({__VA_ARGS__})
#define BOOLEAN(value) std::make_shared<JsonBoolean>(value)
#define SIZE_OF(json_value) (json_value->size())
#define IS_EMPTY(json_value) (json_value->isEmpty())
#define HAS_KEY(json_value, key) (json_value->hasKey(key))
#define TYPE_OF(json_value) (json_value->typeOf())

std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator-(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator*(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator/(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator%(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator>(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator<(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator>=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator<=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator==(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
std::shared_ptr<JsonValue> operator!=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);

#endif // JSONLANG_H
