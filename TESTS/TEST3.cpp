#include "JSONlang.h"

int main() {
    // Arithmitikes prakseis
    auto sum = NUMBER(10) + NUMBER(5);         // 10 + 5 = 15
    auto diff = NUMBER(10) - NUMBER(5);        // 10 - 5 = 5
    auto prod = NUMBER(10) * NUMBER(5);        // 10 * 5 = 50
    auto quotient = NUMBER(10) / NUMBER(5);    // 10 / 5 = 2
    auto mod = NUMBER(10) % NUMBER(3);         // 10 % 3 = 1

    // Ektypwsi apotelesmatwn arithmitikwn prakselwn
    std::cout << "Arithmetic operations:\n";
    std::cout << "10 + 5 = "; 
    sum->print();  // Anamenomeno Apotelesma: 15
    std::cout << "\n10 - 5 = "; 
    diff->print(); // Anamenomeno Apotelesma: 5
    std::cout << "\n10 * 5 = "; 
    prod->print(); // Anamenomeno Apotelesma: 50
    std::cout << "\n10 / 5 = "; 
    quotient->print(); // Anamenomeno Apotelesma: 2
    std::cout << "\n10 % 3 = "; 
    mod->print(); // Anamenomeno Apotelesma: 1
    std::cout << std::endl << std::endl;

    // Sygkritikes prakseis
    auto result1 = NUMBER(10) > NUMBER(5);     // true
    auto result2 = NUMBER(10) < NUMBER(5);     // false
    auto result3 = NUMBER(10) >= NUMBER(10);   // true
    auto result4 = NUMBER(10) <= NUMBER(5);    // false

    // Ektypwsi apotelesmatwn sygkritikwn prakselwn
    std::cout << "Relational operations:\n";
    std::cout << "10 > 5: ";
    std::cout << std::boolalpha << result1;  // Anamenomeno Apotelesma: true
    std::cout << "\n10 < 5: ";
    std::cout << std::boolalpha << result2;  // Anamenomeno Apotelesma: false
    std::cout << "\n10 >= 10: ";
    std::cout << std::boolalpha << result3;  // Anamenomeno Apotelesma: true
    std::cout << "\n10 <= 5: ";
    std::cout << std::boolalpha << result4;  // Anamenomeno Apotelesma: false
    std::cout << std::endl << std::endl;

    // Logikes prakseis
    auto andResult = BOOLEAN(true) && BOOLEAN(false);  // true && false = false
    auto orResult = BOOLEAN(true) || BOOLEAN(false);   // true || false = true
    auto notResult = !BOOLEAN(true);                    // !true = false

    // Ektypwsi apotelesmatwn logikwn prakselwn
    std::cout << "Logical operations:\n";
    std::cout << "true && false: ";
    std::cout << std::boolalpha << andResult << std::endl;  // Anamenomeno Apotelesma: false
    std::cout << "true || false: ";
    std::cout << std::boolalpha << orResult << std::endl;   // Anamenomeno Apotelesma: true
    std::cout << "!true: ";
    std::cout << std::boolalpha << notResult << std::endl;  // Anamenomeno Apotelesma: false
    std::cout << std::endl << std::endl;

    // Synenwsi pinakwn
    auto array1 = ARRAY(NUMBER(1), NUMBER(2));
    auto array2 = ARRAY(NUMBER(3), NUMBER(4));
    auto arrayConcat = ARRAY(NUMBER(1), NUMBER(2)) + ARRAY(NUMBER(3), NUMBER(4));  // [1, 2] + [3, 4] = [1, 2, 3, 4]

    // Ektypwsi apotelesmatos synenwsis pinakwn
    std::cout << "Array concatenation (ARRAY[NUMBER(1), NUMBER(2)] + ARRAY[NUMBER(3), NUMBER(4)]) = ";
    arrayConcat->print();  // Anamenomeno Apotelesma: [1, 2, 3, 4]
    std::cout << std::endl << std::endl;

    // Synenwsi strings
    auto str1 = STRING("hello");
    auto str2 = STRING(" world");
    auto strConcat = STRING("hello") + STRING(" world");  // "hello" + " world" = "hello world"

    // Ektypwsi apotelesmatos synenwsis strings
    std::cout << "String concatenation (STRING(\"hello\") + STRING(\" world\")) = ";
    strConcat->print();  // Anamenomeno Apotelesma: "hello world"
    std::cout << std::endl << std::endl;

    // Synenwsi JSON antikeimenwn
    auto obj1_1 = OBJECT({ "key1", NUMBER(1) });
    auto obj2_1 = OBJECT({ "key2", NUMBER(2) });
    auto objConcat = OBJECT({ "key1", NUMBER(1) }) + OBJECT({ "key2", NUMBER(2) });  // Syndesi dyo antikeimenwn

    // Ektypwsi apotelesmatos synenwsis antikeimenwn
    std::cout << "Object concatenation (OBJECT({\"key1\", NUMBER(1)}) + OBJECT({\"key2\", NUMBER(2)})) = ";
    objConcat->print();  // Anamenomeno Apotelesma: {"key1": 1, "key2": 2}
    std::cout << std::endl << std::endl;

    // Dimioyrgia JSON pinakwn
    JSON(arr1) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr2) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr3) = ARRAY(NUMBER(42), STRING("World"));

    // Dimioyrgia JSON antikeimenwn
    JSON(obj1_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj2_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj3_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("World") });

    // Ektypwsi apotelesmatwn sygkriseon pinakwn
    std::cout << "Array comparisons:\n";
    std::cout << "arr1 == arr2: " << (OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") }) == OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") }) ? "true" : "false") << std::endl;  // Anamenomeno Apotelesma: true
    std::cout << "arr1 != arr3: " << (*arr1 != *arr3 ? "true" : "false") << std::endl << std::endl;  // Anamenomeno Apotelesma: true

    // Ektypwsi apotelesmatwn sygkriseon antikeimenwn
    std::cout << "Object comparisons:\n";
    std::cout << "obj1_2 == obj2_2: " << (*obj1_2 == *obj2_2 ? "true" : "false") << std::endl;  // Anamenomeno Apotelesma: true
    std::cout << "obj1_2 != obj3_2: " << (*obj1_2 != *obj3_2 ? "true" : "false") << std::endl << std::endl;  // Anamenomeno Apotelesma: true

    // Orismos JSON antikeimenou gia bathmologies
    JSON(hy352_nik) = OBJECT(
        {KEY("exam"), NUMBER(7)},
        {KEY("project"), NUMBER(8)}
    );

    // Orismos antikeimenou mathiti me ypologismo mesou orou
    JSON(students) = ARRAY(
        OBJECT(
            {KEY("name"), STRING("Nikos ") + STRING("Nikolaou")},
            {KEY("id"), NUMBER(4444)},
            {KEY("grades"), ARRAY(
                OBJECT(
                    {KEY("hy352"), 
                        std::dynamic_pointer_cast<JsonObject>(hy352_nik)->getKeyValues()[0].second * NUMBER(0.75) + 
                        std::dynamic_pointer_cast<JsonObject>(hy352_nik)->getKeyValues()[1].second * NUMBER(0.25)
                    }
                )
            )},
            {KEY("courses"), ARRAY(
                STRING("CS101"),
                STRING("CS102")
            )}
        ),
        OBJECT(
            {KEY("name"), STRING("Maria ") + STRING("Papadopoulou")},
            {KEY("id"), NUMBER(4445)},
            {KEY("grades"), ARRAY(
                OBJECT(
                    {KEY("hy352"), 
                        std::dynamic_pointer_cast<JsonObject>(hy352_nik)->getKeyValues()[0].second * NUMBER(0.75) + 
                        std::dynamic_pointer_cast<JsonObject>(hy352_nik)->getKeyValues()[1].second * NUMBER(0.25)
                    }
                )
            )},
            {KEY("courses"), ARRAY(
                STRING("CS101"),
                STRING("CS201")
            )}
        )
    );

    // Ektypwsi olwn twn mathitwn kai twn bathmwn
    for (const auto& student : std::dynamic_pointer_cast<JsonArray>(students)->getValues()) {
        student->print();  // Ektypwsi kathe mathiti
        std::cout << std::endl;
    }

    return 0;
}
