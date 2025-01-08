#include "JSONlang.h"

// JsonBoolean ulopoiisi
JsonBoolean::JsonBoolean(bool val) : value(val) {}

void JsonBoolean::print() const {
    std::cout << (value ? "true" : "false");
}

bool JsonBoolean::getValue() const { return value; }

std::string JsonBoolean::typeOf() const { return "boolean"; }

bool JsonBoolean::operator==(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonBoolean*>(&other)) {
        return value == p->value;
    }
    return false;
}

std::shared_ptr<JsonValue> JsonBoolean::operator&&(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonBoolean*>(&other)) {
        return std::make_shared<JsonBoolean>(value && p->value);
    }
    throw std::runtime_error("Den mporei na ginei AND me mh-boolean timi");
}

std::shared_ptr<JsonValue> JsonBoolean::operator||(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonBoolean*>(&other)) {
        return std::make_shared<JsonBoolean>(value || p->value);
    }
    throw std::runtime_error("Den mporei na ginei OR me mh-boolean timi");
}

std::shared_ptr<JsonValue> JsonBoolean::operator!() const {
    return std::make_shared<JsonBoolean>(!value);
}

// JsonString ulopoiisi
JsonString::JsonString(const std::string& val) : value(val) {}

void JsonString::print() const {
    std::cout << "\"" << value << "\"";
}

const std::string& JsonString::getValue() const { return value; }

std::string JsonString::typeOf() const { return "string"; }

bool JsonString::operator==(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonString*>(&other)) {
        return value == p->value;
    }
    return false;
}

std::shared_ptr<JsonValue> JsonString::operator+(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonString*>(&other)) {
        return std::make_shared<JsonString>(value + p->value);
    }
    throw std::runtime_error("Den mporei na ginei concatenate me mh-string timi");
}

// JsonNumber ulopoiisi
JsonNumber::JsonNumber(double val) : value(val) {}

void JsonNumber::print() const {
    std::cout << value;
}

double JsonNumber::getValue() const { return value; }

std::string JsonNumber::typeOf() const { return "number"; }

bool JsonNumber::operator==(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return value == p->value;
    }
    return false;
}

std::shared_ptr<JsonValue> JsonNumber::operator+(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return std::make_shared<JsonNumber>(value + p->value);
    }
    throw std::runtime_error("Den mporei na ginei prosthesi me mh-arithmitiki timi");
}

std::shared_ptr<JsonValue> JsonNumber::operator-(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return std::make_shared<JsonNumber>(value - p->value);
    }
    throw std::runtime_error("Den mporei na ginei afairesi me mh-arithmitiki timi");
}

std::shared_ptr<JsonValue> JsonNumber::operator*(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return std::make_shared<JsonNumber>(value * p->value);
    }
    throw std::runtime_error("Den mporei na ginei pollaplasiasmos me mh-arithmitiki timi");
}

std::shared_ptr<JsonValue> JsonNumber::operator/(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        if (p->value == 0) throw std::runtime_error("Diairesh me to 0");
        return std::make_shared<JsonNumber>(value / p->value);
    }
    throw std::runtime_error("Den mporei na ginei diairesi me mh-arithmitiki timi");
}

std::shared_ptr<JsonValue> JsonNumber::operator%(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        if (p->value == 0) throw std::runtime_error("Modulo me to 0");
        return std::make_shared<JsonNumber>(std::fmod(value, p->value));
    }
    throw std::runtime_error("Den mporei na ginei modulo me mh-arithmitiki timi");
}

bool JsonNumber::operator>(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return value > p->value;
    }
    throw std::runtime_error("Den ypostirizetai sygkrisi gia mh-arithmitiki timi");
}

bool JsonNumber::operator>=(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return value >= p->value;
    }
    throw std::runtime_error("Den ypostirizetai sygkrisi gia mh-arithmitiki timi");
}

bool JsonNumber::operator<(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return value < p->value;
    }
    throw std::runtime_error("Den ypostirizetai sygkrisi gia mh-arithmitiki timi");
}

bool JsonNumber::operator<=(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonNumber*>(&other)) {
        return value <= p->value;
    }
    throw std::runtime_error("Den ypostirizetai sygkrisi gia mh-arithmitiki timi");
}

// JsonObject ulopoiisi
JsonObject::JsonObject(const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& init)
    : keyValues(init) {}

void JsonObject::set(const std::string& key, std::shared_ptr<JsonValue> value) {
    auto it = std::find_if(keyValues.begin(), keyValues.end(),
        [&key](const auto& pair) { return pair.first == key; });
    if (it != keyValues.end()) {
        it->second = value;
    } else {
        keyValues.push_back({key, value});
    }
}

const std::shared_ptr<JsonValue>& JsonObject::get(const std::string& key) const {
    auto it = std::find_if(keyValues.begin(), keyValues.end(),
        [&key](const auto& pair) { return pair.first == key; });
    if (it == keyValues.end()) {
        throw std::runtime_error("Den vrethike kleidi: " + key);
    }
    return it->second;
}

void JsonObject::print() const {
    std::cout << "{";
    bool first = true;
    for (const auto& pair : keyValues) {
        if (pair.second) {  // Ektypose mono mh-null times
            if (!first) std::cout << ", ";
            std::cout << "\"" << pair.first << "\": ";
            pair.second->print();
            first = false;
        }
    }
    std::cout << "}";
}

