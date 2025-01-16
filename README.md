# JSONlang Library

## Overview
The JSONlang project was developed as part of the HY352 - Software Engineering course.
This project was collaboratively developed by **Alexandros Papafragkakis** and **Sofia Koulouraki**.

## Introduction

JSONlang is a lightweight library for handling and manipulating JSON data structures in C++ with an intuitive and simplified syntax.

## Key Features

### JSON Data Types
The library supports the following JSON-compatible data types:
- **Object**: A collection of key-value pairs.
- **Array**: An ordered list of values.
- **String**: Represents textual data.
- **Number**: Supports integers and floating-point values.
- **Boolean**: Represents `true` or `false`.
- **Null**: Represents an absence of a value.

### Dynamic Editing
  - `SET json_lvalue ASSIGN value`: Assigns or updates the value of a JSON node.
  - `SET json_array APPEND value1, value2, ...`: Appends multiple values to a JSON array.
  - `ERASE json_value_or_variable`: Deletes elements from JSON objects or arrays, or clears an entire JSON variable.

### Operations and Expressions
- **Arithmetic and Associative Operations:**
  - Supported between numbers: `+`, `-`, `*`, `/`, `%`, `<`, `<=`, `>`, `>=`.
  - Special case: The `+` operator supports concatenating strings, arrays, and objects.

- **Logical Operations:**
  - Supported between boolean values: `&&`, `||`, `!`.

- **Equality Operations:**
  - `==`, `!=` support all types.
  - Objects and arrays are compared recursively for equality.

- **Utility Operations:**
  - `SIZE_OF(json_value_or_variable)`: Returns the number of elements in arrays or objects.
  - `IS_EMPTY(json_value_or_variable)`: Checks if an object or array is empty.
  - `HAS_KEY(json_value_or_variable, key)`: Verifies the existence of a key in an object.
  - `TYPE_OF(json_value_or_variable)`: Returns the type of the JSON value as a string (e.g., "string", "number").

### Printing JSON Values
Use the `PRINT` macro to display JSON variables.


## File Structure
### Source Files
- **`JSONlang.cpp`:** The core implementation of the JSONlang library.
- **`JSONlang.h`:** Header file containing class declarations, macros, and utility function prototypes.

### Test Cases
The `TESTING` folder contains test cases for validating and demonstrating the library's functionalities:
- **`test1.cpp`:** Demonstrates basic JSON object and array creation, printing, and accessing.
- **`test2.cpp`:** Explores modifying JSON values, appending elements, and usage of dynamic macros.
- **`test3.cpp`:** Focuses on arithmetic and logical operations with JSON values.
- **`test4.cpp`:** Tests type information, size queries, and key existence functions.
- **`test5.cpp`:** Dedicated to testing the `PRINT` functionality in various contexts, including objects, arrays, and nested structures.

---

## Installation and Usage
### Prerequisites
- A C++17-compliant compiler such as GCC or Clang.

### Compilation
To compile a test file:
```bash
g++ -std=c++17 -o json_test -I. TESTING/test.cpp JSONlang.cpp
```
### Running
To execute the compiled binary:
```bash
./json_test
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.