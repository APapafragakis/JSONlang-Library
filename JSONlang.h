#ifndef JSONLANG_H
#define JSONLANG_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <algorithm>

class JsonValue;

// Dilosi voithitikon synartiseon prin apo oles tis diloseis klaseon
void printJsonHelper(const std::shared_ptr<JsonValue>& value);
void printJson(const std::shared_ptr<JsonValue>& jsonValue);
void printJson(const std::shared_ptr<JsonValue>& jsonValue, const std::string& keyPath);

// -------------------------------------------------------------------------
// Vasi klasi: JsonValue
// -------------------------------------------------------------------------
class JsonValue {
public:
    virtual void print() const = 0;
    virtual void erase() = 0;
    virtual void erase(const std::string& key) = 0;
    virtual void erase(size_t index) = 0;
    virtual bool operator==(const JsonValue& other) const = 0;
    virtual bool operator!=(const JsonValue& other) const { return !(*this == other); }
    virtual size_t size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool hasKey(const std::string& key) const = 0;
    virtual std::string typeOf() const = 0;
    virtual ~JsonValue() = default;

    virtual std::shared_ptr<JsonValue>& operator[](size_t) {
        throw std::runtime_error("Den ypostirizetai prosvasis pinaka gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue>& operator[](const std::string&) {
        throw std::runtime_error("Den ypostirizetai prosvasis kleidiou gia ayto to typo");
    }

    virtual JsonValue& operator=(const std::shared_ptr<JsonValue>&) {
        throw std::runtime_error("Den ypostirizetai anathetisi gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator+(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai prosthesi gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator-(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai afairesi gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator*(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai pollaplasiasmos gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator/(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai diairesi gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator%(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai ypoloipo diairesis gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator&&(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai logiko AND gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator||(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai logiko OR gia ayto to typo");
    }

    virtual std::shared_ptr<JsonValue> operator!() const {
        throw std::runtime_error("Den ypostirizetai logiko NOT gia ayto to typo");
    }

    virtual bool operator>(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai sygkrisi megalyterou gia ayto to typo");
    }

    virtual bool operator>=(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai sygkrisi megalyterou i isou gia ayto to typo");
    }

    virtual bool operator<(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai sygkrisi mikroterou gia ayto to typo");
    }

    virtual bool operator<=(const JsonValue& other) const {
        throw std::runtime_error("Den ypostirizetai sygkrisi mikroterou i isou gia ayto to typo");
    }
};

// -------------------------------------------------------------------------
// Dilosi tis JsonNumber klasis
// -------------------------------------------------------------------------
class JsonNumber : public JsonValue {
    double value;
public:
    explicit JsonNumber(double val);
    void print() const override;
    double getValue() const;
    std::string typeOf() const override;
    bool operator==(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator+(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator-(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator*(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator/(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator%(const JsonValue& other) const override;

    bool operator>(const JsonValue& other) const override;
    bool operator>=(const JsonValue& other) const override;
    bool operator<(const JsonValue& other) const override;
    bool operator<=(const JsonValue& other) const override;

    void erase() override {}
    void erase(const std::string&) override {}
    void erase(size_t) override {}
    size_t size() const override { return 1; }
    bool isEmpty() const override { return false; }
    bool hasKey(const std::string&) const override { return false; }
};


// -------------------------------------------------------------------------
// diloseis ton JsonObject kai JsonArray klaseon
// (Aparaiteitai gia na kanoume dynamic cast se aftes tis klaseis sto JsonAccessor.)
// -------------------------------------------------------------------------
class JsonObject;
class JsonArray;

// -------------------------------------------------------------------------
//  typoi JSON: JsonBoolean, JsonString, JsonNumber
// -------------------------------------------------------------------------
class JsonBoolean : public JsonValue {
    bool value;
public:
    explicit JsonBoolean(bool val);
    void print() const override;
    bool getValue() const;
    std::string typeOf() const override;
    bool operator==(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator&&(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator||(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator!() const override;

    void erase() override {}
    void erase(const std::string&) override {}
    void erase(size_t) override {}
    size_t size() const override { return 1; }
    bool isEmpty() const override { return false; }
    bool hasKey(const std::string&) const override { return false; }
};

class JsonString : public JsonValue {
    std::string value;
public:
    explicit JsonString(const std::string& val);
    void print() const override;
    const std::string& getValue() const;
    std::string typeOf() const override;
    bool operator==(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator+(const JsonValue& other) const override;

    void erase() override {}
    void erase(const std::string&) override {}
    void erase(size_t) override {}
    size_t size() const override { return 1; }
    bool isEmpty() const override { return value.empty(); }
    bool hasKey(const std::string&) const override { return false; }
};

// -------------------------------------------------------------------------
// JsonObject
// -------------------------------------------------------------------------
class JsonObject : public JsonValue {
    std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> keyValues;
public:
    JsonObject() = default;
    JsonObject(const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& init);

    std::shared_ptr<JsonValue>& operator[](const std::string& key) override;
    // Prosthiki aftis tis overload gia prosvasis meso string literal
    std::shared_ptr<JsonValue>& operator[](const char* key) {
        return operator[](std::string(key));
    }
    JsonValue& operator=(const std::shared_ptr<JsonValue>& other) override;
    void set(const std::string& key, std::shared_ptr<JsonValue> value);
    const std::shared_ptr<JsonValue>& get(const std::string& key) const;
    void erase(const std::string& key) override;
    void erase() override;
    void erase(size_t) override {}
    void print() const override;
    bool operator==(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator+(const JsonValue& other) const override;
    size_t size() const override;
    bool isEmpty() const override;
    bool hasKey(const std::string& key) const override;
    std::string typeOf() const override;
    const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& getKeyValues() const;
};

// -------------------------------------------------------------------------
// JsonArray
// -------------------------------------------------------------------------
class JsonArray : public JsonValue {
    std::vector<std::shared_ptr<JsonValue>> values;
public:
    JsonArray() = default;
    JsonArray(const std::vector<std::shared_ptr<JsonValue>>& init);

    std::shared_ptr<JsonValue>& operator[](size_t index) override;
    JsonValue& operator=(const std::shared_ptr<JsonValue>& other) override;

    template<typename... Args>
    void appendValues(Args... args) {
        (values.push_back(args), ...);
    }

    void set(size_t index, std::shared_ptr<JsonValue> value);
    std::shared_ptr<JsonValue>& get(size_t index);
    void append(std::shared_ptr<JsonValue> value);
    void erase(size_t index) override;
    void erase() override;
    void erase(const std::string&) override {}
    void print() const override;
    bool operator==(const JsonValue& other) const override;
    std::shared_ptr<JsonValue> operator+(const JsonValue& other) const override;
    size_t size() const override;
    bool isEmpty() const override;
    bool hasKey(const std::string&) const override { return false; }
    std::string typeOf() const override;
    const std::vector<std::shared_ptr<JsonValue>>& getValues() const;
};

class JsonAccessor {
    std::shared_ptr<JsonValue> value;

public:
    explicit JsonAccessor(std::shared_ptr<JsonValue> v) : value(std::move(v)) {}

    // Afairesi olon ton ypoloipon overloads tou operator[] kai antikatastasi me afta:
    template<typename T>
    typename std::enable_if_t<std::is_integral_v<T>, JsonAccessor> 
    operator[](T index) const {
        auto arr = std::dynamic_pointer_cast<JsonArray>(value);
        if (!arr) throw std::runtime_error("Den einai pinakas");
        return JsonAccessor((*arr)[static_cast<size_t>(index)]);
    }

    JsonAccessor operator[](const std::string& key) const {
        auto obj = std::dynamic_pointer_cast<JsonObject>(value);
        if (!obj) throw std::runtime_error("Den einai antikeimeno");
        return JsonAccessor((*obj)[key]);
    }

    JsonAccessor operator[](const char* key) const {
        return operator[](std::string(key));
    }

    JsonArray* operator->() {
        auto arr = std::dynamic_pointer_cast<JsonArray>(value);
        if (!arr) throw std::runtime_error("Aftos o JsonAccessor den krata ena pinaka");
        return arr.get();
    }

    // Gia amesi anathetisi, px. accessor = NUMBER(42);
    JsonAccessor& operator=(std::shared_ptr<JsonValue> rhs) {
        if (!value) {
            // Diaxeirisi periptosis opou to value einai null
            value = rhs;
        } else {
            *value = *rhs;
        }
        return *this;
    }

    // Metatropi piso se shared_ptr<JsonValue> an xreiazetai
    operator std::shared_ptr<JsonValue>&() { return value; }
    operator const std::shared_ptr<JsonValue>&() const { return value; }

    // Prosthiki methodou print
    void print() const {
        if (value) {
            value->print();
        } else {
            std::cout << "null";
        }
    }
    
    template<typename... Args>
    void appendValues(Args... args) {
        auto arr = std::dynamic_pointer_cast<JsonArray>(value);
        if (!arr) {
            std::cerr << "Sfalma: Aftos o JsonAccessor den krata ena pinaka" << std::endl;
            throw std::runtime_error("Aftos o JsonAccessor den krata ena pinaka");
        }
        arr->appendValues(args...);
    }
};

// -------------------------------------------------------------------------
// EraseAccessor gia afairesi JSON stoixion
// -------------------------------------------------------------------------
class EraseAccessor {
    std::shared_ptr<JsonValue> value;
    std::string key;
    size_t index;
    bool isKey;
    bool isIndex;

public:
    EraseAccessor() : value(nullptr), isKey(false), isIndex(false) {}

    explicit EraseAccessor(std::shared_ptr<JsonValue> v) : value(std::move(v)), isKey(false), isIndex(false) {}

    EraseAccessor(std::shared_ptr<JsonValue> v, const std::string& k) : value(std::move(v)), key(k), isKey(true), isIndex(false) {}

    EraseAccessor(std::shared_ptr<JsonValue> v, size_t idx) : value(std::move(v)), index(idx), isKey(false), isIndex(true) {}

    EraseAccessor operator[](const std::string& k) {
        auto obj = std::dynamic_pointer_cast<JsonObject>(value);
        if (!obj) throw std::runtime_error("Den einai antikeimeno");
        return EraseAccessor((*obj)[k]);
    }

    EraseAccessor operator[](const char* k) {
        return operator[](std::string(k));
    }

    EraseAccessor operator[](size_t idx) {
        auto arr = std::dynamic_pointer_cast<JsonArray>(value);
        if (!arr) throw std::runtime_error("Den einai pinakas");
        return EraseAccessor((*arr)[idx]);
    }

    ~EraseAccessor() {
        if (isKey) {
            auto obj = std::dynamic_pointer_cast<JsonObject>(value);
            if (obj) obj->erase(key);
        } else if (isIndex) {
            auto arr = std::dynamic_pointer_cast<JsonArray>(value);
            if (arr) arr->erase(index);
        } else if (value) {
            value->erase();
        }
    }
};

// -------------------------------------------------------------------------
// Ananeosi orismon macros:
// -------------------------------------------------------------------------
#define ERASE(json_var) do { \
    EraseAccessor __erase_temp__(json_var); \
} while (0)
#define APPEND(...) appendValues(__VA_ARGS__)

// -------------------------------------------------------------------------
// Macros gia JSON syntaxi
// -------------------------------------------------------------------------
#define JSON(name) std::shared_ptr<JsonValue> name
#define OBJECT(...) ( std::make_shared<JsonObject>(std::vector<std::pair<std::string,std::shared_ptr<JsonValue>>>{ __VA_ARGS__ }) )
#define ARRAY(...) ( std::make_shared<JsonArray>(std::vector<std::shared_ptr<JsonValue>>{ __VA_ARGS__ }) )
#define STRING(value) ( std::make_shared<JsonString>((value)) )
#define NUMBER(value) ( std::make_shared<JsonNumber>((value)) )
#define BOOLEAN(value) ( std::make_shared<JsonBoolean>((value)) )
#define SET(json_var) ( ACCESS(json_var) )
#define ASSIGN =
#define KEY(k) #k
#define OBJECT_INIT(key, value) {key, value}
#define NULL_VALUE nullptr
#define PROGRAM_BEGIN int main() {
#define PROGRAM_END return 0; }


// Prosthiki neas macros konta stis alles diloseis macros
#define SIZE_OF(json_var) ((json_var)->size())
#define IS_EMPTY(json_var) ((json_var)->isEmpty())
#define HAS_KEY(json_var, key) ((json_var)->hasKey(key))
#define TYPE_OF(json_var) ((json_var)->typeOf())


inline std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) + (*rhs);
}

inline std::shared_ptr<JsonValue> operator-(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) - (*rhs);
}

inline std::shared_ptr<JsonValue> operator*(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) * (*rhs);
}

inline std::shared_ptr<JsonValue> operator/(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) / (*rhs);
}

inline std::shared_ptr<JsonValue> operator&&(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) && (*rhs);
}

inline std::shared_ptr<JsonValue> operator||(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) || (*rhs);
}

inline bool operator>(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) > (*rhs);
}

inline bool operator>=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) >= (*rhs);
}