void JsonObject::erase(const std::string& key) {
    auto it = std::find_if(keyValues.begin(), keyValues.end(),
        [&key](const auto& pair) { return pair.first == key; });
    if (it != keyValues.end()) {
        keyValues.erase(it);
    }
}

void JsonObject::erase() {
    keyValues.clear();
}

bool JsonObject::operator==(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonObject*>(&other)) {
        return keyValues == p->keyValues;
    }
    return false;
}

size_t JsonObject::size() const {
    return keyValues.size();
}

bool JsonObject::isEmpty() const {
    return keyValues.empty();
}

bool JsonObject::hasKey(const std::string& key) const {
    return std::find_if(keyValues.begin(), keyValues.end(),
        [&key](const auto& pair) { return pair.first == key; }) != keyValues.end();
}

std::string JsonObject::typeOf() const {
    return "object";
}

const std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>>& JsonObject::getKeyValues() const {
    return keyValues;
}

std::shared_ptr<JsonValue>& JsonObject::operator[](const std::string& key) {
    auto it = std::find_if(keyValues.begin(), keyValues.end(),
        [&key](const auto& pair) { return pair.first == key; });
    if (it != keyValues.end()) {
        return it->second;
    }
    keyValues.push_back({key, nullptr});
    return keyValues.back().second;
}

JsonValue& JsonObject::operator=(const std::shared_ptr<JsonValue>& other) {
    if (auto obj = std::dynamic_pointer_cast<JsonObject>(other)) {
        keyValues = obj->keyValues;
    }
    return *this;
}

std::shared_ptr<JsonValue> JsonObject::operator+(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonObject*>(&other)) {
        std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> newKeyValues(keyValues);
        for (const auto& pair : p->keyValues) {
            newKeyValues.push_back(pair);
        }
        return std::make_shared<JsonObject>(newKeyValues);
    }
    throw std::runtime_error("Den mporei na ginei concatenate me mh-object timi");
}

// JsonArray ulopoiisi
JsonArray::JsonArray(const std::vector<std::shared_ptr<JsonValue>>& init)
    : values(init) {}

void JsonArray::set(size_t index, std::shared_ptr<JsonValue> value) {
    if (index >= values.size()) {
        throw std::out_of_range("Array index ekso apo oria");
    }
    values[index] = value;
}

std::shared_ptr<JsonValue>& JsonArray::get(size_t index) {
    if (index >= values.size()) {
        throw std::out_of_range("Array index ekso apo oria");
    }
    return values[index];
}

void JsonArray::append(std::shared_ptr<JsonValue> value) {
    values.push_back(value);
}

void JsonArray::print() const {
    std::cout << "[";
    bool first = true;
    for (const auto& val : values) {
        if (val) {  // Ektypose mono mh-null times
            if (!first) std::cout << ", ";
            val->print();
            first = false;
        }
    }
    std::cout << "]";
}

void JsonArray::erase(size_t index) {
    if (index < values.size()) {
        values.erase(values.begin() + index);
    }
}

void JsonArray::erase() {
    values.clear();
}

bool JsonArray::operator==(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonArray*>(&other)) {
        return values == p->values;
    }
    return false;
}

size_t JsonArray::size() const {
    return values.size();
}

bool JsonArray::isEmpty() const {
    return values.empty();
}

std::string JsonArray::typeOf() const {
    return "array";
}

const std::vector<std::shared_ptr<JsonValue>>& JsonArray::getValues() const {
    return values;
}

std::shared_ptr<JsonValue>& JsonArray::operator[](size_t index) {
    if (index >= values.size()) {
        values.resize(index + 1);
    }
    return values[index];
}

JsonValue& JsonArray::operator=(const std::shared_ptr<JsonValue>& other) {
    if (auto arr = std::dynamic_pointer_cast<JsonArray>(other)) {
        values = arr->values;
    }
    return *this;
}

std::shared_ptr<JsonValue> JsonArray::operator+(const JsonValue& other) const {
    if (auto p = dynamic_cast<const JsonArray*>(&other)) {
        std::vector<std::shared_ptr<JsonValue>> newValues(values);
        newValues.insert(newValues.end(), p->values.begin(), p->values.end());
        return std::make_shared<JsonArray>(newValues);
    }
    throw std::runtime_error("Den mporei na ginei concatenate me mh-array timi");
}

// Voithitikes sunartiseis ulopoiisi
void printJsonHelper(const std::shared_ptr<JsonValue>& value) {
    if (!value) {
        std::cout << "null" << std::endl;
        return;
    }
    value->print();
    std::cout << std::endl;
}

void printJson(const std::shared_ptr<JsonValue>& jsonValue) {
    printJsonHelper(jsonValue);
}

void printJson(const std::shared_ptr<JsonValue>& jsonValue, const std::string& keyPath) {
    if (!jsonValue) {
        std::cout << "null" << std::endl;
        return;
    }

    std::string current;
    size_t pos = 0;
    std::shared_ptr<JsonValue> currentValue = jsonValue;

    while (pos < keyPath.length()) {
        size_t nextDot = keyPath.find('.', pos);
        current = keyPath.substr(pos, nextDot - pos);
        
        if (auto obj = dynamic_cast<JsonObject*>(currentValue.get())) {
            try {
                currentValue = obj->get(current);
            } catch (const std::runtime_error&) {
                std::cout << "null" << std::endl;
                return;
            }
        } else {
            std::cout << "null" << std::endl;
            return;
        }

        if (nextDot == std::string::npos) break;
        pos = nextDot + 1;
    }

    currentValue->print();
    std::cout << std::endl;
}
