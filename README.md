# JSON C++ Library

## Overview

This project is a lightweight library for creating, manipulating, and printing JSON-like data structures in C++. It includes a robust set of classes and macros for handling JSON objects, arrays, strings, numbers, booleans, and null values, making it easy to represent and output JSON data programmatically.

## Files

### 1. `JSONlang.h`
- **Purpose**: 
  - Defines the core classes (`JsonObject`, `JsonArray`, `JsonString`, `JsonNumber`, `JsonBoolean`, `JsonNull`) and the `JsonValue` base class.
  - Provides macros for convenient creation and manipulation of JSON objects and arrays.

- **Classes**:
  - **JsonValue**: Abstract base class for all JSON types.
  - **JsonObject**: Represents key-value pairs in JSON.
  - **JsonArray**: Represents a collection of JSON values.
  - **JsonString**: Represents a JSON string.
  - **JsonNumber**: Represents a JSON number.
  - **JsonBoolean**: Represents a JSON boolean (`true` or `false`).
  - **JsonNull**: Represents a JSON null value.

- **Macros**:
  - **JSON(name)**: Declares a JSON object or array.
  - **OBJECT(...)**: Creates a `JsonObject` with key-value pairs.
  - **ARRAY(...)**: Creates a `JsonArray` with values.
  - **STRING(value), NUMBER(value), TRUE, FALSE, JSON_NULL**: Macros for JSON types.
  - **KEY(key)**: Helper macro for JSON keys.

### 2. `JSONlang.cpp`
- **Purpose**: Implements the functionality defined in `JSONlang.h`.
- **Details**:
  - Implements methods for all classes, including constructors and `print()` methods.
  - Provides logic for handling key-value pairs, arrays, and other JSON elements.

### 3. `main.cpp`
- **Purpose**: Demonstrates the use of the JSON library through various examples.
- **Examples**:
  1. **Creating Empty JSON Object and Array**:
     ```cpp
     JSON(emptyObj) = OBJECT();
     emptyObj->print(); // Outputs: {}
     JSON(emptyArray) = ARRAY();
     emptyArray->print(); // Outputs: []
     ```

  2. **Creating a Complex JSON Object**:
     ```cpp
     JSON(book) = OBJECT(
         {KEY("title"), STRING("Gone Girl")},
         {KEY("published"), NUMBER(2012)},
         {KEY("type"), STRING("Thriller")},
         {KEY("author"), OBJECT(
             {KEY("firstname"), STRING("GILLIAN")},
             {KEY("sirname"), STRING("FLYNN")},
             {KEY("age"), NUMBER(45)}
         )}
     );
     book->print(); 
     // Outputs a structured JSON object.
     ```

  3. **Creating and Printing Arrays**:
     ```cpp
     JSON(week_temperatures) = ARRAY(
         NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
         NUMBER(19), NUMBER(18.5), NUMBER(19)
     );
     week_temperatures->print(); // Outputs: [20, 19.5, 19, 20, 19, 18.5, 19]
     ```

  4. **Nested JSON Structures**:
     Demonstrates a `students` array containing objects, arrays, and key-value pairs.

## How to Use

1. **Clone or Copy the Project**:
   Copy all `.cpp` and `.h` files to your project directory.

2. **Compile the Code**:
   Use the following command to compile:
   ```bash
   g++ -o json_test main.cpp JSONlang.cpp