inline bool operator<(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) < (*rhs);
}

inline bool operator<=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs) {
    return (*lhs) <= (*rhs);
}

namespace detail {
    template<typename T>
    struct JsonPrinter {
        static void print(const T& val) {
            std::cout << val;
        }
    };

    template<>
    struct JsonPrinter<JsonAccessor> {
        static void print(const JsonAccessor& acc) {
            acc.print();
        }
    };

    template<>
    struct JsonPrinter<std::shared_ptr<JsonValue>> {
        static void print(const std::shared_ptr<JsonValue>& val) {
            if (val) val->print();
            else std::cout << "null";
        }
    };

    template<>
    struct JsonPrinter<const char*> {
        static void print(const char* val) {
            std::cout << val;
        }
    };

    template<>
    struct JsonPrinter<std::string> {
        static void print(const std::string& val) {
            std::cout << val;
        }
    };

    template<typename T>
    void printValue(const T& val) {
        JsonPrinter<std::remove_cv_t<std::remove_reference_t<T>>>::print(val);
    }

    template<typename... Args>
    void printAll(const Args&... args) {
        ((printValue(args), std::cout << " "), ...);
        std::cout << std::endl;
    }
}


inline JsonAccessor get_accessor(const std::shared_ptr<JsonValue>& ptr) {
    return JsonAccessor(ptr);
}

#define PRINT(...) detail::printAll(__VA_ARGS__)
#define ACCESS(json_var) get_accessor(json_var)

#endif // JSONLANG_H
