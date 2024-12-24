    #ifndef JSONLANG_H
    #define JSONLANG_H

    #include <iostream>
    #include <vector>
    #include <string>
    #include <memory>
    #include <stdexcept>
    #include <initializer_list>
    #include <algorithm>

    class JsonValue; 

    void printJson(const std::shared_ptr<JsonValue>& jsonValue, const std::string& keyPath);

    // Base class for all JSON values
    class JsonValue {
    public:
        virtual void print() const = 0;
        virtual void erase() {};                      // Clear all
        virtual void erase(const std::string& key) {}; // Remove by key (for objects)
        virtual void erase(size_t index) {};          // Remove by index (for arrays)
        virtual bool operator==(const JsonValue& other) const = 0;  // Add this declaration
        virtual bool operator!=(const JsonValue& other) const {
            return !(*this == other);  // Default negation of equality
        }
        virtual size_t size() const; // Default size method
        virtual bool isEmpty() const; // Default isEmpty method
        virtual bool hasKey(const std::string& key) const; // Default hasKey method
        virtual std::string typeOf() const; // Default typeOf method

        virtual ~JsonValue() = default;
    };

    class JsonBoolean : public JsonValue {
        bool value;
    public:
        explicit JsonBoolean(bool val);  // Constructor declaration
        void print() const override;     // print method declaration
        bool getValue() const;           // getValue method declaration
        std::string typeOf() const override; // Override typeOf for boolean
        virtual bool operator==(const JsonValue& other) const override;

        std::shared_ptr<JsonValue> operator&&(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator||(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator!() const;
    };

    // JsonString class
    class JsonString : public JsonValue {
        std::string value;
    public:
        explicit JsonString(const std::string& val);
        void print() const override;
        virtual bool operator==(const JsonValue& other) const override;
        std::string typeOf() const override; // Override typeOf for string
        const std::string& getValue() const { return value; }
    };


    // JsonNumber class
    class JsonNumber : public JsonValue {
        double value;
    public:
        explicit JsonNumber(double val);
        void print() const override;

        // Getter for value
        double getValue() const { return value; }
        std::string typeOf() const override; // Override typeOf for number
        virtual bool operator==(const JsonValue& other) const override;
        // Overload arithmetic operators for JsonNumber
        std::shared_ptr<JsonValue> operator+(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator-(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator*(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator/(const JsonValue& other) const;
        std::shared_ptr<JsonValue> operator%(const JsonValue& other) const;

        // Overload relational operators for JsonNumber
        bool operator>(const JsonValue& other) const;
        bool operator<(const JsonValue& other) const;
        bool operator>=(const JsonValue& other) const;
        bool operator<=(const JsonValue& other) const;
    };

    // JsonObject class
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
        size_t size() const override; // Override size for object
        bool isEmpty() const override; // Override isEmpty for object
        bool hasKey(const std::string& key) const override; // Override hasKey for object
        std::string typeOf() const override; // Override typeOf for object
        const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& getKeyValues() const { return keyValues; }  // Add const qualifier
    };

    // JsonArray class
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

        size_t size() const override; // Override size for array
        void resize(size_t newSize, std::shared_ptr<JsonValue> defaultValue); // Resize array
        bool isEmpty() const override; // Override isEmpty for array
        std::string typeOf() const override; // Override typeOf for array

        const std::vector<std::shared_ptr<JsonValue>>& getValues() const { return values; }  // Add const qualifier
    };

    // Helper class for editing JSON values
    class JsonSetter {
        std::shared_ptr<JsonValue>& target;
    public:
        explicit JsonSetter(std::shared_ptr<JsonValue>& target);
        JsonSetter operator[](const std::string& key);
        JsonSetter operator[](size_t index);
        void assign(std::shared_ptr<JsonValue> value);
        void append(std::initializer_list<std::shared_ptr<JsonValue>> values);
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

    inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<JsonValue>& jsonValue) {
        if (!jsonValue) {
            os << "null"; // Handle NULL explicitly
        } else {
            jsonValue->print(); // Call the print function of the stored JsonValue
        }
        return os;
    }


template <typename T>
void PRINT(const std::shared_ptr<JsonValue>& jsonValue, T&& key) {
    if constexpr (std::is_same_v<std::decay_t<T>, bool>) {
        // Handle boolean keys
        std::cout << (key ? "true" : "false") << std::endl;
    } else if constexpr (std::is_same_v<std::decay_t<T>, const char*> || std::is_same_v<std::decay_t<T>, std::string>) {
        // Handle string keys
        printJson(jsonValue, key);
    } else {
        // For other types, print the value directly
        std::cout << key << std::endl;
    }
}


template <typename T, typename... Args>
void printJsonHelper(const std::shared_ptr<JsonValue>& jsonValue, T&& first, Args&&... rest) {
    // Print the first argument
    printJsonHelper(jsonValue, std::forward<T>(first));

    // Recursively handle the rest
    if constexpr (sizeof...(rest) > 0) {
        printJsonHelper(jsonValue, std::forward<Args>(rest)...);
    }
}


    // Macros for JSON syntax
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



    // Operators for shared_ptr<JsonValue>
    std::shared_ptr<JsonValue> operator+(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator-(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator*(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator/(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator%(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs); // Added %
    std::shared_ptr<JsonValue> operator>(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator<(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator>=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator<=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator==(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);
    std::shared_ptr<JsonValue> operator!=(const std::shared_ptr<JsonValue>& lhs, const std::shared_ptr<JsonValue>& rhs);


    #endif // JSONLANG_H